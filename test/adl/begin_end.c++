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

// ADL begin/end tests

#include <wheels/adl/begin.h++>
#include <wheels/adl/end.h++>

#include <catch.h++>

namespace test {
    struct foo {};

    auto source = "foo";
    auto expected_begin = &source[0];
    auto expected_end = &source[3];
    char const* begin(foo const&) { return expected_begin; }
    char const* end(foo const&) { return expected_end; }
} // namespace test

namespace test2 {
    struct bar {
        char const* begin() const { return test::expected_begin; }
        char const* end() const { return test::expected_end; }
    };
} // namespace test2

TEST_CASE("adl/begin", "adl::begin tests") {
    SECTION("in namespace", "") {
        CHECK(wheels::adl::begin(test::foo{}) == test::expected_begin);
        CHECK(wheels::adl::end(test::foo{}) == test::expected_end);
    }
    SECTION("in class", "") {
        CHECK(wheels::adl::begin(test2::bar{}) == test::expected_begin);
        CHECK(wheels::adl::end(test2::bar{}) == test::expected_end);
    }
}

