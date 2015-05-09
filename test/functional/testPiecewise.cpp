#include <Functional.h>
#include <testUtil.h>
#include <iostream>

using namespace std;
using namespace Eigen;

default_random_engine engine;

template <typename BreakType>
Piecewise<Polynomial<double>, BreakType> createTestPiecewisePolynomial() {
  vector<double> breaks = {(BreakType) 1, (BreakType) 2, (BreakType) 3};
  vector<Polynomial<double>> functions;
  int num_coeffs = 3;
  for (int i = 1; i < breaks.size(); ++i) {
    auto poly = Polynomial<double>(VectorXd::Random(num_coeffs));
    functions.push_back(poly);
  }
  return Piecewise<Polynomial<double>, BreakType>(breaks, functions);
}

template<typename Scalar>
void testConstantValue() {
  normal_distribution<Scalar> distribution;
  Scalar constant = distribution(engine);
  auto val = [&] (Scalar arg) {return constant;};
  Piecewise<function<Scalar(Scalar)>, Scalar> piecewise_constant(val);
  valueCheck(constant, piecewise_constant(distribution(engine)));
}

template <typename Arg, typename F, typename BreakType>
void testIntegralAndDerivative(const Piecewise<F, BreakType>& piecewise, const Arg& value_at_start_time) {
  // differentiate integral, get original back

  auto piecewise_integral = integral(piecewise, value_at_start_time);
  Piecewise<F, BreakType> piecewise_back = weakDerivative(piecewise_integral);
  uniform_real_distribution<Arg> distribution(piecewise.domainStart(), piecewise.domainEnd());
  Arg arg = distribution(engine);
  valueCheck(piecewise(arg), piecewise_back(arg), 1e-8 * (Arg) 1);

  valueCheck(value_at_start_time, piecewise_integral(piecewise.domainStart()),  1e-8 * (Arg) 1);

  // check continuity at knot points
  for (int i = 0; i < piecewise.numberOfSegments() - 1; ++i) {
    const auto& f_this = (piecewise_integral.getSubfunction(i));
    const auto& f_next = piecewise_integral.getSubfunction(i + 1);
    valueCheck(f_this(piecewise_integral.segmentEnd(i) - piecewise_integral.segmentStart(i)), f_next(0.0), 1e-8 * (Arg) 1);
  }
}

template <typename Scalar>
void testPiecewisePolynomial() {
  auto piecewise_polynomial = createTestPiecewisePolynomial<Scalar>();

  uniform_real_distribution<Scalar> distribution(piecewise_polynomial.domainStart(), piecewise_polynomial.domainEnd());
  Scalar t = distribution(engine);

  valueCheck(piecewise_polynomial.domainStart(), piecewise_polynomial.segmentStart(0));
  valueCheck(piecewise_polynomial.domainEnd(), piecewise_polynomial.segmentEnd(piecewise_polynomial.numberOfSegments() - 1));
  // TODO: test more

  std::normal_distribution<Scalar> normal;
  Scalar value_at_start_time = normal(engine);
  testIntegralAndDerivative<double>(createTestPiecewisePolynomial<double>(), value_at_start_time);
}

//template <typename Scalar>
//void testPiecewisePolynomialMatrix() {
//
//}

int main (int argc, char *argv[])
{
  testConstantValue<double>();
  testPiecewisePolynomial<double>();
//  testPiecewisePolynomialMatrix<float>();

  std::cout << is_differentiable<double>::value << std::endl;
  std::cout << is_differentiable<Polynomial<double>>::value << std::endl;
}
