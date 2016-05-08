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

// ADL get tests

#include <wheels/adl/get.h++>

#include <catch.hpp>

#include <array>

namespace test {
    namespace {
        struct foo {};

        template <int N>
        int get(foo const&) { return N; }
    } // namespace
} // namespace test

TEST_CASE("adl/get", "adl::get tests") {
    SECTION("custom", "") {
        CHECK(wheels::adl::get<0>(test::foo{}) == 0);
        CHECK(wheels::adl::get<17>(test::foo{}) == 17);
        CHECK(wheels::adl::get<23>(test::foo{}) == 23);
        CHECK(wheels::adl::get<42>(test::foo{}) == 42);
    }
    SECTION("default", "") {
        std::array<int, 3> a = { 17, 23, 42 };
        CHECK(wheels::adl::get<0>(a) == 17);
        CHECK(wheels::adl::get<1>(a) == 23);
        CHECK(wheels::adl::get<2>(a) == 42);
    }
}

