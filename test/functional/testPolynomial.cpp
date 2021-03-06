#include "functional/Polynomial.h"
#include <Eigen/Core>
#include <random>
#include "testUtil.h"
#include <iostream>
#include <typeinfo>

using namespace Eigen;
using namespace std;

template <typename CoefficientType>
void testIntegralAndDerivative() {
  VectorXd coefficients = VectorXd::Random(5);
  Polynomial<CoefficientType> poly(coefficients);
  Polynomial<CoefficientType> third_derivative = poly.derivative(3);
  Polynomial<CoefficientType> third_derivative_check = poly.derivative().derivative().derivative();
  valueCheckMatrix(third_derivative.getCoefficients(), third_derivative_check.getCoefficients(), 1e-14);

  Polynomial<CoefficientType> tenth_derivative = poly.derivative(10);
  valueCheckMatrix(tenth_derivative.getCoefficients(), VectorXd::Zero(1), 1e-14);

  Polynomial<CoefficientType> integral = poly.integral(0.0);
  Polynomial<CoefficientType> poly_back = integral.derivative();
  valueCheckMatrix(poly_back.getCoefficients(), poly.getCoefficients(), 1e-14);
}

template <typename CoefficientType>
void testOperators() {
  int max_num_coefficients = 6;
  int num_tests = 10;
  default_random_engine generator;
  std::uniform_int_distribution<> int_distribution(1, max_num_coefficients);
  uniform_real_distribution<double> uniform;

  for (int i = 0; i < num_tests; ++i) {
    VectorXd coeff1 = VectorXd::Random(int_distribution(generator));
    Polynomial<CoefficientType> poly1(coeff1);

    VectorXd coeff2 = VectorXd::Random(int_distribution(generator));
    Polynomial<CoefficientType> poly2(coeff2);

    double scalar = uniform(generator);

    Polynomial<CoefficientType> sum = poly1 + poly2;
    Polynomial<CoefficientType> difference = poly2 - poly1;
    Polynomial<CoefficientType> product = poly1 * poly2;
    Polynomial<CoefficientType> poly1_plus_scalar = poly1 + scalar;
    Polynomial<CoefficientType> poly1_minus_scalar = poly1 - scalar;
    Polynomial<CoefficientType> poly1_scaled = poly1 * scalar;
    Polynomial<CoefficientType> poly1_div = poly1 / scalar;
    Polynomial<CoefficientType> poly1_times_poly1 = poly1;
    poly1_times_poly1 *= poly1_times_poly1;

    double t = uniform(generator);
    valueCheck(sum(t), poly1(t) + poly2(t), 1e-8);
    valueCheck(difference(t), poly2(t) - poly1(t), 1e-8);
    valueCheck(product(t), poly1(t) * poly2(t), 1e-8);
    valueCheck(poly1_plus_scalar(t), poly1(t) + scalar, 1e-8);
    valueCheck(poly1_minus_scalar(t), poly1(t) - scalar, 1e-8);
    valueCheck(poly1_scaled(t), poly1(t) * scalar, 1e-8);
    valueCheck(poly1_div(t), poly1(t) / scalar, 1e-8);
    valueCheck(poly1_times_poly1(t), poly1(t) * poly1(t), 1e-8);
  }
}

template <typename CoefficientType>
void testRoots() {
  int max_num_coefficients = 6;
  default_random_engine generator;
  std::uniform_int_distribution<> int_distribution(1, max_num_coefficients);

  int num_tests = 50;
  for (int i = 0; i < num_tests; ++i) {
    VectorXd coeffs = VectorXd::Random(int_distribution(generator));
    Polynomial<CoefficientType> poly(coeffs);
    auto roots = poly.roots();
    valueCheck<DenseIndex>(roots.rows(), poly.getDegree());
    for (int i = 0; i < roots.size(); i++) {
      auto value = poly(roots[i]);
      valueCheck(std::abs(value), 0.0, 1e-8);
    }
  }
}

void testEvalType() {
  int max_num_coefficients = 6;
  default_random_engine generator;
  std::uniform_int_distribution<> int_distribution(1, max_num_coefficients);
  VectorXd coeffs = VectorXd::Random(int_distribution(generator));
  Polynomial<double> poly(coeffs);

  auto valueIntInput = poly(1);
  valueCheck(typeid(decltype(valueIntInput)) == typeid(double), true);

  auto valueComplexInput = poly(std::complex<double>(1.0, 2.0));
  valueCheck(typeid(decltype(valueComplexInput)) == typeid(std::complex<double>), true);
}

template <typename CoefficientType>
void testPolynomialMatrix() {
  int max_matrix_rows_cols = 7;
  int num_coefficients = 6;
  default_random_engine generator;

  uniform_int_distribution<> matrix_size_distribution(1, max_matrix_rows_cols);
  int rows_A = matrix_size_distribution(generator);
  int cols_A = matrix_size_distribution(generator);
  int rows_B = cols_A;
  int cols_B = matrix_size_distribution(generator);

  auto A = Polynomial<CoefficientType>::template randomPolynomialMatrix<Dynamic, Dynamic>(num_coefficients, rows_A, cols_A);
  auto B = Polynomial<CoefficientType>::template randomPolynomialMatrix<Dynamic, Dynamic>(num_coefficients, rows_B, cols_B);
  auto C = Polynomial<CoefficientType>::template randomPolynomialMatrix<Dynamic, Dynamic>(num_coefficients, rows_A, cols_A);
  auto product = A * B; // just verify that this is possible without crashing
  auto sum = A + C;

  uniform_real_distribution<double> uniform;
  for (int row = 0; row < A.rows(); ++row) {
    for (int col = 0; col < A.cols(); ++col) {
      double t = uniform(generator);
      valueCheck(sum(row, col)(t), A(row, col)(t) + C(row, col)(t), 1e-8);
    }
  }

  C.setZero(); // this was a problem before
}

int main(int argc, char **argv) {

  testIntegralAndDerivative<double>();
  testOperators<double>();
  testRoots<double>();
  testEvalType();
  testPolynomialMatrix<double>();
  cout << "test passed" << endl;
  return 0;
}
