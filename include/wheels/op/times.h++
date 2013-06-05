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

// Binary operator* function object

#ifndef WHEELS_OP_TIMES_HPP
#define WHEELS_OP_TIMES_HPP

#include <wheels/op/detail/binary_op.h++>

namespace wheels {
    namespace op {
        WHEELS_BINARY_OP_FUNOBJ(times, *);
    } // namespace op
} // namespace wheels

#endif // WHEELS_OP_TIMES_HPP

