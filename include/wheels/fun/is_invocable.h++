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

// INVOKE protocol test

#ifndef WHEELS_FUN_IS_INVOCABLE_HPP
#define WHEELS_FUN_IS_INVOCABLE_HPP

#include <wheels/fun/invoke.h++>

#include <wheels/meta/bool.h++>
#include <wheels/meta/void.h++>

#include <utility> // declval

namespace wheels {
    namespace fun {
        // *Returns*: `True` if `Fun` is callable with signature `Sig`.
        template <typename Fun, typename Sig,
                  typename Sfinae = void>
        struct is_invocable : meta::False {};
        template <typename Fun, typename Ret, typename... Args>
        struct is_invocable<Fun, Ret(Args...),
                            meta::Void<decltype((invoke<Ret>)(std::declval<Fun>(), std::declval<Args>()...))>>
        : meta::True {};
    } // namespace fun
} // namespace wheels

#endif // WHEELS_FUN_IS_INVOCABLE_HPP

