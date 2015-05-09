//
// Created by Twan Koolen on 5/9/15.
//

#ifndef FUNCTIONAL_TYPEDEFS_H
#define FUNCTIONAL_TYPEDEFS_H

template <typename Rhs, typename Lhs>
using ProductType = decltype((Rhs) 0 * (Lhs) 0);

#endif //FUNCTIONAL_TYPEDEFS_H
