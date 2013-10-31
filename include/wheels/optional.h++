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

// Optional

#ifndef WHEELS_OPTIONAL_HPP
#define WHEELS_OPTIONAL_HPP

#include <wheels/meta/storage_for.h++>
#include <wheels/meta/remove_reference.h++>
#include <wheels/meta/decay.h++>

#include <cassert>
#include <memory> // addressof
#include <type_traits> // is_nothrow_assignable

namespace wheels {
    template <typename T>
    class optional;

    struct none_t {
        template <typename T>
        constexpr operator optional<T>() const noexcept { return {}; }
    } constexpr none;

    namespace detail {
        template <typename T>
        struct optional_storage {
        public:
            optional_storage() noexcept = default;
            optional_storage(optional_storage const&) = delete;
            optional_storage& operator=(optional_storage const&) = delete;

            template <typename... Args>
            void construct(Args&&... args) noexcept(std::is_nothrow_constructible<T, Args&&...>()) {
                storage.construct(std::forward<Args>(args)...);
                present_ = true;
            }
            void assign(T const& t) noexcept(std::is_nothrow_copy_assignable<T>()) {
                get() = t;
            }
            void assign(T&& t) noexcept(std::is_nothrow_move_assignable<T>()) {
                get() = std::move(t);
            }
            void destroy() noexcept(std::is_nothrow_destructible<T>()) {
                storage.destroy();
                present_ = false;
            }
            T& get() & noexcept {
                assert(present());
                return storage.get();
            }
            T&& get() && noexcept {
                assert(present());
                return std::move(storage.get());
            }
            T const& get() const& noexcept {
                assert(present());
                return storage.get();
            }
            T* ptr() noexcept {
                assert(present());
                return storage.ptr();
            }
            T const* ptr() const noexcept {
                assert(present());
                return storage.ptr();
            }

            bool present() const noexcept {
                return present_;
            }

        private:
            bool present_ = false;
            wheels::meta::StorageFor<T> storage;
        };

        template <typename T>
        struct optional_storage<T&> {
        public:
            void construct(T& t) noexcept {
                storage = std::addressof(t);
            }
            void assign(T& t) noexcept {
                construct(t);
            }
            void destroy() noexcept {
                storage = nullptr;
            }
            T& get() const noexcept {
                assert(present());
                return *storage;
            }
            T* ptr() const noexcept {
                assert(present());
                return storage;
            }

            bool present() const noexcept {
                return storage;
            }

        private:
            T* storage = nullptr;
        };
        static_assert(std::is_default_constructible<optional_storage<int>>(), "");
        static_assert(std::is_default_constructible<optional_storage<int&>>(), "");

        template <typename T>
        struct optional_base : private detail::optional_storage<T> {
        private:
            using storage = detail::optional_storage<T>;

        public:
            using value_type = T;

            using storage::construct;
            using storage::assign;
            using storage::get;
            using storage::present;

            optional_base() noexcept {}
            optional_base(none_t) noexcept {}

            optional_base(optional_base const& that) noexcept(meta::is_nothrow_copy_placeable<T>())
            : storage() {
                if(that.present()) storage::construct(that.get());
            }
            optional_base(optional_base&& that) noexcept(meta::is_nothrow_move_placeable<T>())
            : storage() {
                if(that.present()) storage::construct(std::move(that).get());
            }

            optional_base& operator=(none_t) noexcept(std::is_nothrow_destructible<T>()) {
                if(storage::present()) storage::destroy();
                return *this;
            }
            optional_base& operator=(optional_base const& that)
            noexcept(noexcept(std::declval<storage&>().assign(that.get()))
                  && std::is_nothrow_destructible<T>()
                  && meta::is_nothrow_copy_placeable<T>()) {
                if(storage::present() && that.present()) storage::assign(that.get());
                else if(storage::present()) storage::destroy();
                else if(that.present()) storage::construct(that.get());
                return *this;
            }
            optional_base& operator=(optional_base&& that)
            noexcept(noexcept(std::declval<storage&>().assign(std::move(that).get()))
                  && std::is_nothrow_destructible<T>()
                  && meta::is_nothrow_move_placeable<T>()) {
                if(storage::present() && that.present()) storage::assign(std::move(that).get());
                else if(storage::present()) storage::destroy();
                else if(that.present()) storage::construct(std::move(that).get());
                return *this;
            }

            ~optional_base() noexcept(std::is_nothrow_destructible<T>()) {
                if(storage::present()) storage::destroy();
            }

            wheels::meta::RemoveReference<T>& operator*() & noexcept { return storage::get(); }
            wheels::meta::RemoveReference<T>&& operator*() && noexcept { return storage::get(); }
            wheels::meta::RemoveReference<T> const& operator*() const& noexcept { return storage::get(); }

            wheels::meta::RemoveReference<T>* operator->() noexcept { return storage::ptr(); }
            wheels::meta::RemoveReference<T> const* operator->() const noexcept { return storage::ptr(); }

            explicit operator bool() const noexcept {
                return storage::present();
            }
        };
        static_assert(std::is_default_constructible<optional_base<int>>(), "");
        static_assert(std::is_default_constructible<optional_base<int&>>(), "");
    } // namespace detail

    template <typename T>
    struct optional : private detail::optional_base<T> {
    private:
        using base = detail::optional_base<T>;

    public:
        using base::base;
        using base::operator*;
        using base::operator->;
        using base::operator bool;

        optional() noexcept = default;
        optional(T const& t) noexcept(meta::is_nothrow_copy_placeable<T>()) {
            base::construct(t);
        }
        optional(T&& t) noexcept(meta::is_nothrow_move_placeable<T>()) {
            base::construct(std::move(t));
        }

        optional& operator=(T const& t)
        noexcept(std::is_nothrow_copy_assignable<T>()
                && meta::is_nothrow_copy_placeable<T>()) {
            if(base::present()) base::get() = t;
            else base::construct(t);
            return *this;
        }
        optional& operator=(T&& t)
        noexcept(std::is_nothrow_move_assignable<T>()
                && meta::is_nothrow_move_placeable<T>()) {
            if(base::present()) base::get() = std::move(t);
            else base::construct(std::move(t));
            return *this;
        }
    };
    template <typename T>
    struct optional<T&> : private detail::optional_base<T&> {
    private:
        using base = detail::optional_base<T&>;

    public:
        using base::base;
        using base::operator*;
        using base::operator->;
        using base::operator bool;

        optional() noexcept {}
        optional(T& t) noexcept {
            base::construct(t);
        }
        optional(T&& t) noexcept { // TODO should I?
            base::construct(t);
        }

        optional& operator=(T& t) noexcept {
            if(base::present()) base::assign(t);
            else base::construct(t);
            return *this;
        }
        optional& operator=(T&& t) noexcept { // TODO should I?
            if(base::present()) base::assign(t);
            else base::construct(t);
            return *this;
        }
    };
    static_assert(std::is_default_constructible<optional<int>>(), "");
    static_assert(std::is_default_constructible<optional<int&>>(), "");

    template <typename T>
    optional<wheels::meta::Decay<T>> some(T&& t) {
        return std::forward<T>(t);
    }
} // namespace wheels

#endif // WHEELS_OPTIONAL_HPP

