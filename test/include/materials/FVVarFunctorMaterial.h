//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "Material.h"

template <typename>
class MooseVariableFV;
template <typename>
class FunctorMaterialProperty;

/**
 * A material that couples a variable
 */
class FVVarFunctorMaterial : public Material
{
public:
  static InputParameters validParams();

  FVVarFunctorMaterial(const InputParameters & parameters);

protected:
  void computeQpProperties() override;

  const MooseVariableFV<Real> & _var;
  FunctorMaterialProperty<ADReal> & _functor_prop;
};
