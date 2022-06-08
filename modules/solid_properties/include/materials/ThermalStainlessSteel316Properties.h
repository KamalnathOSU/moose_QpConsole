//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "ThermalSolidPropertiesMaterial.h"

/**
 * Stainless steel alloy 306 thermal solid properties as a function of
 * temperature \cite mills.
 *
 * The transition melting range is from 1385 C to 1450 C, so all data used here
 * is obtained form solid phase measurements and these properties should not
 * be used to compute transition or liquid regime properties.
 */
class ThermalStainlessSteel316Properties : public ThermalSolidPropertiesMaterial
{
public:
  static InputParameters validParams();

  ThermalStainlessSteel316Properties(const InputParameters & parameters);

  /**
   * Molar mass
   * The nominal chemical composition in weight percent is:
   * 0.08 C, 17.0 Cr, 0.3 Cu, 65.0 Fe, 2.0 Mn, 2.5 Mo, 12.0 Ni, 1.0 Si \cite mills.
   * @return molar mass (kg/mol)
   */
  virtual Real molarMass() const override;

  /**
   * Isobaric specific heat capacity (J/kg$\cdot$K) as a function of temperature (K).
   * A curve fit is performed from data in \cite mills over
   * 25 $\degree$C $\le$ T $\le$ 1300 $\degree$C. The fit is obtained with an
   * R$^2$ value of 0.9926. Uncertainty on the tabulated data is $\pm$ 5%.
   */
  virtual void computeIsobaricSpecificHeat() override;

  /// Isobaric specific heat capacity derivatives
  virtual void computeIsobaricSpecificHeatDerivatives() override;

  /**
   * Thermal conductivity (W/m$\cdot$K) as a function of temperature (K).
   * A curve fit is performed from data in \cite mills over
   * 25 $\degree$ C $\le$ T $\le$ 1300 $\degree$ C. The fit is obtained with an
   * R$^2$ value of 0.9960. Uncertainty on the tabulated data is $\pm$ 10%.
   */
  virtual void computeThermalConductivity() override;

  /// Thermal conductivity derivatives
  virtual void computeThermalConductivityDerivatives() override;

  /**
   * Density (kg/m$^3$) as a function of temperature (K).
   * A curve fit is performed from data in \cite mills over
   * 25 $\degree$ C $\le$ T $\le$ 1300 $\degree$ C. The fit is obtained with
   * an R$^2$ value of 0.9995. Uncertainty on the tabulated data is $\pm$ 3%.
   */
  virtual void computeDensity() override;

  /// Density derivatives
  virtual void computeDensityDerivatives() override;

private:
  /// The solid name
  static const std::string _name;
};
