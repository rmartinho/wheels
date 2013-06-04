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

// Member pointer type

#ifndef WHEELS_META_MEMBER_OF_HPP
#define WHEELS_META_MEMBER_OF_HPP

#include <wheels/meta/invoke.h++>
#include <wheels/meta/identity.h++>

namespace wheels {
    namespace meta {
        // *Returns*: the member type of this member pointer
        template <typename T>
        struct member_of {};
        template <typename Sig, typename Class>
        struct member_of<Sig Class::*> : identity<Sig> {};
        template <typename T>
        using MemberOf = Invoke<member_of<T>>;
    } // namespace meta
} // namespace wheels

#endif // WHEELS_META_MEMBER_OF_HPP


