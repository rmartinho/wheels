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

// `int` meta-constants

#ifndef WHEELS_META_INT_HPP
#define WHEELS_META_INT_HPP

#include <wheels/meta/constant.h++>

namespace wheels {
    namespace meta {
        // `int` meta-constant
        template <int I>
        using Int = constant<int, I>;
    } // namespace meta
} // namespace wheels

#endif // WHEELS_META_INT_HPP

