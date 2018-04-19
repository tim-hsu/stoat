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

#ifndef INTERFACESURFEXCHANGEFULLYCOUPLED_H
#define INTERFACESURFEXCHANGEFULLYCOUPLED_H

#include "InterfaceKernel.h"

//Forward Declarations
class InterfaceSurfExchangeFullyCoupled;

template<>
InputParameters validParams<InterfaceSurfExchangeFullyCoupled>();

/**
 * DG kernel for surface exchange of oxygen across LSM/pore
 */
class InterfaceSurfExchangeFullyCoupled : public InterfaceKernel
{
public:
  InterfaceSurfExchangeFullyCoupled(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual(Moose::DGResidualType type);
  virtual Real computeQpJacobian(Moose::DGJacobianType type);

  const Real _k;             // exchange coefficient
  const Real _R;
  const Real _T;
};

#endif
