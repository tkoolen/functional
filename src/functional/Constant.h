//
// Created by Twan Koolen on 8/23/15.
//

#ifndef FUNCTIONAL_CONSTANT_H
#define FUNCTIONAL_CONSTANT_H

/**
 * A
 */
template<typename CoefScalar, int Rows, int Cols>
class Constant
{
private:
  Eigen::Matrix<CoefScalar, Rows, Cols> A;

public:
  template<typename TScalar>
  using OutputType = const decltype(A)&;

  template<typename DerivedA>
  Constant(const Eigen::MatrixBase<DerivedA>& A) :
      A(A)
  {
    // empty
  }

  template<typename Derived>
  OutputType<Derived> operator()(const Eigen::MatrixBase<Derived>& X) const
  {
    return A;
  }

  Constant derivative() const
  {
    return Constant(Eigen::Matrix<CoefScalar, Rows, Cols>::Zero(A.rows(), A.cols()));
  }
};

#endif //FUNCTIONAL_CONSTANT_H
