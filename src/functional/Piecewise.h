//
// Created by Twan Koolen on 5/9/15.
//

#ifndef FUNCTIONAL_PIECEWISE_H
#define FUNCTIONAL_PIECEWISE_H

#include <vector>
#include <limits>
#include "FunctionalUtil.h"

template<typename F, typename BreakType>
class Piecewise
{
public:
  template <typename T>
  using ResultType = decltype(std::declval<F>().operator() (std::declval<T>()));

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

  template <typename T>
  ResultType<T> operator()(const T &from) {
    size_t segment_index = segmentIndex(from);
    return functions[segment_index](from - breaks[segment_index]);
  }

  size_t numberOfSegments() {
    return functions.size();
  }

  size_t segmentIndex(const BreakType &arg) {
    assert(inDomain(arg));
    size_t segment_index = 0;
    // TODO: something smarter than this linear search
    while (segment_index < numberOfSegments() - 1)
      segment_index++;
    return segment_index;
  }

  inline const BreakType& domainStart() {
    return breaks[0];
  }

  inline const BreakType& domainEnd() {
    return breaks[numberOfSegments()];
  }

  inline bool inDomain(const BreakType &arg) {
    return arg >= breaks[0] && arg <= breaks[numberOfSegments()];
  }

private:
  Piecewise() {};
};

#endif //FUNCTIONAL_PIECEWISE_H
