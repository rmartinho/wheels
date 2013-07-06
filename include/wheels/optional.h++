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

namespace wheels {
    template <typename T>
    class optional;

    struct none_t {
        template <typename T>
        constexpr operator optional<T>() const { return {}; }
    } constexpr none;

    namespace detail {
        template <typename T>
        struct optional_storage {
        public:
            optional_storage() = default;
            optional_storage(optional_storage const&) = delete;
            optional_storage& operator=(optional_storage const&) = delete;

            template <typename... Args>
            void construct(Args&&... args) {
                storage.construct(std::forward<Args>(args)...);
                present_ = true;
            }
            void assign(T const& t) {
                get() = t;
            }
            void destroy() {
                storage.destroy();
                present_ = false;
            }
            T& get() & {
                assert(present());
                return storage.get();
            }
            T&& get() && {
                assert(present());
                return std::move(storage.get());
            }
            T const& get() const& {
                assert(present());
                return storage.get();
            }
            T* ptr() {
                assert(present());
                return storage.ptr();
            }
            T const* ptr() const {
                assert(present());
                return storage.ptr();
            }

            bool present() const {
                return present_;
            }

        private:
            bool present_ = false;
            wheels::meta::StorageFor<T> storage;
        };

        template <typename T>
        struct optional_storage<T&> {
        public:
            void construct(T& t) {
                storage = std::addressof(t);
            }
            void assign(T& t) {
                construct(t);
            }
            void destroy() {
                storage = nullptr;
            }
            T& get() const {
                assert(present());
                return *storage;
            }
            T* ptr() const {
                assert(present());
                return storage;
            }

            bool present() const {
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

            optional_base() {}
            optional_base(none_t) {}

            optional_base(optional_base const& that) : storage() {
                if(that.present()) storage::construct(that.get());
            }
            optional_base(optional_base&& that) : storage() {
                if(that.present()) storage::construct(std::move(that).get());
            }

            optional_base& operator=(none_t) {
                if(storage::present()) storage::destroy();
                return *this;
            }
            optional_base& operator=(optional_base const& that) {
                if(storage::present() && that.present()) storage::get() = that.get();
                else if(storage::present()) storage::destroy();
                else if(that.present()) storage::construct(that.get());
                return *this;
            }
            optional_base& operator=(optional_base&& that) {
                if(storage::present() && that.present()) storage::get() = std::move(that).get();
                else if(storage::present()) storage::destroy();
                else if(that.present()) storage::construct(std::move(that).get());
                return *this;
            }

            ~optional_base() {
                if(storage::present()) storage::destroy();
            }

            wheels::meta::RemoveReference<T>& operator*() & { return storage::get(); }
            wheels::meta::RemoveReference<T>&& operator*() && { return storage::get(); }
            wheels::meta::RemoveReference<T> const& operator*() const& { return storage::get(); }

            wheels::meta::RemoveReference<T>* operator->() { return storage::ptr(); }
            wheels::meta::RemoveReference<T> const* operator->() const { return storage::ptr(); }

            explicit operator bool() const {
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

        optional() = default;
        optional(T const& t) {
            base::construct(t);
        }
        optional(T&& t) {
            base::construct(std::move(t));
        }

        optional& operator=(T const& t) {
            if(base::present()) base::get() = t;
            else base::construct(t);
            return *this;
        }
        optional& operator=(T&& t) {
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

        optional() {}
        optional(T& t) {
            base::construct(t);
        }
        optional(T&& t) { // TODO should I?
            base::construct(t);
        }

        optional& operator=(T& t) {
            if(base::present()) base::assign(t);
            else base::construct(t);
            return *this;
        }
        optional& operator=(T&& t) { // TODO should I?
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

