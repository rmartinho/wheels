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

// optional tests

#include <wheels/optional.h++>

#include <catch.hpp>

TEST_CASE("optional", "optional tests") {
    wheels::optional<int> o1;
    CHECK(!o1);
    wheels::optional<int> o2 = 42;
    CHECK(bool(o2));
    CHECK(*o2 == 42);

    wheels::optional<int> o3 = o2;
    CHECK(bool(o3));
    CHECK(*o3 == 42);

    o3 = wheels::none;
    CHECK(!o3);

    o3 = o2;
    CHECK(bool(o3));
    CHECK(*o3 == 42);

    wheels::optional<int> o4 = 23;
    o3 = o4;
    CHECK(bool(o3));
    CHECK(*o3 == 23);
}

TEST_CASE("optional-ref", "optional tests") {
    int x = 17;
    int y = 23;

    wheels::optional<int&> o1;
    CHECK(!o1);
    wheels::optional<int&> o2 = x;
    CHECK(bool(o2));
    CHECK(&*o2 == &x);

    wheels::optional<int&> o3 = o2;
    CHECK(bool(o3));
    CHECK(&*o3 == &x);

    o3 = wheels::none;
    CHECK(!o3);

    o3 = o2;
    CHECK(bool(o3));
    CHECK(&*o3 == &x);

    wheels::optional<int&> o4 = y;
    o3 = o4;
    CHECK(bool(o3));
    CHECK(&*o3 == &y);

    REQUIRE(x == 17);
    REQUIRE(y == 23);
}

