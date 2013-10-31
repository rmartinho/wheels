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

// Binary operator[] function object

#ifndef WHEELS_OP_SUBSCRIPT_HPP
#define WHEELS_OP_SUBSCRIPT_HPP

#include <utility> // declval, forward

namespace wheels {
    namespace op {
        struct subscript {
            template <typename T, typename U,
                      typename Result = decltype(std::declval<T>()[std::declval<U>()]),
                      bool NoExcept = noexcept(std::declval<T>()[std::declval<U>()])
                                   && meta::is_nothrow_returnable<Result>()>
            Result operator()(T&& t, U&& u) const noexcept(NoExcept) {
                return std::forward<T>(t)[std::forward<U>(u)];
            }
        };
    } // namespace op
} // namespace wheels

#endif // WHEELS_OP_SUBSCRIPT_HPP

