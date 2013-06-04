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

// Boolean conjunction meta-function

#ifndef WHEELS_META_ALL_HPP
#define WHEELS_META_ALL_HPP

#include <wheels/meta/invoke.h++>
#include <wheels/meta/bool.h++>
#include <wheels/meta/if.h++>

namespace wheels {
    namespace meta {
        // Boolean conjunction meta-function
        // *Returns*: `True` if all `T::value` are `true`; `False` otherwise.
        template <typename... T>
        struct all : True {};
        template <typename H, typename... T>
        struct all<H, T...> : If<H, All<T...>, False> {};
        template <typename... T>
        using All = Invoke<all<T...>>;
    } // namespace meta
} // namespace wheels

#endif // WHEELS_META_ALL_HPP

