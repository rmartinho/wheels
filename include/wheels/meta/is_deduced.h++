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

// Manual type deduction kit

#ifndef WHEELS_META_IS_DEDUCED_HPP
#define WHEELS_META_IS_DEDUCED_HPP

#include <type_traits> // is_same

namespace wheels {
    namespace meta {
        // Marker for deduced template parameters
        // *Remarks*: use as default argument for parameters that may need manual type deduction.
        struct deduced;
        // *Returns*: `True` if `T` is `deduced`.
        template <typename T>
        struct is_deduced : std::is_same<T, deduced> {};
    } // namespace meta
} // namespace wheels

#endif // WHEELS_META_IS_DEDUCED_HPP

