//
// Created by Twan Koolen on 5/9/15.
//

#ifndef FUNCTIONAL_LTIHOMOGENEOUSSOLUTION_H
#define FUNCTIONAL_LTIHOMOGENEOUSSOLUTION_H

#include <Eigen/Core>
#include "FunctionalUtil.h"

/**
 * K * exp(A * t) * x0
 */
template<typename CoefScalar, int NumStates, int NumOutputs>
class LTIHomogeneousSolution
{
private:
  Eigen::Matrix<CoefScalar, NumOutputs, NumStates> K;
  Eigen::Matrix<CoefScalar, NumStates, NumStates> A;
  Eigen::Matrix<CoefScalar, NumStates, 1> x0;

public:
  template <typename TScalar>
  using OutputType = Eigen::Matrix<ProductType<CoefScalar, TScalar>, NumOutputs, 1>;

  template <typename DerivedK, typename DerivedA, typename Derivedx0>
  LTIHomogeneousSolution(const Eigen::MatrixBase<DerivedK>& K, const Eigen::MatrixBase<DerivedA>& A, const Eigen::MatrixBase<Derivedx0>& x0) :
          K(K), A(A), x0(x0) {
    assert(K.cols() == A.rows());
    assert(A.rows() == A.cols());
    assert(x0.rows() == A.cols());
  }

  template <typename TScalar>
  OutputType<TScalar> operator() (const TScalar& t) const {
    auto exponential = (A * t).eval().exp().eval();
    auto exponential_times_x0 = (exponential * x0).eval();
    return K * exponential_times_x0;
  }

  Eigen::DenseIndex rows() const {
    return K.rows();
  }

  Eigen::DenseIndex cols() const {
    return 1;
  }
};


#endif //FUNCTIONAL_LTIHOMOGENEOUSSOLUTION_H
