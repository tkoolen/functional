#include <Functional.h>
#include <testUtil.h>

using namespace std;
using namespace Eigen;

default_random_engine engine;

template<typename Scalar>
void testConstantValue() {
  normal_distribution<Scalar> distribution;
  Scalar constant = distribution(engine);
//  auto val = [&] (Scalar arg) {return constant;};
//  Piecewise<function<Scalar(Scalar)>, Scalar> piecewise_constant(val);
//  valueCheck(constant, piecewise_constant(distribution(engine)));
}

template <typename Scalar>
void testPiecewisePolynomial() {
  vector<double> breaks = {(Scalar) 1, (Scalar) 2, (Scalar) 3};
  vector<Polynomial<double>> functions;
  int num_coeffs = 3;
  for (int i = 1; i < breaks.size(); ++i) {
    auto poly = Polynomial<double>(VectorXd::Random(num_coeffs));
    functions.push_back(poly);
  }
  Piecewise<Polynomial<double>, double> piecewise_polynomial
          (breaks, functions);

  uniform_real_distribution<Scalar> distribution(piecewise_polynomial.domainStart(), piecewise_polynomial.domainEnd());
  Scalar t = distribution(engine);
  cout << piecewise_polynomial(t) << endl;
}

int main (int argc, char *argv[])
{
  testPiecewisePolynomial<double>();
  testConstantValue<double>();
}