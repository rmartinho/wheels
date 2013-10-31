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

// swap() function object

#ifndef WHEELS_OP_SWAP_HPP
#define WHEELS_OP_SWAP_HPP

#include <wheels/adl/swap.h++>

#include <utility> // declval, forward

namespace wheels {
    namespace op {
        struct swap {
            template <typename T, typename U>
            auto operator()(T&& t, U&& u) const
            noexcept(noexcept(adl::swap(std::declval<T>(), std::declval<U>())))
            -> decltype(adl::swap(std::declval<T>(), std::declval<U>())) {
                return adl::swap(std::forward<T>(t), std::forward<U>(u));
            }
        };
    } // namespace op
} // namespace wheels

#endif // WHEELS_OP_SWAP_HPP

