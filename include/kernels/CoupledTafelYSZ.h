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

#ifndef COUPLEDTAFELYSZ_H
#define COUPLEDTAFELYSZ_H

#include "Kernel.h"

// Forward Declaration
class CoupledTafelYSZ;

template<>
InputParameters validParams<CoupledTafelYSZ>();

/**
 * Coupled Tafel source for potential in YSZ.
 */

class CoupledTafelYSZ : public Kernel
{
public:
  CoupledTafelYSZ(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

private:
  Real _j0;       // exchange (equilibrium) current density
  Real _alpha;
  Real _F;
  Real _cO2_ref;
  Real _R;
  Real _T;
  Real _E_rev;    // reversible voltage (V)
  Real _phi_LSM;

  unsigned int _num_c_O2;
  const VariableValue & _c_O2;
};

#endif //COUPLEDTAFELYSZ_H
