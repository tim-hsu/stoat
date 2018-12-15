#include "ChargeTransferButlerNBC.h"
#include "Function.h"
#include <cmath>

registerMooseObject("stoatApp", ChargeTransferButlerNBC);


template<>
InputParameters validParams<ChargeTransferButlerNBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addClassDescription("Integrated BC that sets the electric flux at YSZ interface as j = 2 * j0 * sinh(coef * eta), where eta_ct = E_rev - (phi_LSM - phi_YSZ)");
  params.addRequiredParam<Real>("E_rev", "Reversible Nernst potential");
  params.addRequiredParam<Real>("phi_LSM", "Potential in LSM");
  params.addRequiredParam<Real>("j0", "Charge Transfer exchange current density");
  params.addParam<Real>("z", 4, "Number of electrons involved in the reaction");
  params.addParam<Real>("F", 96485.33, "Faraday constant (C/mol)");
  params.addParam<Real>("R", 8.31446, "Gas constant");
  params.addParam<Real>("T", 1073, "Temperature");
  return params;
}

ChargeTransferButlerNBC::ChargeTransferButlerNBC(const InputParameters & parameters) :
    IntegratedBC(parameters),
    _E_rev(getParam<Real>("E_rev")),
    _phi_LSM(getParam<Real>("phi_LSM")),
    _j0(getParam<Real>("j0")),
    _z(getParam<Real>("z")),
    _F(getParam<Real>("F")),
    _R(getParam<Real>("R")),
    _T(getParam<Real>("T"))
{}


Real
ChargeTransferButlerNBC::computeQpResidual()
{
  Real b    = _z * _F / _R / _T;
  Real eta  = _E_rev - (_phi_LSM - _u[_qp]);
  Real res  = 2 * _j0 * sinh(0.5 * b * eta);
  return _test[_i][_qp] * res;
}

Real
ChargeTransferButlerNBC::computeQpJacobian()
{
  Real b    = _z * _F / _R / _T;
  Real eta  = _E_rev - (_phi_LSM - _u[_qp]);
  Real jac  = b * _j0 * cosh(0.5 * b * eta);
  return _test[_i][_qp] * _phi[_j][_qp] * jac;
}
