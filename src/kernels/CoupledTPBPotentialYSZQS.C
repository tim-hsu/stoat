/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "CoupledTPBPotentialYSZQS.h"
#include "Function.h"
#include <cmath>

registerMooseObject("stoatApp", CoupledTPBPotentialYSZQS);


template<>
InputParameters validParams<CoupledTPBPotentialYSZQS>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Fully Coupled TPB reaction source kernel in Butler-Volmer sinh() form for potential in YSZ. j = 2 * j0 * sinh(coef * eta)");
  params.addRequiredParam<Real>("s0", "Exchange volumetric current density rate (A/cm^3)");
  params.addParam<Real>("z", 4.0, "electron number (num of electrons transferred)");
  params.addParam<Real>("F", 96485.33289, "Faraday constant (C/mol)");
  params.addParam<Real>("R", 8.3144598, "Gas constant (J/K/mol)");
  params.addParam<Real>("T", 1073.0, "Temperature (T)");
  params.addRequiredParam<FunctionName>("function_phi_LSM", "Function for the LSM potential");
  params.addRequiredParam<Real>("pO2_CE", "Oxygen partial pressure at the counter electrode (atm)");
  params.addRequiredCoupledVar("p_O2", "The coupled oxygen partial pressure variable in pore");
  return params;
}

CoupledTPBPotentialYSZQS::CoupledTPBPotentialYSZQS(const InputParameters & parameters) :
    Kernel(parameters),
    _s0(getParam<Real>("s0")),
    _z(getParam<Real>("z")),
    _F(getParam<Real>("F")),
    _R(getParam<Real>("R")),
    _T(getParam<Real>("T")),
    _func_phi_LSM(getFunction("function_phi_LSM")),
    _pO2_CE(getParam<Real>("pO2_CE")),
    _num_p_O2(coupled("p_O2")),
    _p_O2(coupledValue("p_O2"))
{
}

Real
CoupledTPBPotentialYSZQS::computeQpResidual()
{
  Real b       = _z * _F / _R / _T;
  Real E_conc  = - _R * _T / _z / _F * log(_pO2_CE / _p_O2[_qp]);
  Real phi_LSM = _func_phi_LSM.value(_t, _q_point[_qp]);
  Real eta     = E_conc - (phi_LSM - _u[_qp]);

  Real res     = 2 * _s0 * sinh(0.5 * b * eta);

  return res * _test[_i][_qp];
}

Real
CoupledTPBPotentialYSZQS::computeQpJacobian()
{
  Real b       = _z * _F / _R / _T;
  Real E_conc  = - _R * _T / _z / _F * log(_pO2_CE / _p_O2[_qp]);
  Real phi_LSM = _func_phi_LSM.value(_t, _q_point[_qp]);
  Real eta     = E_conc - (phi_LSM - _u[_qp]);

  Real jac     = b * _s0 * cosh(0.5 * b * eta);

  return jac * _test[_i][_qp] * _phi[_j][_qp];
}

Real
CoupledTPBPotentialYSZQS::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _num_p_O2)
  {
    Real b       = _z * _F / _R / _T;
    Real E_conc  = - _R * _T / _z / _F * log(_pO2_CE / _p_O2[_qp]);
    Real phi_LSM = _func_phi_LSM.value(_t, _q_point[_qp]);
    Real eta     = E_conc - (phi_LSM - _u[_qp]);

    Real jac     = _s0 * cosh(0.5 * b * eta) / _p_O2[_qp];

    return jac * _test[_i][_qp] * _phi[_j][_qp];
  }
  else return 0.0;
}
