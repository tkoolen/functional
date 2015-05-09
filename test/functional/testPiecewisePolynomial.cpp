#include <Functional.h>
#include <random>
#include <iostream>

using namespace std;
using namespace Eigen;

int main (int argc, char *argv[])
{
  vector<double> breaks;
  breaks.push_back(1.0);
  breaks.push_back(2.0);
  breaks.push_back(3.0);
  vector<Polynomial<double>> functions;
  int num_coeffs = 3;
  for (int i = 1; i < breaks.size(); ++i) {
    auto poly = Polynomial<double>(VectorXd::Random(num_coeffs));
    functions.push_back(poly);
  }
  Piecewise<Polynomial<double>, double> pp(breaks, functions);

  default_random_engine engine;
  uniform_real_distribution<> distribution(pp.domainStart(), pp.domainEnd());
  auto t = distribution(engine);
  cout << pp(t) << endl;
}