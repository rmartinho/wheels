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

// Const and volatile qualifier propagation

#ifndef WHEELS_META_QUALIFYING_CV_OF_HPP
#define WHEELS_META_QUALIFYING_CV_OF_HPP

#include <wheels/meta/invoke.h++>
#include <wheels/meta/qualifying_const_of.h++>
#include <wheels/meta/qualifying_volatile_of.h++>

namespace wheels {
    namespace meta {
        // Propagates the `const` and `volatile` qualifiers of `From` to `To`.
        template <typename From, typename To>
        struct qualifying_cv_of : qualifying_volatile_of<From, QualifyingConstOf<From, To>> {};
        using QualifyingCvOf = Invoke<qualifying_cv_of<From, To>>;
    } // namespace meta
} // namespace wheels

#endif // WHEELS_META_QUALIFYING_CV_OF_HPP

