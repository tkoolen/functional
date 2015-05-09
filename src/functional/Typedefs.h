//
// Created by Twan Koolen on 5/9/15.
//

#ifndef FUNCTIONAL_TYPEDEFS_H
#define FUNCTIONAL_TYPEDEFS_H

#include <utility>

template <typename Rhs, typename Lhs>
using ProductType = decltype((Rhs) 0 * (Lhs) 0);

template <typename Function, typename Arg> // TODO: variadic?
using ResultType = decltype(std::declval<Function>().operator() (std::declval<Arg>()));

#endif //FUNCTIONAL_TYPEDEFS_H
