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

// Volatile qualifier propagation

#ifndef WHEELS_META_QUALIFYING_VOLATILE_OF_HPP
#define WHEELS_META_QUALIFYING_VOLATILE_OF_HPP

#include <wheels/meta/id.h++>
#include <wheels/meta/invoke.h++>
#include <wheels/meta/if.h++>

#include <type_traits> // is_volatile, add_volatile

namespace wheels {
    namespace meta {
        // Propagates the `volatile` qualifier of `From` to `To`.
        template <typename From, typename To>
        struct qualifying_volatile_of
        : If<std::is_volatile<From>,
                std::add_volatile<To>,
                id<To>> {};
        template <typename From, typename To>
        using QualifyingVolatileOf = Invoke<qualifying_volatile_of<From, To>>;
    } // namespace meta
} // namespace wheels

#endif // WHEELS_META_QUALIFYING_VOLATILE_OF_HPP

