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

// Generic handle type

#ifndef WHEELS_HANDLE_HPP
#define WHEELS_HANDLE_HPP

#include <wheels/meta/bool.h++>
#include <wheels/meta/enable_if.h++>
#include <wheels/meta/trait_of.h++>

#include <type_traits> // is_convertible
#include <utility>

namespace wheels {
#define WHEELS_MEMBER_TESTER(Name, ...)                         \
    struct Name##_tester {                                      \
        template <typename T>                                   \
        static __VA_ARGS__ test(int);                           \
        template <typename>                                     \
        static meta::False test(...);                           \
    };                                                          \
    template <typename T>                                       \
    struct has_##Name : decltype(Name##_tester::test<T>(0)) {}

    namespace detail {
        WHEELS_MEMBER_TESTER(is_valid, std::is_convertible<decltype(T::is_valid(std::declval<typename T::native_type>())), bool>);
        WHEELS_MEMBER_TESTER(empty, std::is_convertible<decltype(T::empty()), typename T::native_type>);
        WHEELS_MEMBER_TESTER(move, std::is_convertible<decltype(T::move(std::declval<typename T::native_type&>())), typename T::native_type>);
        WHEELS_MEMBER_TESTER(move_assign, std::is_convertible<decltype(T::move_assign(std::declval<typename T::native_type&>(), std::declval<typename T::native_type&>())), void>);
        WHEELS_MEMBER_TESTER(copy, std::is_convertible<decltype(T::copy(std::declval<typename T::native_type const&>())), typename T::native_type>);
        WHEELS_MEMBER_TESTER(copy_assign, std::is_convertible<decltype(T::copy_assign(std::declval<typename T::native_type&>(), std::declval<typename T::native_type const&>())), void>);
    } // namespace detail
#undef WHEELS_MEMBER_TESTER

    template <typename Traits>
    struct handle_traits {
        using native_type = typename Traits::native_type;

        template <typename T = Traits,
                  meta::EnableIf<detail::has_is_valid<T>>...>
        static bool is_valid(native_type const& handle) {
            return Traits::is_valid(handle);
        }
        template <typename T = Traits,
                  meta::DisableIf<detail::has_is_valid<T>>...>
        static bool is_valid(native_type const& handle) {
            return static_cast<bool>(handle);
        }

        template <typename T = Traits,
                  meta::EnableIf<detail::has_empty<T>>...>
        static native_type empty() {
            return Traits::empty();
        }
        template <typename T = Traits,
                  meta::DisableIf<detail::has_empty<T>>...>
        static native_type empty() {
            return native_type{};
        }

        template <typename T = Traits,
                  meta::EnableIf<detail::has_move<T>>...>
        static auto move(native_type& h) -> decltype(T::move(h)) {
            return Traits::move(h);
        }
        template <typename T = Traits,
                  meta::DisableIf<detail::has_move<T>>...>
        static native_type move(native_type& h) {
            auto copy = h;
            h = empty();
            return copy;
        }

        template <typename T = Traits,
                  meta::EnableIf<detail::has_move_assign<T>>...>
        static void move_assign(native_type& to, native_type& from) {
            return Traits::move_assign(to, from);
        }
        template <typename T = Traits,
                  meta::DisableIf<detail::has_move_assign<T>>...>
        static void move_assign(native_type& to, native_type& from) {
            close(to);
            to = from;
            from = empty();
        }

        template <typename T = Traits>
        static auto copy(native_type const& h) -> decltype(T::copy(h)) {
            static_assert(detail::has_copy<T>(), "traits must provide copying semantics");
            return Traits::copy(h);
        }
        template <typename T = Traits>
        static void copy_assign(native_type& to, native_type const& from) {
            static_assert(detail::has_copy_assign<T>(), "traits must provide copying assignment semantics");
            return Traits::copy_assign(to, from);
        }

        static void close(native_type& handle) {
            Traits::close(handle);
        }
    };

    template <typename Traits>
    struct handle {
    private:
        using traits = handle_traits<Traits>;

    public:
        using native_type = typename traits::native_type;

        handle() : native_handle(traits::empty()) {}

        handle(native_type const& native_handle)
        : native_handle(traits::copy(native_handle)) {}

        handle(handle&& that) noexcept(noexcept(traits::move(std::declval<native_type&>())))
        : native_handle(traits::move(that.native_handle)) {}

        handle& operator=(handle&& that) noexcept(noexcept(traits::move_assign(std::declval<native_type&>(), std::declval<native_type&>()))) {
            traits::move_assign(native_handle, that.native_handle);
            return *this;
        }
        handle& operator=(handle const& that) {
            traits::copy_assign(native_handle, that.native_handle);
            return *this;
        }

        ~handle() {
            if(traits::is_valid(native_handle)) {
                traits::close(native_handle);
            }
        }

        explicit operator bool() const {
            return traits::is_valid(native_handle);
        }

    private:
        native_type native_handle;
    };
} // namespace wheels

namespace examples {
    struct fd_traits {
        using native_type = int;

        static bool is_valid(native_type const& handle) {
            return handle >= 0;
        }
        static native_type empty() { return -1; }
        static void close(native_type& handle) {
            close(handle);
        }

        static native_type copy(native_type const& handle) {
            if(handle < 0) return handle;
            return dup(handle);
        }
        static void copy_assign(native_type& to, native_type const& from) {
            if(from < 0) {
                if(to >= 0) close(to);
                to = from;
            } else {
                if(to < 0) {
                    to = dup(from);
                } else {
                    dup2(from, to);
                }
            }
        }
    };
    struct gl_program_traits {
        using native_type = GLuint;

        static void close(native_type& handle) {
            glDeleteProgram(handle);
        }
    };
    template <typename T>
    struct allocated_memory_traits {
        using native_type = T*;

        static void close(native_type& handle) {
            delete handle;
        }
    };
    template <typename T>
    struct allocated_memory_traits<T[]> {
        using native_type = T*;

        static void close(native_type& handle) {
            delete[] handle;
        }
    };
    struct win_handle_traits {
        // Fuck this shit, the Windows API is too fucked up for such a generic thing:
        // some APIs indicate failure with INVALID_HANDLE_VALUE, some 0, some -1, some non-zero,
        // some <= 32 (yes, that is goddamn right, check ShellExecute). I quit.
    };
} // namespace examples

#endif // WHEELS_HANDLE_HPP


