//
// Created by Twan Koolen on 5/9/15.
//

#ifndef FUNCTIONAL_SUM_H
#define FUNCTIONAL_SUM_H

#include <utility>

template <typename T1, typename T2>
class Sum
{
private:
  T1 t1;
  T2 t2;

public:
  Sum(const T1& t1, const T2& t2) :
          t1(t1), t2(t2){
    // empty
  }

  template <typename From>
  auto operator() (From&& from) const -> decltype(t1(std::forward<From>(from)) + t2(std::forward<From>(from))) {
    return t1(std::forward<From>(from)) + t2(std::forward<From>(from));
  }
};

#endif //FUNCTIONAL_SUM_H
