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

// Qualifier propagation

#ifndef WHEELS_META_QUALIFYING_HPP
#define WHEELS_META_QUALIFYING_HPP

#include <wheels/meta/invoke.h++>
#include <wheels/meta/qualifying_value_category_of.h++>
#include <wheels/meta/qualifying_cv_of.h++>
#include <wheels/meta/remove_reference.h++>

namespace wheels {
    namespace meta {
        // Propagates all the qualifiers of `From` to `To`.
        template <typename From, typename To>
        struct qualifying : qualifying_value_category_of<From, QualifyingCvOf<RemoveReference<In>, To>>
        template <typename From, typename To>
        using Qualifying = Invoke<qualifying<From, To>>;
    } // namespace meta
} // namespace wheels

#endif // WHEELS_META_QUALIFYING_HPP

