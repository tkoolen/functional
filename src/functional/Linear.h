//
// Created by Twan Koolen on 8/23/15.
//

#ifndef FUNCTIONAL_LINEAR_H
#define FUNCTIONAL_LINEAR_H

#include <Eigen/Core>
#include "FunctionalUtil.h"
#include "Constant.h"

/**
 * A * X
 */
template<typename CoefScalar, int Rows, int Cols>
class Linear
{
private:
  Eigen::Matrix<CoefScalar, Rows, Cols> A;

public:
  template <typename TScalar>
  using OutputType = Eigen::Matrix<ProductType<CoefScalar, TScalar>, Rows, 1>;

  template <typename DerivedA>
  Linear(const Eigen::MatrixBase<DerivedA>& A) :
      A(A){
    // empty
  }

  template <typename Derived>
  OutputType<Derived> operator() (const Eigen::MatrixBase<Derived>& X) const {
    return A * X;
  }

  Constant<CoefScalar, Rows, Cols> derivative() const {
    return A;
  }
};

#endif //FUNCTIONAL_LINEAR_H
