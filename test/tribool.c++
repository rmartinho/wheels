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

// tribool tests

#include <wheels/tribool.h++>

#include <boost/logic/tribool.hpp>

#include <catch.h++>

#define CHECK_TRIBOOL_TRUE(x) {                         \
        CHECK(::wheels::is_true((x)));                  \
        CHECK_FALSE(::wheels::is_false((x)));           \
        CHECK_FALSE(::wheels::is_indeterminate((x)));   \
    }
#define CHECK_TRIBOOL_FALSE(x) {                        \
        CHECK_FALSE(::wheels::is_true((x)));            \
        CHECK(::wheels::is_false((x)));                 \
        CHECK_FALSE(::wheels::is_indeterminate((x)));   \
    }
#define CHECK_TRIBOOL_INDETERMINATE(x) {        \
        CHECK_FALSE(::wheels::is_true((x)));    \
        CHECK_FALSE(::wheels::is_false((x)));   \
        CHECK(::wheels::is_indeterminate((x))); \
    }

TEST_CASE("tribool", "tribool tests") {
    using wheels::indeterminate;
    static_assert(!std::is_convertible<wheels::tribool, bool>(), "tribool cannot be implicitly convertible to bool");

    wheels::tribool xxx;
    SECTION("default-ctor", "") {
        wheels::tribool a;
        CHECK_TRIBOOL_FALSE(a);
    }
    SECTION("bool-ctor", "") {
        {
            wheels::tribool a = true;
            CHECK_TRIBOOL_TRUE(a);
        }
        {
            wheels::tribool a = false;
            CHECK_TRIBOOL_FALSE(a);
        }
        {
            wheels::tribool a = indeterminate;
            CHECK_TRIBOOL_INDETERMINATE(a);
        }
    }
    SECTION("negation", "") {
        {
            wheels::tribool a(true);
            CHECK_TRIBOOL_FALSE(!a);
        }
        {
            wheels::tribool a(false);
            CHECK_TRIBOOL_TRUE(!a);
        }
        {
            wheels::tribool a(indeterminate);
            CHECK_TRIBOOL_INDETERMINATE(!a);
        }
    }
    SECTION("equal", "") {
        {
            wheels::tribool a(true);
            wheels::tribool b(true);
            CHECK_TRIBOOL_TRUE(a == b);
        }
        {
            wheels::tribool a(true);
            wheels::tribool b(false);
            CHECK_TRIBOOL_FALSE(a == b);
        }
        {
            wheels::tribool a(true);
            wheels::tribool b(indeterminate);
            CHECK_TRIBOOL_INDETERMINATE(a == b);
        }
        {
            wheels::tribool a(false);
            wheels::tribool b(true);
            CHECK_TRIBOOL_FALSE(a == b);
        }
        {
            wheels::tribool a(false);
            wheels::tribool b(false);
            CHECK_TRIBOOL_TRUE(a == b);
        }
        {
            wheels::tribool a(false);
            wheels::tribool b(indeterminate);
            CHECK_TRIBOOL_INDETERMINATE(a == b);
        }
        {
            wheels::tribool a(indeterminate);
            wheels::tribool b(true);
            CHECK_TRIBOOL_INDETERMINATE(a == b);
        }
        {
            wheels::tribool a(indeterminate);
            wheels::tribool b(false);
            CHECK_TRIBOOL_INDETERMINATE(a == b);
        }
        {
            wheels::tribool a(indeterminate);
            wheels::tribool b(indeterminate);
            CHECK_TRIBOOL_INDETERMINATE(a == b);
        }
    }
    SECTION("not-equal", "") {
        {
            wheels::tribool a(true);
            wheels::tribool b(true);
            CHECK_TRIBOOL_FALSE(a != b);
        }
        {
            wheels::tribool a(true);
            wheels::tribool b(false);
            CHECK_TRIBOOL_TRUE(a != b);
        }
        {
            wheels::tribool a(true);
            wheels::tribool b(indeterminate);
            CHECK_TRIBOOL_INDETERMINATE(a != b);
        }
        {
            wheels::tribool a(false);
            wheels::tribool b(true);
            CHECK_TRIBOOL_TRUE(a != b);
        }
        {
            wheels::tribool a(false);
            wheels::tribool b(false);
            CHECK_TRIBOOL_FALSE(a != b);
        }
        {
            wheels::tribool a(false);
            wheels::tribool b(indeterminate);
            CHECK_TRIBOOL_INDETERMINATE(a != b);
        }
        {
            wheels::tribool a(indeterminate);
            wheels::tribool b(true);
            CHECK_TRIBOOL_INDETERMINATE(a != b);
        }
        {
            wheels::tribool a(indeterminate);
            wheels::tribool b(false);
            CHECK_TRIBOOL_INDETERMINATE(a != b);
        }
        {
            wheels::tribool a(indeterminate);
            wheels::tribool b(indeterminate);
            CHECK_TRIBOOL_INDETERMINATE(a != b);
        }
    }
    SECTION("boost-interop", "") {
        {
            boost::tribool b = true;
            wheels::tribool a = b;
            CHECK_TRIBOOL_TRUE(a);
        }
        {
            boost::tribool b = false;
            wheels::tribool a = b;
            CHECK_TRIBOOL_FALSE(a);
        }
        {
            boost::tribool b = boost::indeterminate;
            wheels::tribool a = b;
            CHECK_TRIBOOL_INDETERMINATE(a);
        }
        {
            wheels::tribool a = true;
            boost::tribool b = a;
            CHECK(bool(b));
        }
        {
            wheels::tribool a = false;
            boost::tribool b = a;
            CHECK(bool(!b));
        }
        {
            wheels::tribool a = indeterminate;
            boost::tribool b = a;
            CHECK(boost::indeterminate(b));
        }
    }
    SECTION("and", "") {
        {
            wheels::tribool a = true;
            wheels::tribool b = true;
            CHECK_TRIBOOL_TRUE(a && b);
        }
        {
            wheels::tribool a = true;
            wheels::tribool b = false;
            CHECK_TRIBOOL_FALSE(a && b);
        }
        {
            wheels::tribool a = true;
            wheels::tribool b = indeterminate;
            CHECK_TRIBOOL_INDETERMINATE(a && b);
        }
        {
            wheels::tribool a = false;
            wheels::tribool b = true;
            CHECK_TRIBOOL_FALSE(a && b);
        }
        {
            wheels::tribool a = false;
            wheels::tribool b = false;
            CHECK_TRIBOOL_FALSE(a && b);
        }
        {
            wheels::tribool a = false;
            wheels::tribool b = indeterminate;
            CHECK_TRIBOOL_FALSE(a && b);
        }
        {
            wheels::tribool a = indeterminate;
            wheels::tribool b = true;
            CHECK_TRIBOOL_INDETERMINATE(a && b);
        }
        {
            wheels::tribool a = indeterminate;
            wheels::tribool b = false;
            CHECK_TRIBOOL_FALSE(a && b);
        }
        {
            wheels::tribool a = indeterminate;
            wheels::tribool b = indeterminate;
            CHECK_TRIBOOL_INDETERMINATE(a && b);
        }
    }
    SECTION("or", "") {
        {
            wheels::tribool a = true;
            wheels::tribool b = true;
            CHECK_TRIBOOL_TRUE(a || b);
        }
        {
            wheels::tribool a = true;
            wheels::tribool b = false;
            CHECK_TRIBOOL_TRUE(a || b);
        }
        {
            wheels::tribool a = true;
            wheels::tribool b = indeterminate;
            CHECK_TRIBOOL_TRUE(a || b);
        }
        {
            wheels::tribool a = false;
            wheels::tribool b = true;
            CHECK_TRIBOOL_TRUE(a || b);
        }
        {
            wheels::tribool a = false;
            wheels::tribool b = false;
            CHECK_TRIBOOL_FALSE(a || b);
        }
        {
            wheels::tribool a = false;
            wheels::tribool b = indeterminate;
            CHECK_TRIBOOL_INDETERMINATE(a || b);
        }
        {
            wheels::tribool a = indeterminate;
            wheels::tribool b = true;
            CHECK_TRIBOOL_TRUE(a || b);
        }
        {
            wheels::tribool a = indeterminate;
            wheels::tribool b = false;
            CHECK_TRIBOOL_INDETERMINATE(a || b);
        }
        {
            wheels::tribool a = indeterminate;
            wheels::tribool b = indeterminate;
            CHECK_TRIBOOL_INDETERMINATE(a || b);
        }
    }
}

