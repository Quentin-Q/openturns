//                                               -*- C++ -*-
/**
 *  @brief SimulatedAnnealingLHS
 *
 *  Copyright 2005-2018 Airbus-EDF-IMACS-Phimeca
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef OPENTURNS_SIMULATEDANNEALINGLHS_HXX
#define OPENTURNS_SIMULATEDANNEALINGLHS_HXX

#include "openturns/TemperatureProfile.hxx"
#include "openturns/GeometricProfile.hxx"
#include "openturns/SpaceFilling.hxx"
#include "openturns/SpaceFillingMinDist.hxx"
#include "openturns/OptimalLHSExperiment.hxx"

namespace OT
{

/**
 * @class SimulatedAnnealingLHS
 *
 * SimulatedAnnealingLHS is the algorithm used for LHS optimisation
 */
class OT_API SimulatedAnnealingLHS
  : public OptimalLHSExperiment
{
  CLASSNAME

public:

  typedef Collection<LHSResult> LHSResultCollection;

  SimulatedAnnealingLHS();

  /** SimulatedAnnealingLHS */
  explicit SimulatedAnnealingLHS (const LHSExperiment & lhs,
                                  const TemperatureProfile & profile = GeometricProfile(),
                                  const SpaceFilling & spaceFilling = SpaceFillingMinDist());

  /** SimulatedAnnealingLHS constructor with LHS*/
  SimulatedAnnealingLHS(const Sample & initialDesign,
                        const Distribution & distribution,
                        const TemperatureProfile & profile,
                        const SpaceFilling & spaceFilling);

  /** Virtual constructor method */
  SimulatedAnnealingLHS * clone() const;

  /** Compute design method **/
  virtual Sample generateWithWeights(Point & weightsOut) const;
  Sample generateWithRestart(UnsignedInteger nRestart) const;

  /** String converter */
  String __repr__() const;

  /** Method save() stores the object through the StorageManager */
  virtual void save(Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  virtual void load(Advocate & adv);

private:
  TemperatureProfile profile_;
  Sample standardInitialDesign_;

}; /* class SimulatedAnnealingLHS */

} /* namespace OT */

#endif /* OT_SIMULATEDANNEALINGLHS_HXX */
