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

// Implicit conversion function object

#ifndef WHEELS_OP_CONVERT_IMPLICIT_HPP
#define WHEELS_OP_CONVERT_IMPLICIT_HPP

#include <wheels/meta/noexcept.h++> // is_nothrow_convertible

namespace wheels {
    namespace op {
        template <typename T>
        struct convert_implicit {
            template <typename U>
            T operator()(U&& u) const noexcept(meta::is_nothrow_convertible<U, T>()) {
                return std::forward<U>(u);
            }
        };
    } // namespace op
} // namespace wheels

#endif // WHEELS_OP_CONVERT_IMPLICIT_HPP

