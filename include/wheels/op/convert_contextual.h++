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

// Contextual conversion function object

#ifndef WHEELS_OP_CONVERT_CONTEXTUAL_HPP
#define WHEELS_OP_CONVERT_CONTEXTUAL_HPP

#include <wheels/op/convert_static.h++>

#include <type_traits> // is_same

namespace wheels {
    namespace op {
        template <typename T>
        struct convert_contextual : public convert_static<T> {
            static_assert(std::is_same<T, bool>(), "can only perform contextual conversions to bool");
        };
    } // namespace op
} // namespace wheels

#endif // WHEELS_OP_CONVERT_CONTEXTUAL_HPP

