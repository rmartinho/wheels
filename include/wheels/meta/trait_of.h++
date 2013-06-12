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

// Trait builder

#ifndef WHEELS_META_TRAIT_OF_HPP
#define WHEELS_META_TRAIT_OF_HPP

namespace wheels {
    namespace meta {
        template <typename Test, typename... T>
        using TraitOf = decltype(Test::template test<T...>(0));
    } // namespace meta
} // namespace wheels

#endif // WHEELS_META_TRAIT_OF_HPP

