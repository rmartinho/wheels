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

// is_invocable tests

#include <wheels/fun/is_invocable.h++>

#include <catch.hpp>

TEST_CASE("fun/is_invocable", "is_invocable tests") {
    SECTION("no fun", "not a function thingy") {
        CHECK((not wheels::fun::is_invocable<int, void()>::value));
    }

    SECTION("simple funobj", "function object with one op()") {
        auto lambda = [](int) { };
        CHECK((wheels::fun::is_invocable<decltype(lambda), void(int)>::value));
        CHECK((not wheels::fun::is_invocable<decltype(lambda), void()>::value));
        CHECK((wheels::fun::is_invocable<decltype(lambda), void(long)>::value));
        CHECK((not wheels::fun::is_invocable<decltype(lambda), double(int)>::value));
    }

    struct funobj {
        int* operator()() {
            return nullptr;
        }

        int operator()() const {
            return 0;
        }
    };

    SECTION("const or not", "function object with const and non-const op()") {
        CHECK((wheels::fun::is_invocable<funobj, void()>::value));
        CHECK((wheels::fun::is_invocable<funobj, int*()>::value));
        CHECK((wheels::fun::is_invocable<funobj, void*()>::value));
        CHECK((not wheels::fun::is_invocable<funobj, int()>::value));

        CHECK((wheels::fun::is_invocable<const funobj, void()>::value));
        CHECK((not wheels::fun::is_invocable<const funobj, int*()>::value));
        CHECK((wheels::fun::is_invocable<const funobj, int()>::value));
        CHECK((wheels::fun::is_invocable<const funobj, long()>::value));
    }
    SECTION("ptmo", "pointer to member object") {
        using ptmo = int funobj::*;
        CHECK((wheels::fun::is_invocable<ptmo, int&(funobj&)>::value));
        CHECK((wheels::fun::is_invocable<ptmo, int const&(funobj const&)>::value));
        CHECK((wheels::fun::is_invocable<ptmo, int&&(funobj&&)>::value));
        CHECK((wheels::fun::is_invocable<ptmo, int const&&(funobj const&&)>::value));
        CHECK((wheels::fun::is_invocable<ptmo, double(funobj&)>::value));
        CHECK((not wheels::fun::is_invocable<ptmo, int&(funobj&, int)>::value));
    }
    SECTION("ptmf", "pointer to member function") {
        using ptmf = float (funobj::*)(double);
        using ptcmf = int* (funobj::*)() const;
        CHECK((wheels::fun::is_invocable<ptmf, float(funobj&, double)>::value));
        CHECK((wheels::fun::is_invocable<ptmf, float(funobj*, double)>::value));
        CHECK((wheels::fun::is_invocable<ptmf, double(funobj&, double)>::value));
        CHECK((wheels::fun::is_invocable<ptmf, double(funobj*, double)>::value));

        CHECK((wheels::fun::is_invocable<ptcmf, int* (funobj&)>::value));
        CHECK((wheels::fun::is_invocable<ptcmf, int* (funobj*)>::value));
        CHECK((wheels::fun::is_invocable<ptcmf, void* (funobj&)>::value));
        CHECK((wheels::fun::is_invocable<ptcmf, void* (funobj*)>::value));
        CHECK((wheels::fun::is_invocable<ptcmf, int* (funobj const&)>::value));
        CHECK((wheels::fun::is_invocable<ptcmf, int* (funobj const*)>::value));
        CHECK((wheels::fun::is_invocable<ptcmf, void* (funobj const&)>::value));
        CHECK((wheels::fun::is_invocable<ptcmf, void* (funobj const*)>::value));
    }
}

