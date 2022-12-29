//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "MultiAppGeneralFieldTransfer.h"
#include "KDTree.h"

/**
 * Performs a geometric interpolation based on the values at the nearest nodes to a target location
 * in the origin mesh.
 */
class MultiAppGeneralFieldNearestNodeTransfer : public MultiAppGeneralFieldTransfer
{
public:
  static InputParameters validParams();

  MultiAppGeneralFieldNearestNodeTransfer(const InputParameters & parameters);

protected:
  virtual void prepareEvaluationOfInterpValues(const VariableName & var_name) override;

  virtual void evaluateInterpValues(const std::vector<Point> & incoming_points,
                                    std::vector<std::pair<Real, Real>> & outgoing_vals) override;

  using MultiAppGeneralFieldTransfer::inBlocks;
  bool inBlocks(const std::set<SubdomainID> & blocks,
                const MooseMesh & mesh,
                const Elem * elem) const override;

private:
  /*
   * Build mesh functions
   */
  void buildKDTrees(const VariableName & var_name,
                    std::vector<std::shared_ptr<KDTree>> & local_kdtrees,
                    std::vector<std::vector<Point>> & local_points,
                    std::vector<std::vector<Real>> & local_values);

  /*
   * Evaluate interpolation values for incoming points
   */
  void evaluateInterpValuesNearestNode(const std::vector<std::shared_ptr<KDTree>> & local_kdtrees,
                                       const std::vector<std::vector<Point>> & local_points,
                                       const std::vector<std::vector<Real>> & local_values,
                                       const std::vector<Point> & incoming_points,
                                       std::vector<std::pair<Real, Real>> & outgoing_vals);

  std::vector<std::shared_ptr<KDTree>> _local_kdtrees;

  std::vector<std::vector<Point>> _local_points;

  std::vector<std::vector<Real>> _local_values;

  /// Number of points to consider
  unsigned int _num_nearest_points;
};
