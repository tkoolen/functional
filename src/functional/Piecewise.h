//
// Created by Twan Koolen on 5/9/15.
//

#ifndef FUNCTIONAL_PIECEWISE_H
#define FUNCTIONAL_PIECEWISE_H

#include <vector>
#include <limits>
#include "FunctionalUtil.h"

template<typename F, typename BreakType = double>
class Piecewise
{
public:


  std::vector<BreakType> breaks; // size n + 1
  std::vector<F> functions; // size n

  Piecewise(const std::vector<BreakType> &breaks, const std::vector<F> &functions) :
          breaks(breaks), functions(functions) {
    assert(isMonotonic(breaks));
    assert(breaks.size() == functions.size() + 1);
  }

  Piecewise(const F& value) :
          breaks( {-std::numeric_limits<BreakType>::infinity(), std::numeric_limits<BreakType>::infinity()} )
  {
    functions.push_back(value);
  }

  const F& getSubfunction(size_t segment_index) {
    assert(segmentNumberInRange(segment_index));
    return functions[segment_index];
  }

  template <typename T>
  std::result_of<F(const T&)> operator()(const T &from) const {
    size_t segment_index = segmentIndex(from);
    return functions[segment_index](from - breaks[segment_index]);
  }

  size_t numberOfSegments() const {
    return functions.size();
  }

  size_t segmentIndex(const BreakType &arg) const {
    assert(inDomain(arg));
    size_t segment_index = 0;
    // TODO: something smarter than this linear search
    while (arg >= segmentEnd(segment_index) && segment_index < numberOfSegments() - 1)
      segment_index++;
    return segment_index;
  }

  inline const BreakType& domainStart() const{
    return breaks[0];
  }

  inline const BreakType& domainEnd() const {
    return breaks[numberOfSegments()];
  }

  inline const BreakType& segmentStart(size_t segment_number) const
  {
    assert(segmentNumberInRange(segment_number));
    return breaks[segment_number];
  }

  inline const BreakType& segmentEnd(size_t segment_number) const
  {
    assert(segmentNumberInRange(segment_number));
    return breaks[segment_number + 1];
  }

  inline bool inDomain(const BreakType &arg) const {
    return arg >= breaks[0] && arg <= breaks[numberOfSegments()];
  }

  inline bool segmentNumberInRange(size_t segment_number) const {
    return segment_number >= 0 && segment_number < numberOfSegments();
  }

private:
  Piecewise() {};
};

template <typename F, typename BreakType>
auto weakDerivative(const Piecewise<F, BreakType>& fun) -> Piecewise<decltype(std::declval<F>().derivative()), BreakType> {
  typedef decltype(std::declval<F>().derivative()) SubFunctionDerivativeType;
  std::vector<SubFunctionDerivativeType> subfunction_derivatives;
  subfunction_derivatives.reserve(fun.numberOfSegments());
  for (const auto &subfunction : fun.functions) {
    subfunction_derivatives.push_back(subfunction.derivative());
  }
  return Piecewise<SubFunctionDerivativeType, BreakType>(fun.breaks, subfunction_derivatives);
}

template <typename F, typename BreakType, typename T>
auto integral(const Piecewise<F, BreakType>& fun, const T& value_at_domain_start)
-> Piecewise<decltype(std::declval<F>().integral(std::declval<std::result_of<F(const T&)>>())), BreakType> {
  typedef decltype(std::declval<F>().integral(std::declval<std::result_of<F(const T&)>>())) SubFunctionIntegralType;
  std::vector<SubFunctionIntegralType> subfunction_integrals;
  subfunction_integrals.reserve(fun.numberOfSegments());
  std::result_of<F(const T&)> value_at_subfunction_domain_start = value_at_domain_start;
  for (int i = 0; i < fun.functions.size(); i++) {
    const auto &subfunction = fun.functions[i];
    subfunction_integrals.push_back(subfunction.integral(value_at_subfunction_domain_start));
    if (i != fun.functions.size() - 1) {
      value_at_subfunction_domain_start = subfunction_integrals[i](fun.segmentEnd(i) - fun.segmentStart(i));
    }
  }
  return Piecewise<SubFunctionIntegralType, BreakType>(fun.breaks, subfunction_integrals);
}

#endif //FUNCTIONAL_PIECEWISE_H
