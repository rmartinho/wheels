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

// handle tests

#include <wheels/handle.h++>

#include <catch.h++>

struct foo {
    static int destroyed_count;
    ~foo() { ++destroyed_count; }
};
int foo::destroyed_count = 0;

int posix_closed = 0;
void wheels::posix_close(int) {
    ++posix_closed;
}
int wheels::posix_dup(int x) { return x*2; }
void wheels::posix_dup2(int, int b) {
    if(b >= 0) posix_close(b);
}

TEST_CASE("handle", "[handle]") {
    {
        wheels::handle<wheels::allocated_memory_traits<int>> h;
        REQUIRE_FALSE(bool(h));
    }

    {
        wheels::handle<wheels::allocated_memory_traits<foo>> h(new foo);
        REQUIRE(foo::destroyed_count == 0);
        REQUIRE(bool(h));
    }
    REQUIRE(foo::destroyed_count == 1);
    foo::destroyed_count = 0;

    {
        wheels::handle<wheels::allocated_memory_traits<foo>> h0(new foo);
        REQUIRE(foo::destroyed_count == 0);
        REQUIRE(bool(h0));
        wheels::handle<wheels::allocated_memory_traits<foo>> h1(new foo);
        REQUIRE(foo::destroyed_count == 0);
        REQUIRE(bool(h1));
        h0 = std::move(h1);
        REQUIRE(bool(h0));
        REQUIRE_FALSE(bool(h1));
        REQUIRE(foo::destroyed_count == 1);
    }
    REQUIRE(foo::destroyed_count == 2);
    foo::destroyed_count = 0;

    {
        wheels::handle<wheels::fd_traits> h0;
        REQUIRE_FALSE(bool(h0));
        wheels::handle<wheels::fd_traits> h1(1);
        REQUIRE(bool(h1));
        wheels::handle<wheels::fd_traits> h2(2);
        REQUIRE(bool(h2));
        h2 = h0;
        REQUIRE(posix_closed == 1);
        REQUIRE_FALSE(bool(h0));
        REQUIRE_FALSE(bool(h2));
        h0 = h1;
        REQUIRE(bool(h0));
        REQUIRE(bool(h1));
    }
    REQUIRE(posix_closed == 3);
}

