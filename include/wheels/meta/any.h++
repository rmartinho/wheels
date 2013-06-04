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

// Boolean disjunction meta-function

#ifndef WHEELS_META_ANY_HPP
#define WHEELS_META_ANY_HPP

#include <wheels/meta/bool.h++>
#include <wheels/meta/if.h++>

namespace wheels {
    namespace meta {
        // Boolean disjunction meta-function
        // *Returns*: `True` if any `T::value` is `true`; `False` otherwise.
        template <typename... T>
        struct Any : False {};
        template <typename H, typename... T>
        struct Any<H, T...> : If<H, True, Any<T...>> {};
    } // namespace meta
} // namespace wheels

#endif // WHEELS_META_ANY_HPP

