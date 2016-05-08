// Wheels - various C++ utilities
//
// Written in 2013 by Martinho Fernandes <rmf@rmf.io>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Scoped enum operators

#ifndef WHEELS_ENUMS_HPP
#define WHEELS_ENUMS_HPP

#include <wheels/meta/bool.h++>
#include <wheels/meta/enable_if.h++>
#include <wheels/meta/underlying_type.h++>

#include <type_traits> // is_enum

#define WHEELS_ENUM_UNARY_OPERATOR(OP, KIND)                                    \
    template <typename Enum,                                                    \
              ::wheels::meta::EnableIf<std::is_enum<Enum>>...,                  \
              ::wheels::meta::EnableIf< ::wheels::enums::is_##KIND<Enum>>...>   \
    constexpr Enum operator OP(Enum value) noexcept {                           \
        return static_cast<Enum>(OP ::wheels::enums::to_underlying(value));     \
    }

#define WHEELS_ENUM_BINARY_OPERATOR(OP, KIND)                                   \
    template <typename Enum,                                                    \
              ::wheels::meta::EnableIf<std::is_enum<Enum>>...,                  \
              ::wheels::meta::EnableIf< ::wheels::enums::is_##KIND<Enum>>...>   \
    constexpr Enum operator OP(Enum const& l, Enum const& r) noexcept {         \
        return static_cast<Enum>(::wheels::enums::to_underlying(l)              \
                                 OP ::wheels::enums::to_underlying(r));         \
    }                                                                           \
    template <typename Enum,                                                    \
              ::wheels::meta::EnableIf<std::is_enum<Enum>>...,                  \
              ::wheels::meta::EnableIf< ::wheels::enums::is_##KIND<Enum>>...>   \
    constexpr Enum operator OP##=(Enum& l, Enum const& r) noexcept {            \
        return l = l OP r;                                                       \
    }

namespace wheels {
    namespace enums {
        template <typename T>
        struct is_flags : meta::Bool<flag_ops_enabled(T{})> {};

        template <typename Enum,
                  meta::EnableIf<std::is_enum<Enum>>...,
                  typename Underlying = meta::UnderlyingType<Enum>>
        constexpr Underlying to_underlying(Enum value) noexcept {
            return static_cast<Underlying>(value);
        }

        namespace operators {
            WHEELS_ENUM_UNARY_OPERATOR(~, flags)
            WHEELS_ENUM_BINARY_OPERATOR(|, flags)
            WHEELS_ENUM_BINARY_OPERATOR(&, flags)
            WHEELS_ENUM_BINARY_OPERATOR(^, flags)
        } // namespace operators

        template <typename Enum,
                  wheels::meta::EnableIf<std::is_enum<Enum>>...,
                  wheels::meta::EnableIf<is_flags<Enum>>...>
        bool has_flag_set(Enum flags, Enum flag) noexcept {
            return (to_underlying(flags) & to_underlying(flag)) != 0;
        }
    } // namespace enums
} // namespace wheels

#undef WHEELS_UNARY_ENUM_OPERATOR
#undef WHEELS_BINARY_ENUM_OPERATOR

#endif // WHEELS_ENUMS_HPP

