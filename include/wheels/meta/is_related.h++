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

// Related types

#ifndef WHEELS_META_IS_RELATED_HPP
#define WHEELS_META_IS_RELATED_HPP

#include <wheels/meta/unqual.h++>

#include <type_traits> // is_same

namespace wheels {
    namespace meta {
        // Tests if two types have the same core type.
        // *Returns*: `True` if `T` and `U` are the same when unqualified.
        template <typename T, typename U>
        struct is_related : std::is_same<Unqual<T>, Unqual<U>> {};
    } // namespace meta
} // namespace wheels

#endif // WHEELS_META_IS_RELATED_HPP

