//
// Written in 2013 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Tri-valued logic

#ifndef WHEELS_TRIBOOL_HPP
#define WHEELS_TRIBOOL_HPP

#include <boost/logic/tribool.hpp>

namespace wheels {
    using boost::indeterminate;

    struct tribool;
    constexpr bool is_true(tribool t);
    constexpr bool is_false(tribool t);
    constexpr bool is_indeterminate(tribool t);

    struct tribool {
    public:
        constexpr tribool() : tribool(false_value) {}
        constexpr tribool(bool value) : value(value? true_value : false_value) {}
        constexpr tribool(decltype(boost::indeterminate)) : value(indeterminate_value) {}
        /*constexpr*/ tribool(boost::tribool t) : value(t? true_value : !t? false_value : indeterminate_value) {}

        constexpr tribool operator!() const {
            return is_indeterminate(*this)? *this : !value;
        }

        constexpr tribool operator==(tribool that) const {
            return is_indeterminate(*this) || is_indeterminate(that)
                    ? indeterminate
                    : tribool(value == that.value);
        }
        constexpr tribool operator!=(tribool that) const {
            return is_indeterminate(*this) || is_indeterminate(that)
                    ? indeterminate
                    : tribool(value != that.value);
        }

        /*constexpr*/ operator boost::tribool() const {
            return is_indeterminate(*this)
                    ? boost::indeterminate
                    : boost::tribool(value == true_value);
        }

        constexpr tribool operator&&(tribool that) const {
            return is_false(*this) || is_false(that)
                    ? false
                    : is_indeterminate(*this) || is_indeterminate(that)
                        ? indeterminate
                        : tribool(true);
        }

        constexpr tribool operator||(tribool that) const {
            return is_true(*this) || is_true(that)
                    ? true
                    : is_indeterminate(*this) || is_indeterminate(that)
                        ? indeterminate
                        : tribool(false);
        }

    private:
        enum { false_value, true_value, indeterminate_value } value;

        friend constexpr bool is_true(tribool t) { return t.value == true_value; }
        friend constexpr bool is_false(tribool t) { return t.value == false_value; }
        friend constexpr bool is_indeterminate(tribool t) { return t.value == indeterminate_value; }
    };

} // namespace wheels

#endif // WHEELS_TRIBOOL_HPP
