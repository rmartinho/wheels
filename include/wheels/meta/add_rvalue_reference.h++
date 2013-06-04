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

// Add rvalue reference qualifier

#ifndef WHEELS_META_ADD_RVALUE_REFERENCE_HPP
#define WHEELS_META_ADD_RVALUE_REFERENCE_HPP

#include <wheels/meta/invoke.h++>

#include <type_traits> // add_rvalue_reference

namespace wheels {
    namespace meta {
        // Adds rvalue reference qualifier
        template <typename T>
        using AddRvalueReference = Invoke<std::add_rvalue_reference<T>>;
    } // namespace meta
} // namespace wheels

#endif // WHEELS_META_ADD_RVALUE_REFERENCE_HPP

