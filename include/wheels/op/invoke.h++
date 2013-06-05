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

// invoke() function object

#ifndef WHEELS_OP_INVOKE_HPP
#define WHEELS_OP_INVOKE_HPP

#include <wheels/fun/invoke.h++>

#include <utility> // declval, forward

namespace wheels {
    namespace op {
        struct invoke {
            template <typename... T>
            auto operator()(T&&... t) -> decltype(fun::invoke(std::declval<T>()...)) {
                return fun::invoke(std::forward<T>(t)...);
            }
        };
    } // namespace op
} // namespace wheels

#endif // WHEELS_OP_INVOKE_HPP

