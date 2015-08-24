//
// Created by Twan Koolen on 8/24/15.
//
#include "Functional.h"
#include <iostream>


using namespace std;
using namespace Eigen;

void testDifferentiability() {
  typedef Polynomial<double> Polynomiald;
  static_assert(!is_differentiable<Piecewise<Polynomiald>>::value, "failed");
  static_assert(is_differentiable<Polynomiald>::value, "failed");
  static_assert(is_differentiable<Linear<double, 4, 5>>::value, "failed");
  static_assert(is_differentiable<Constant<double, 4, 5>>::value, "failed");
  static_assert(is_differentiable<Sum<Polynomiald, Polynomiald>>::value, "failed");
  static_assert(!is_differentiable<Sum<Polynomiald, Piecewise<Polynomiald>>>::value, "failed");
  decltype(std::declval<Polynomiald>().derivative()) a;
}

int main(int argc, char **argv) {
  testDifferentiability();
}
