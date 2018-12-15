#ifndef CHARGETRANSFERBUTLERNBC_H
#define CHARGETRANSFERBUTLERNBC_H

#include "IntegratedBC.h"

// Charge Transfer Neumann Boundary Condition between LSM and YSZ

class ChargeTransferButlerNBC : public IntegratedBC
{
public:
  ChargeTransferButlerNBC(const InputParameters & parameters);
  virtual ~ChargeTransferButlerNBC() {}

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  const Real _E_rev;      // reversible Nernst potential
  const Real _phi_LSM;    // potential in LSM
  const Real _j0;
  const Real _z;
  const Real _F;
  const Real _R;
  const Real _T;
};

template<>
InputParameters validParams<ChargeTransferButlerNBC>();

#endif //SURFEXNBC
