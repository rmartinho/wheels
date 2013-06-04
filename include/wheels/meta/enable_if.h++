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

// Generic bool-to-substitution-failure conversion

#ifndef WHEELS_META_ENABLE_IF_HPP
#define WHEELS_META_ENABLE_IF_HPP

#include <wheels/meta/invoke.h++>
#include <wheels/meta/all.h++>
#include <wheels/meta/any.h++>

#include <type_traits> // enable_if

namespace wheels {
    namespace meta {
        namespace detail {
            // Marker for EnableIf
            enum class enabled {};
        } // namespace detail

        // Conditional overload enabler
        // *Effects*: causes a substitution failure if not all of `T...` are true.
        // *Remarks*: intended usage is as `EnableIf<F<T>, G<T>>...` in template parameter lists.
        template <typename... T>
        using EnableIf = Invoke<std::enable_if<All<T...>::value, enabled>>;
        // Conditional overload disabler
        // *Effects*: causes a substitution failure if all of `T...` are false.
        // *Remarks*: intended usage is as `DisableIf<F<T>, G<T>>...` in template parameter lists.
        template <typename... T>
        using DisableIf = Invoke<std::enable_if<Any<T...>::value, enabled>>;
    } // namespace meta
} // namespace wheels

#endif // WHEELS_META_ENABLE_IF_HPP

