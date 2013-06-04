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

// Boolean meta-constants

#ifndef WHEELS_META_BOOL_HPP
#define WHEELS_META_BOOL_HPP

#include <wheels/meta/constant.h++>

namespace wheels {
    namespace meta {
        // Boolean meta-constant
        template <bool B>
        using Bool = constant<bool, B>;
    } // namespace meta
} // namespace wheels

#endif // WHEELS_META_BOOL_HPP

