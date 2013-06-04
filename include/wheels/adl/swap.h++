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

// ADL-enabled swap

#ifndef WHEELS_ADL_SWAP_HPP
#define WHEELS_ADL_SWAP_HPP

#include <utility> // swap, declval

namespace wheels {
    namespace adl {
        namespace detail {
            using std::swap;
            template <typename T, typename U,
                      typename Result = decltype(swap(std::declval<T>(), std::declval<U>())),
                      bool NoExcept = noexcept(swap(std::declval<T>(), std::declval<U>()))>
            Result adl_swap(T&& t, U&& u) noexcept(NoExcept) {
                return swap(std::forward<T>(t), std::forward<U>(u));
            }
        } // namespace detail

        // Calls swap with ADL-lookup include std::swap
        template <typename T, typename U,
                  typename Result = decltype(detail::adl_swap(std::declval<T>(), std::declval<U>())),
                  bool NoExcept = noexcept(detail::adl_swap(std::declval<T>(), std::declval<U>()))>
        Result swap(T&& t, U&& u) noexcept(NoExcept) {
            return detail::adl_swap(std::forward<T>(t), std::forward<U>(u));
        }
    } // namespace adl
} // namespace wheels

#endif // WHEELS_ADL_SWAP_HPP

