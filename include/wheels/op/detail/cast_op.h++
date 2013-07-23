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

// Cast operator function object macro

#ifndef WHEELS_OP_DETAIL_CAST_OP_HPP
#define WHEELS_OP_DETAIL_CAST_OP_HPP

#include <utility> // declval, forward

#define WHEELS_CAST_OP_FUNOBJ(CAST)                                             \
    template <typename T>                                                       \
    struct convert_##CAST {                                                     \
        template <typename U>                                                   \
        auto operator()(U&& u) -> decltype(CAST##_cast<T>(std::declval<U>())) { \
            return CAST##_cast<T>(std::forward<U>(u));                          \
        }                                                                       \
    }

#endif // WHEELS_OP_DETAIL_CAST_OP_HPP

