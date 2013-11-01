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

// INVOKE protocol result type

#ifndef WHEELS_FUN_RESULT_OF_HPP
#define WHEELS_FUN_RESULT_OF_HPP

#include <wheels/fun/invoke.h++>
#include <wheels/fun/is_invocable.h++>

#include <wheels/meta/invoke.h++>
#include <wheels/meta/id.h++>
#include <wheels/meta/bool.h++>
#include <wheels/meta/depend_on.h++>

#include <utility> // declval

namespace wheels {
    namespace fun {
        namespace detail {
            template <typename Sig, bool Invocable>
            struct result_of {};
            template <typename Fun, typename... Args>
            struct result_of<Fun(Args...), true>
            : meta::id<decltype((invoke)(std::declval<Fun>(), std::declval<Args>()...))> {};
        } // namespace detail

        // *Requires*: `Sig` is a signature type `Fun(Args...)` [hard] and `Fun` is invocable with `Args...` [soft]
        // *Returns*: the result of calling `Fun` with the given `Args...` through the INVOKE protocol.
        template <typename Sig>
        struct result_of {
            static_assert(meta::DependOn<meta::False, Sig>(), "Sig must be a signature type");
        };
        template <typename Fun, typename... Args>
       struct result_of<Fun(Args...)> : detail::result_of<Fun(Args...), is_invocable<Fun, void(Args...)>::value> {};
        template <typename Sig>
        using ResultOf = meta::Invoke<result_of<Sig>>;
    } // namespace fun
} // namespace wheels

#endif // WHEELS_FUN_RESULT_OF_HPP

