#ifndef CHARGETRANSFERNBC_H
#define CHARGETRANSFERNBC_H

#include "IntegratedBC.h"

// Charge Transfer Neumann Boundary Condition between LSM and YSZ

class ChargeTransferNBC : public IntegratedBC
{
public:
  ChargeTransferNBC(const InputParameters & parameters);
  virtual ~ChargeTransferNBC() {}

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  const Real _E_rev;      // reversible Nernst potential
  const Real _phi_LSM;    // potential in LSM
  const Real _ASR_ct;     // area specific resistance
};

template<>
InputParameters validParams<ChargeTransferNBC>();

#endif //SURFEXNBC
