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

// Generic substitution-failure-to-bool conversion

#ifndef WHEELS_META_CAN_COMPUTE_HPP
#define WHEELS_META_CAN_COMPUTE_HPP

#include <wheels/meta/invoke.h++>
#include <wheels/meta/bool.h++>
#include <wheels/meta/void.h++>

namespace wheels {
    namespace meta {
        // Substitution test
        // *Returns*: `True` if `T::type` can be substituted; `False` otherwise.
        template <typename T, typename Sfinae = void>
        struct can_compute : False {};
        template <typename T>
        struct can_compute<T, Void<Invoke<T>>> : True {};
    } // namespace meta
} // namespace wheels

#endif // WHEELS_META_CAN_COMPUTE_HPP

