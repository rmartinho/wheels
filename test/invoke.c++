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

// INVOKE tests

#include <wheels/fun/invoke.h++>

#include <catch.h++>

TEST_CASE("invoke", "INVOKE tests") {
    struct local { int i; } l;
    wheels::fun::invoke<void>(&local::i, local{0});
    CHECK(wheels::fun::invoke<double>(&local::i, local{0}) == 0.0);
    CHECK(&wheels::fun::invoke(&local::i, l) == &l.i);
}

