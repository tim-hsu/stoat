#include "ChargeTransferNBC.h"
#include "Function.h"

registerMooseObject("stoatApp", ChargeTransferNBC);


template<>
InputParameters validParams<ChargeTransferNBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addClassDescription("Integrated BC that sets the electric flux as J = eta_ct / ASR_ct, where eta_ct = E_rev - (phi_LSM - phi_YSZ)");
  params.addRequiredParam<Real>("E_rev", "Reversible Nernst potential");
  params.addRequiredParam<Real>("phi_LSM", "Potential in LSM");
  params.addRequiredParam<Real>("ASR_ct", "Area specific resistance w.r.t. charge trasnfer");
  return params;
}

ChargeTransferNBC::ChargeTransferNBC(const InputParameters & parameters) :
    IntegratedBC(parameters),
    _E_rev(getParam<Real>("E_rev")),
    _phi_LSM(getParam<Real>("phi_LSM")),
    _ASR_ct(getParam<Real>("ASR_ct"))
{}


Real
ChargeTransferNBC::computeQpResidual()
{
  return _test[_i][_qp] * (_E_rev - (_phi_LSM - _u[_qp])) / _ASR_ct;
}

Real
ChargeTransferNBC::computeQpJacobian()
{
  return _test[_i][_qp] * _phi[_j][_qp] / _ASR_ct;
}
