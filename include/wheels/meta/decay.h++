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

// Value decay

#ifndef WHEELS_META_DECAY_HPP
#define WHEELS_META_DECAY_HPP

#include <wheels/meta/invoke.h++>

#include <type_traits> // decay
#include <utility> // forward

namespace wheels {
    namespace meta {
        // Simulates pass-by-value decay semantics
        template <typename T>
        using Decay = Invoke<std::decay<T>>;

        // Forces value decay
        template <typename T>
        Decay<T> decay(T&& t) {
            return std::forward<T>(t);
        }
    } // namespace meta
} // namespace wheels

#endif // WHEELS_META_DECAY_HPP

