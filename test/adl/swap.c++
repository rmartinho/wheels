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

// ADL swap tests

#include <wheels/adl/swap.h++>

#include <catch.hpp>

namespace test {
    struct foo { int x; };

    void swap(foo& a, foo& b) { a.x += 1; b.x += 2; }
} // namespace test

TEST_CASE("adl/swap", "adl::swap tests") {
    SECTION("custom", "") {
        test::foo a = { 16 };
        test::foo b = { 21 };
        wheels::adl::swap(a, b);
        CHECK(a.x == 17);
        CHECK(b.x == 23);
    }
    SECTION("default", "") {
        int a = 17;
        int b = 23;
        wheels::adl::swap(a, b);
        CHECK(a == 23);
        CHECK(b == 17);
    }
}


