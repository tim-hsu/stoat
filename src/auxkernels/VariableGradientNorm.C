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
