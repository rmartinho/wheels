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

// Boolean negation meta-function

#ifndef WHEELS_META_NOT_HPP
#define WHEELS_META_NOT_HPP

#include <wheels/meta/bool.h++>

namespace wheels {
    namespace meta {
        // Boolean negation meta-function
        // *Returns*: a meta-constant with the negated value of `T`.
        template <typename T>
        using Not = Bool<not T::value>;
    } // namespace meta
} // namespace wheels

#endif // WHEELS_META_NOT_HPP

