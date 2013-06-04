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

// Lazy if-then-else meta-function

#ifndef WHEELS_META_INVOKE_IF_HPP
#define WHEELS_META_INVOKE_IF_HPP

#include <wheels/meta/invoke.h++>
#include <wheels/meta/if.h++>

namespace wheels {
    namespace meta {
        // Lazy if-then-else metafunction
        // *Returns*: `Invoke<Then>` if `Condition` is true; `Invoke<Else>` otherwise.
        template <typename Condition, typename Then, typename Else>
        using InvokeIf = Invoke<If<Condition, Then, Else>>;
    } // namespace meta
} // namespace wheels

#endif // WHEELS_META_INVOKE_IF_HPP

