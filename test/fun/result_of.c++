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

// result_of tests

#include <wheels/fun/result_of.h++>

#include <catch.hpp>

#include <wheels/meta/is_computable.h++>

TEST_CASE("fun/result_of", "result_of tests") {
    struct funobj {
        double operator()(int) const { return 0.0; }
        float operator()(int, int) const { return 0.0f; }
    };
    SECTION("SFINAE", "whether result_of SFINAEs") {
        CHECK((not wheels::meta::is_computable<wheels::fun::result_of<funobj()>>::value));
        CHECK((wheels::meta::is_computable<wheels::fun::result_of<funobj(int)>>::value));
        CHECK((wheels::meta::is_computable<wheels::fun::result_of<funobj(int, int)>>::value));
    }
    SECTION("result", "is the result correct?") {
        CHECK((std::is_same<wheels::fun::ResultOf<funobj(int)>, double>::value));
        CHECK((std::is_same<wheels::fun::ResultOf<funobj(int, int)>, float>::value));
    }
}

