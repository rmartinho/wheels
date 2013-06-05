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

// Variadic side-effect expansion

#ifndef WHEELS_EXPAND_HPP
#define WHEELS_EXPAND_HPP

#include <wheels/meta/alias.h++>

#define WHEELS_EXPAND(...) \
    void(::wheels::meta::Alias<char[]> { 0, ((__VA_ARGS__), void(), 0)... })

#endif // WHEELS_EXPAND_HPP

