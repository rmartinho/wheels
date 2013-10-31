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

// Unary operator function object macro

#ifndef WHEELS_OP_DETAIL_UNARY_OP_HPP
#define WHEELS_OP_DETAIL_UNARY_OP_HPP

#include <wheels/meta/noexcept.h++> // is_nothrow_returnable

#include <utility> // declval, forward

#define WHEELS_UNARY_OP_FUNOBJ(NAME, OP)                                \
    struct NAME {                                                       \
        template <typename T, typename U,                               \
                  typename Result = decltype(OP std::declval<U>()),     \
                  bool NoExcept = noexcept(OP std::declval<U>())        \
                              && meta::is_nothrow_returnable<Result>()> \
        Result operator()(T&& t) const noexcept(NoExcept) {             \
            return OP std::forward<T>(t);                               \
        }                                                               \
    }

#endif // WHEELS_OP_DETAIL_UNARY_OP_HPP

