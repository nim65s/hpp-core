// Copyright (c) 2015, LAAS-CNRS
// Authors: Joseph Mirabel (joseph.mirabel@laas.fr)
//
// This file is part of hpp-core.
// hpp-core is free software: you can redistribute it
// and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version
// 3 of the License, or (at your option) any later version.
//
// hpp-core is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Lesser Public License for more details.  You should have
// received a copy of the GNU Lesser General Public License along with
// hpp-core. If not, see <http://www.gnu.org/licenses/>.

#include "hpp/core/numerical-constraint.hh"

#include <hpp/constraints/differentiable-function.hh>

namespace hpp {
  namespace core {
    NumericalConstraint::NumericalConstraint (const DifferentiableFunctionPtr_t& function,
        ComparisonTypePtr_t comp) :
      Equation (comp, vector_t::Zero (function->outputSize ())),
      function_ (function), value_ (function->outputSize ()),
      jacobian_ (matrix_t (function->outputSize (), function->inputDerivativeSize ()))
    {}

    NumericalConstraint::NumericalConstraint (const DifferentiableFunctionPtr_t& function,
        ComparisonTypePtr_t comp, vectorIn_t rhs) :
      Equation (comp, rhs), function_ (function), value_ (function->outputSize ()),
      jacobian_ (matrix_t (function->outputSize (), function->inputDerivativeSize ()))
    {}

    NumericalConstraintPtr_t NumericalConstraint::create (
        const DifferentiableFunctionPtr_t& function, ComparisonTypePtr_t comp)
    {
      NumericalConstraintPtr_t sh (new NumericalConstraint (function, comp));
      return sh;
    }

    NumericalConstraintPtr_t NumericalConstraint::create (
        const DifferentiableFunctionPtr_t& function,
        ComparisonTypePtr_t comp, vectorIn_t rhs)
    {
      NumericalConstraintPtr_t sh (new NumericalConstraint (function, comp, rhs));
      return sh;
    }

    void NumericalConstraint::rightHandSideFromConfig (ConfigurationIn_t config)
    {
      if (rhsSize () > 0) {
        assert (rhsSize () == function_->outputSize ());
        (*function_) (nonConstRightHandSide (), config);
      }
    }

    DifferentiableFunction& NumericalConstraint::function () const
    {
      return *function_;
    }
  } // namespace core
} // namespace hpp