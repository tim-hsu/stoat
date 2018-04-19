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

#ifndef VARIABLEGRADIENTNORM_H
#define VARIABLEGRADIENTNORM_H

// MOOSE includes
#include "AuxKernel.h"

// Forward declarations
class VariableGradientNorm;

template<>
InputParameters validParams<VariableGradientNorm>();

/**
 * Compute the norm of the gradient of a variable
 */
class VariableGradientNorm : public AuxKernel
{
public:

  /**
   * Class constructor
   * @param parameters Input parameters for the object
   */
  VariableGradientNorm(const InputParameters & parameters);

protected:
  virtual Real computeValue() override;

private:

  /// Reference to the gradient of the coupled variable
  const VariableGradient & _gradient;

};

#endif // VARIABLEGRADIENTNORM_H
