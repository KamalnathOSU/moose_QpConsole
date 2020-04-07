#pragma once

#include "Kernel.h"
#include "DerivativeMaterialInterfaceTHM.h"

/**
 * Computes the area gradient term in the momentum equation.
 *
 * This kernel computes the following area gradient term in momentum equation:
 * \f[
 *   p_k \frac{\partial A}{\partial x} .
 * \f]
 */
class OneD3EqnMomentumAreaGradient : public DerivativeMaterialInterfaceTHM<Kernel>
{
public:
  OneD3EqnMomentumAreaGradient(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  const VariableGradient & _area_grad;

  /// The direction of the flow channel
  const MaterialProperty<RealVectorValue> & _dir;

  const MaterialProperty<Real> & _pressure;
  const MaterialProperty<Real> & _dp_darhoA;
  const MaterialProperty<Real> & _dp_darhouA;
  const MaterialProperty<Real> & _dp_darhoEA;

  unsigned int _arhoA_var_number;
  unsigned int _arhoE_var_number;

public:
  static InputParameters validParams();
};
