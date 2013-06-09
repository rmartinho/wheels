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

// Specialization tester

#ifndef WHEELS_META_IS_SPECIALIZATION_OF_HPP
#define WHEELS_META_IS_SPECIALIZATION_OF_HPP

#include <wheels/meta/bool.h++>

namespace wheels {
    namespace meta {
        // Tests if a type is a specialization of a template
        // *Returns*: `True` if `T` is a specialization of `Templ`; `False` otherwise.
        template <template <typename...> class Templ, typename T>
        struct is_specialization_of : meta::False {};
        template <template <typename...> class Templ, typename... T>
        struct is_specialization_of<Templ, Templ<T...>> : meta::True {};
    } // namespace meta
} // namespace wheels

#endif // WHEELS_META_IS_SPECIALIZATION_OF_HPP

