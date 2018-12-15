#ifndef SURFEXNBC_H
#define SURFEXNBC_H

#include "IntegratedBC.h"

// Surface Exchange Neumann Boundary Condition (generic)

class SurfExNBC : public IntegratedBC
{
public:
  SurfExNBC(const InputParameters & parameters);
  virtual ~SurfExNBC() {}

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  const Real _c_infinity;       // equilibrium concentration
  const Real _k;                // exchange coefficient
};

template<>
InputParameters validParams<SurfExNBC>();

#endif //SURFEXNBC
