// Wheels - various C++ utilities
//
// Written in 2013 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Binary operator function object macro

#ifndef WHEELS_OP_DETAIL_BINARY_OP_HPP
#define WHEELS_OP_DETAIL_BINARY_OP_HPP

#include <utility> // declval, forward

#define WHEELS_BINARY_OP_FUNOBJ(NAME, OP)                                               \
    struct NAME {                                                                       \
        template <typename T, typename U,                                               \
                  typename Result = decltype(std::declval<T>() OP std::declval<U>()),   \
                  bool NoExcept = noexcept(std::declval<T>() OP std::declval<U>())>     \
        Result operator()(T&& t, U&& u) const noexcept(NoExcept) {                      \
            return std::forward<T>(t) OP std::forward<U>(u);                            \
        }                                                                               \
    }

#endif // WHEELS_OP_DETAIL_BINARY_OP_HPP

