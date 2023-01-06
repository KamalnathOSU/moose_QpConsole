//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "FVFluxBC.h"
#include "INSFVFlowBC.h"

/**
 * Flux boundary condition for the weakly compressible scalar advection equation
 */
class WCNSFVScalarFluxBC : public FVFluxBC, public INSFVFlowBC
{
public:
  static InputParameters validParams();
  WCNSFVScalarFluxBC(const InputParameters & params);

protected:
  ADReal computeQpResidual() override;

  /// Scaling factor
  const Real _scaling_factor;

  /// Postprocessor with the inlet scalar concentration
  const PostprocessorValue * const _scalar_value_pp;

  /// Postprocessor with the inlet scalar flow rate
  const PostprocessorValue * const _scalar_flux_pp;

  /// Postprocessor with the inlet velocity
  const PostprocessorValue * const _velocity_pp;

  /// Postprocessor with the inlet mass flow rate
  const PostprocessorValue * const _mdot_pp;

  /// Postprocessor with the inlet area
  const PostprocessorValue * const _area_pp;

  /// Fluid density functor
  const Moose::Functor<ADReal> * const _rho;

  /// The direction in which the flow is entering/leaving the domain. This is mainly used for cases
  /// when the orientation of the face cannot be established (boundary on an internal face) or when the flow is
  /// entering with an angle compared to the boundary surface.
  const Point _direction;

  /// Flag to store if the flow direction is specified by the user
  const bool _direction_specified_by_user;
};
