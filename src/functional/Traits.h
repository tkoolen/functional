//
// Created by Twan Koolen on 5/9/15.
//

#ifndef FUNCTIONAL_TRAITS_H
#define FUNCTIONAL_TRAITS_H

#include <type_traits>

template <typename T>
struct is_differentiable
{
  template <class, class> class checker;

  template <typename C>
  static std::true_type test(checker<C, decltype(&C::derivative)> *);

  template <typename C>
  static std::false_type test(...);

  typedef decltype(test<T>(nullptr)) type;
  static const bool value = std::is_same<std::true_type, decltype(test<T>(nullptr))>::value;
};

#endif //FUNCTIONAL_TRAITS_H
