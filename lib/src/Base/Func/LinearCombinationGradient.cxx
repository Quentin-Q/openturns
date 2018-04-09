//                                               -*- C++ -*-
/**
 *  @brief The gradient part of linear combination of polynomials
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
#include "openturns/LinearCombinationGradient.hxx"
#include "openturns/OSS.hxx"
#include "openturns/PersistentObjectFactory.hxx"

BEGIN_NAMESPACE_OPENTURNS



CLASSNAMEINIT(LinearCombinationGradient)

static const Factory<LinearCombinationGradient> Factory_LinearCombinationGradient;


/* Default constructor */
LinearCombinationGradient::LinearCombinationGradient()
  : GradientImplementation()
  , p_evaluation_()
{
  // Nothing to do
}


/* Parameters constructor */
LinearCombinationGradient::LinearCombinationGradient(const LinearCombinationEvaluation & evaluation)
  : GradientImplementation()
  , p_evaluation_(evaluation.clone())
{
  // Nothing to do
}

/* Parameters constructor */
LinearCombinationGradient::LinearCombinationGradient(const Pointer<LinearCombinationEvaluation> & p_evaluation)
  : GradientImplementation()
  , p_evaluation_(p_evaluation)
{
  // Nothing to do
}

/* Virtual constructor */
LinearCombinationGradient * LinearCombinationGradient::clone() const
{
  return new LinearCombinationGradient(*this);
}


/* Gradient method */
Matrix LinearCombinationGradient::gradient(const Point & inP) const
{
  const UnsignedInteger inputDimension = getInputDimension();
  if (inP.getDimension() != inputDimension) throw InvalidArgumentException(HERE) << "Error: the given point has an invalid dimension. Expect a dimension " << inputDimension << ", got " << inP.getDimension();
  const UnsignedInteger size = p_evaluation_->functionsCollection_.getSize();
  Matrix result(p_evaluation_->getInputDimension(), p_evaluation_->getOutputDimension());
  for (UnsignedInteger i = 0; i < size; ++i) result = result + p_evaluation_->coefficients_[i] * p_evaluation_->functionsCollection_[i].gradient(inP);
  return result;
}

/* Accessor for input point dimension */
UnsignedInteger LinearCombinationGradient::getInputDimension() const
{
  return p_evaluation_->getInputDimension();
}

/* Accessor for output point dimension */
UnsignedInteger LinearCombinationGradient::getOutputDimension() const
{
  return p_evaluation_->getOutputDimension();
}

/* String converter */
String LinearCombinationGradient::__repr__() const
{
  return OSS(true) << "class=" << GetClassName()
         << " evaluation=" << *p_evaluation_;
}

String LinearCombinationGradient::__str__(const String & offset) const
{
  OSS oss(false);
  oss << offset;
  const UnsignedInteger size = p_evaluation_->functionsCollection_.getSize();
  for (UnsignedInteger i = 0; i < size; ++i) oss << (i > 0 ? "+" : "") << "(" << p_evaluation_->coefficients_[i] << ")*" << p_evaluation_->functionsCollection_[i].getGradient().__str__();
  return oss;
}

/* Method save() stores the object through the StorageManager */
void LinearCombinationGradient::save(Advocate & adv) const
{
  PersistentObject::save(adv);
  adv.saveAttribute( "evaluation_", *p_evaluation_ );
}


/* Method load() reloads the object from the StorageManager */
void LinearCombinationGradient::load(Advocate & adv)
{
  PersistentObject::load(adv);
  TypedInterfaceObject<LinearCombinationEvaluation> evaluation;
  adv.loadAttribute( "evaluation_", evaluation );
  p_evaluation_ = evaluation.getImplementation();
}



END_NAMESPACE_OPENTURNS
