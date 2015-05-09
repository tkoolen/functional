//
// Created by Twan Koolen on 5/9/15.
//

#ifndef FUNCTIONAL_TYPEDEFS_H
#define FUNCTIONAL_TYPEDEFS_H

#include <Eigen/Core>
#include "Piecewise.h"
#include "Sum.h"
#include "LTIHomogeneousSolution.h"
#include "Polynomial.h"

template <typename CoefficientType, int NumStates, int NumOutputs>
using LTIPiecewisePolySolution = Piecewise<Sum<LTIHomogeneousSolution<CoefficientType, NumStates, NumOutputs>, Eigen::Matrix<Polynomial<CoefficientType>, NumStates, 1> >, CoefficientType >;

#endif //FUNCTIONAL_TYPEDEFS_H
