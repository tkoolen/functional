//
// Created by Twan Koolen on 5/9/15.
//

#ifndef FUNCTIONAL_TRAITS_H
#define FUNCTIONAL_TRAITS_H

#include <type_traits>

template<class T, class Enable = void>
struct is_differentiable
{
  static const bool value = false;
};

template<class T>
struct is_differentiable<T, typename std::enable_if<!std::is_void<decltype(std::declval<T>().derivative())>{}>::type>
{
  static const bool value = true;
};

#endif //FUNCTIONAL_TRAITS_H
