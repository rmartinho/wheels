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

namespace test1 {
    const int expected_result = 42;
    const double expected_arg1 = 17.23;
    const int expected_arg2 = true;
    int called{};
    double arg1{};
    bool arg2{};
    int call(double a1, bool a2) {
        ++called;
        arg1 = a1;
        arg2 = a2;
        return expected_result;
    }
} // namespace fun1
TEST_CASE("invoke", "INVOKE tests") {
    SECTION("function", "invoking functions") {
        test1::called = 0;
        auto result = wheels::fun::invoke(test1::call, test1::expected_arg1, test1::expected_arg2);

        CHECK((std::is_same<decltype(wheels::fun::invoke(test1::call, 0, 0)), int>::value));
        CHECK(test1::called == 1);
        CHECK(result == test1::expected_result);
        CHECK(test1::arg1 == test1::expected_arg1);
        CHECK(test1::arg2 == test1::expected_arg2);
    }
    SECTION("funobj", "invoking function objects") {
        struct local {
            double a1;
            int operator()(bool a2) {
                return test1::call(a1, a2);
            }
        };
        local l { test1::expected_arg1 };
        test1::called = 0;
        auto result = wheels::fun::invoke(l, test1::expected_arg2);

        CHECK((std::is_same<decltype(wheels::fun::invoke(l, 0)), int>::value));
        CHECK(test1::called == 1);
        CHECK(result == test1::expected_result);
        CHECK(test1::arg1 == test1::expected_arg1);
        CHECK(test1::arg2 == test1::expected_arg2);
    }
    SECTION("ptmo", "invoking pointer to member object") {
        struct local {
            int r;
        };
        {
            local l { test1::expected_result };
            auto&& result = wheels::fun::invoke(&local::r, l);

            CHECK((std::is_same<decltype(result), int&>::value));
            CHECK(result == test1::expected_result);
        }
        {
            auto&& result = wheels::fun::invoke(&local::r, local{ test1::expected_result });

            CHECK((std::is_same<decltype(result), int&&>::value));
        }
    }
    SECTION("ptmf", "invoking pointer to member function") {
        struct local {
            double a1;
            int f(bool a2) {
                return test1::call(a1, a2);
            }
        };
        local l { test1::expected_arg1 };
        test1::called = 0;
        auto result = wheels::fun::invoke(&local::f, l, test1::expected_arg2);

        CHECK((std::is_same<decltype(result), int>::value));
        CHECK(test1::called == 1);
        CHECK(result == test1::expected_result);
        CHECK(test1::arg1 == test1::expected_arg1);
        CHECK(test1::arg2 == test1::expected_arg2);
    }
    SECTION("result", "invoking with forced result type") {
        auto result = wheels::fun::invoke<unsigned>(test1::call, test1::expected_arg1, test1::expected_arg2);
        CHECK((std::is_same<decltype(result), unsigned>::value));
        CHECK(result == unsigned(test1::expected_result));
    }
    SECTION("void", "invoking discarding result") {
        CHECK((std::is_same<decltype(wheels::fun::invoke<void>(test1::call, 0, 0)), void>::value));
    }
}

