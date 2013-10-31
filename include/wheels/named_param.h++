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

// Named parameter emulation toolkit

#ifndef WHEELS_NAMED_PARAM_HPP
#define WHEELS_NAMED_PARAM_HPP

#include <wheels/meta/is_unqual.h++>
#include <wheels/meta/int.h++>
#include <wheels/meta/any.h++>
#include <wheels/meta/not.h++>
#include <wheels/meta/if.h++>
#include <wheels/meta/id.h++>
#include <wheels/meta/invoke.h++>
#include <wheels/meta/is_specialization_of.h++>

#include <type_traits> // is_reference, is_same
#include <utility> // forward

// Defines a parameter name that can be used anywhere
#define WHEELS_DEFINE_NAMED_PARAM(NAME) \
    struct NAME##_name : private ::wheels::param_name<NAME##_name> {    \
        using ::wheels::param_name<NAME##_name>::operator=;             \
    } constexpr NAME {};                                                \
    template <typename T>                                               \
    using NAME##_param = ::wheels::named_param<NAME##_name, T>

namespace wheels {
    // Holder for the arguments passed through named parameters
    template <typename Name, typename T>
    struct named_param {
    public:
        static_assert(std::is_reference<T>(), "T must be a reference type");
        static_assert(meta::is_unqual<Name>(), "Name must be an unqualified type");

        using name = Name;
        using type = T;

        constexpr named_param(T&& t) noexcept : ref(std::forward<T>(t)) {}

        void operator=(named_param const&) = delete;

        T&& forward() const noexcept { return std::forward<T>(ref); }

    private:
        T ref;
    };

    // Retrieves the name of a named parameter
    template <typename Param>
    using ParamName = typename Param::name;
    // Retrieves the type of a named parameter
    template <typename Param>
    using ParamType = typename Param::type;

    // *Returns*: `True` if any `Param` has the name `Name`
    template <typename Name, typename... Param>
    struct has_param : meta::Any<std::is_same<ParamName<Param>, Name>...> {};

    // *Returns*: the parameter with the given name from the list
    template <typename Name, typename... Param>
    struct get_param {};
    template <typename Name, typename H, typename... T>
    struct get_param<Name, H, T...>
    : meta::If<has_param<Name, H>,
        meta::id<H>,
        get_param<Name, T...>
    > {};
    template <typename Name, typename... Param>
    using GetParam = meta::Invoke<get_param<Name, Param...>>;

    // Name tag for named parameters
    template <typename Name>
    struct param_name {
        constexpr param_name() noexcept = default;
        // Fake assignment to hold an argument passed through a parameter of this name
        template <typename T>
        constexpr named_param<Name, T&&> operator=(T&& t) const noexcept {
            return { std::forward<T>(t) };
        }
        param_name(param_name const&) = delete;
        param_name& operator=(param_name const&) = delete;
    };

    // *Returns*: `True` if `T` is a named parameter holder
    template <typename T>
    struct is_named_param : meta::is_specialization_of<named_param, T> {};

    // *Returns*: `True` if none of `T...` is a named parameter holder
    template <typename... T>
    struct no_named_param : meta::Not<meta::Any<is_named_param<T>...>> {};

    // *Returns*: the number of named parameter holders in all of `T...`
    template <typename... T>
    struct named_param_count : meta::Int<0> {}; // TODO : use typelist algorithm
    template <typename H, typename... T>
    struct named_param_count<H, T...> : named_param_count<T...> {};
    template <typename N, typename H, typename... T>
    struct named_param_count<named_param<N, H>, T...> : meta::Int<1 + named_param_count<T...>()> {};

    // Forwards the parameter with the given name from an argument list
    template <typename Name, typename H, typename... T>
    H&& forward_named(Name const&, named_param<Name, H> const& param, T&&...) noexcept {
        return param.forward();
    }
    template <typename Name, typename H, typename... T>
    ParamType<GetParam<Name, T...>>&& forward_named(Name const& name, H&&, T&&... t) noexcept {
        return forward_named(name, std::forward<T>(t)...);
    }
} // namespace wheels

#endif // WHEELS_NAMED_PARAM_HPP

