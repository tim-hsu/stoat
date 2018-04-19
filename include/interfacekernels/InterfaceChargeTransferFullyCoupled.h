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

#ifndef INTERFACECHARGETRANSFERFULLYCOUPLED_H
#define INTERFACECHARGETRANSFERFULLYCOUPLED_H

#include "InterfaceKernel.h"

//Forward Declarations
class InterfaceChargeTransferFullyCoupled;

template<>
InputParameters validParams<InterfaceChargeTransferFullyCoupled>();

/**
 * DG kernel for charge trasnfer of oxygen ions/vacancies across LSM/YSZ interface
 */
class InterfaceChargeTransferFullyCoupled : public InterfaceKernel
{
public:
  InterfaceChargeTransferFullyCoupled(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual(Moose::DGResidualType type);
  virtual Real computeQpJacobian(Moose::DGJacobianType type);

  const Real _j0;
  const Real _z;
  const Real _F;
  const Real _R;
  const Real _T;
  const Real _phi_LSM;
  const Real _pO2_CE;
};

#endif
