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

// Meta-programming facilities

#ifndef WHEELS_META_HPP
#define WHEELS_META_HPP

#include <wheels/meta/invoke.h++>
#include <wheels/meta/identity.h++>
#include <wheels/meta/alias.h++>
#include <wheels/meta/not_deducible.h++>

#include <wheels/meta/constant.h++>
#include <wheels/meta/int.h++>
#include <wheels/meta/bool.h++>

#include <wheels/meta/void.h++>

#include <wheels/meta/if.h++>
#include <wheels/meta/invoke_if.h++>

#include <wheels/meta/enable_if.h++>
#include <wheels/meta/can_compute.h++>

#include <wheels/meta/depend_on.h++>

#include <wheels/meta/add_const.h++>
#include <wheels/meta/remove_const.h++>
#include <wheels/meta/add_volatile.h++>
#include <wheels/meta/remove_volatile.h++>
#include <wheels/meta/add_cv.h++>
#include <wheels/meta/remove_cv.h++>

#include <wheels/meta/add_lvalue_reference.h++>
#include <wheels/meta/add_rvalue_reference.h++>
#include <wheels/meta/remove_reference.h++>

#include <wheels/meta/decay.h++>
#include <wheels/meta/unqualified.h++>

#endif // WHEELS_META_HPP

