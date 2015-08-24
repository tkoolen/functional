//
// Created by Twan Koolen on 5/9/15.
//

#ifndef FUNCTIONAL_SUM_H
#define FUNCTIONAL_SUM_H

#include <utility>

template<typename T1, typename T2>
class Sum
{
private:
  T1 t1;
  T2 t2;

public:
  Sum(const T1& t1, const T2& t2) :
      t1(t1), t2(t2)
  {
    // empty
  }

  template<typename From>
  auto operator()(From&& from) const -> decltype(t1(std::forward<From>(from)) + t2(std::forward<From>(from)))
  {
    return t1(std::forward<From>(from)) + t2(std::forward<From>(from));
  }

  template<typename Q1 = T1, typename Q2 = T2, typename std::enable_if<is_differentiable<Q1>::value && is_differentiable<Q2>::value>::type* = nullptr>
  auto derivative() const -> Sum<decltype(std::declval<Q1>().derivative()), decltype(std::declval<Q2>().derivative())>
  {
    return Sum<decltype(t1.derivative()), decltype(t2.derivative())>(t1.derivative(), t2.derivative());
  }
};

#endif //FUNCTIONAL_SUM_H
