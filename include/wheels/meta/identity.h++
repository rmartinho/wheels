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

// Identity metafunction

#ifndef WHEELS_META_IDENTITY_HPP
#define WHEELS_META_IDENTITY_HPP

#include <wheels/meta/invoke.h++>

namespace wheels {
    namespace meta {
        // *Returns*: `T`.
        template <typename T>
        struct identity {
            using type = T;
        };

        // *Returns*: `T`.
        // *Remarks*: this alias is not deducible.
        template <typename T>
        using Identity = Invoke<identity<T>>;
    } // namespace meta
} // namespace wheels

#endif // WHEELS_META_IDENTITY_HPP

