#ifndef FUNCTIONAL_FUNCTIONALUTIL_H
#define FUNCTIONAL_FUNCTIONALUTIL_H

#include <utility>
#include <vector>

template <typename T>
inline bool isMonotonic(const std::vector<T>& values) {
  for (size_t i = 1; i < values.size(); i++) {
    if (values[i] < values[i - 1]) {
      return false;
    }
  }
  return true;
}

template <typename Rhs, typename Lhs>
using ProductType = decltype((Rhs) 0 * (Lhs) 0);

template <typename Function, typename Arg> // TODO: variadic?
using ResultType = decltype(std::declval<Function>().operator() (std::declval<Arg>()));


#endif // FUNCTIONAL_FUNCTIONALUTIL_H