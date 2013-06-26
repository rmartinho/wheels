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

// Unqualified type tester

#ifndef WHEELS_META_IS_UNQUAL_HPP
#define WHEELS_META_IS_UNQUAL_HPP

#include <wheels/meta/unqual.h++>

#include <type_traits> // is_same

namespace wheels {
    namespace meta {
        // Tests if a type has no qualifiers
        // *Returns*: `True` if `T` has no qualifiers; `False` otherwise.
        template <typename T>
        struct is_unqual : std::is_same<T, Unqual<T>> {};
    } // namespace meta
} // namespace wheels

#endif // WHEELS_META_IS_UNQUAL_HPP

