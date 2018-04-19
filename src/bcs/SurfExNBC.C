/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#include "SurfExNBC.h"
#include "Function.h"

registerMooseObject("stoatApp", SurfExNBC);


template<>
InputParameters validParams<SurfExNBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addClassDescription("Integrated BC that sets the flux of u as J = -k(C_inf - u)");
  params.addRequiredParam<Real>("c_infinity", "Final equilibrium concentration");
  params.addRequiredParam<Real>("k", "Exchange coefficient");

  return params;
}

SurfExNBC::SurfExNBC(const InputParameters & parameters) :
    IntegratedBC(parameters),
    _c_infinity(getParam<Real>("c_infinity")),
    _k(getParam<Real>("k"))
{}


Real
SurfExNBC::computeQpResidual()
{
  return _test[_i][_qp] * _k * (_u[_qp] - _c_infinity);
}

Real
SurfExNBC::computeQpJacobian()
{
  return _test[_i][_qp] * _k * _phi[_j][_qp];
}
