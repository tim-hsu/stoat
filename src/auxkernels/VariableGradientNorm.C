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
#include "VariableGradientNorm.h"
#include <math.h>

registerMooseObject("stoatApp", VariableGradientNorm);


template<>
InputParameters validParams<VariableGradientNorm>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("gradient_variable", "The variable from which to compute the norm of the gradient");
  return params;
}

VariableGradientNorm::VariableGradientNorm(const InputParameters & parameters) :
    AuxKernel(parameters),
    _gradient(coupledGradient("gradient_variable"))
{
}

Real
VariableGradientNorm::computeValue()
{
  return sqrt( _gradient[_qp](0) * _gradient[_qp](0) + _gradient[_qp](1) * _gradient[_qp](1) + _gradient[_qp](2) * _gradient[_qp](2) );
}
