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

// noexcept-related meta-programming facilities

#ifndef WHEELS_META_NOEXCEPT_HPP
#define WHEELS_META_NOEXCEPT_HPP

#include <wheels/meta/bool.h++>

#include <new>
#include <utility> // declval
#include <type_traits> // traits

namespace wheels {
    namespace meta {
        namespace detail {
            template <typename To>
            void nothrow_conversion_test(To) noexcept;

            template <typename From, typename To, bool = std::is_convertible<From, To>::value>
            struct is_nothrow_convertible
            : Bool<noexcept((nothrow_conversion_test<To>)(std::declval<From>()))> {};

            template <typename From, typename To>
            struct is_nothrow_convertible<From, To, false> : False {};

            template <typename From>
            struct is_nothrow_convertible<From, void, true> : True {};
        } // namespace detail

        template <typename From, typename To>
        struct is_nothrow_convertible : detail::is_nothrow_convertible<From, To> {};

        template <typename T, typename... Args>
        struct is_nothrow_placeable : Bool<noexcept(::new(std::declval<void*>()) T(std::declval<Args>()...))> {};

        template <typename T, typename... Args>
        struct is_nothrow_placeable<T&, Args...> : False {};

        template <typename T, typename... Args>
        struct is_nothrow_placeable_braced : Bool<noexcept(::new(std::declval<void*>()) T{std::declval<Args>()...})> {};

        template <typename T>
        struct is_nothrow_copy_placeable : is_nothrow_placeable<T, T const&> {};

        template <typename T>
        struct is_nothrow_move_placeable : is_nothrow_placeable<T, T&&> {};
    } // namespace meta
} // namespace wheels

#endif // WHEELS_META_NOEXCEPT_HPP

