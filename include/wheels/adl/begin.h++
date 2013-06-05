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

// ADL-enabled begin

#ifndef WHEELS_ADL_BEGIN_HPP
#define WHEELS_ADL_BEGIN_HPP

#include <iterator> // begin
#include <utility> // declval

namespace wheels {
    namespace adl {
        namespace detail {
            using std::begin;
            template <typename T,
                      typename Result = decltype(begin(std::declval<T>()))>
            Result adl_begin(T&& t) {
                return begin(std::forward<T>(t));
            }
        } // namespace detail

        // Calls swap with ADL-lookup include std::swap
        template <std::size_t I, typename T,
                  typename Result = decltype(detail::adl_begin(std::declval<T>()))>
        Result begin(T&& t) {
            return detail::adl_begin(std::forward<T>(t));
        }
    } // namespace adl
} // namespace wheels

#endif // WHEELS_ADL_BEGIN_HPP

