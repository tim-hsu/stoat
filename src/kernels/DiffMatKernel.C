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
#include "DiffMatKernel.h"

registerMooseObject("stoatApp", DiffMatKernel);


template<>
InputParameters validParams<DiffMatKernel>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<MaterialPropertyName>("diff_coef", "the name of the diffusion coefficient (material property)");
  return params;
}


DiffMatKernel::DiffMatKernel(const InputParameters & parameters) :
    Kernel(parameters),
    _diff_coef(getMaterialProperty<Real>("diff_coef"))
{
}

Real
DiffMatKernel::computeQpResidual()
{
  return _diff_coef[_qp] * _grad_test[_i][_qp] * _grad_u[_qp];
}

Real
DiffMatKernel::computeQpJacobian()
{
  return _diff_coef[_qp] * _grad_test[_i][_qp] * _grad_phi[_j][_qp];
}
