#ifndef CLOSURES1PHASEBASE_H
#define CLOSURES1PHASEBASE_H

#include "ClosuresBase.h"

class Closures1PhaseBase;

template <>
InputParameters validParams<Closures1PhaseBase>();

/**
 * Base class for 1-phase closures
 */
class Closures1PhaseBase : public ClosuresBase
{
public:
  Closures1PhaseBase(const InputParameters & params);

protected:
  /**
   * Adds material that computes wall friction factor from a specified function
   *
   * This function assumes that the flow channel component has the parameter
   * 'f' as a valid parameter, so this function should be guarded appropriately.
   *
   * @param[in] flow_channel   Flow channel component
   */
  void addWallFrictionFunctionMaterial(const Pipe & flow_channel) const;
};

#endif /* CLOSURES1PHASEBASE_H */
