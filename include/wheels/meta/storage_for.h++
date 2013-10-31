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

// Raw aligned storage type

#ifndef WHEELS_STORAGE_FOR_HPP
#define WHEELS_STORAGE_FOR_HPP

#include <wheels/meta/invoke.h++>
#include <wheels/meta/noexcept.h++>

#include <memory> // addressof
#include <type_traits> // aligned_storage, is_nothrow_destructible
#include <utility> // forward

namespace wheels {
    namespace meta {
        template <typename T>
        struct storage_for {
            struct type {
            public:
                type() noexcept = default;
                type(type const&) = delete;
                type& operator=(type const&) = delete;
                type(type&&) = delete;
                type& operator=(type&&) = delete;

                T& get() noexcept {
                    return *static_cast<T*>(static_cast<void*>(&storage));
                }
                T const& get() const noexcept {
                    return *static_cast<T const*>(static_cast<void const*>(&storage));
                }

                template <typename... Args>
                T& construct(Args&&... args) noexcept(meta::is_nothrow_placeable<T, Args&&...>()) {
                    return *::new(&storage) T(std::forward<Args>(args)...);
                }

                template <typename... Args>
                T& construct_braced(Args&&... args) noexcept(meta::is_nothrow_placeable_braced<T, Args&&...>()) {
                    return *::new(&storage) T{std::forward<Args>(args)...};
                }

                void destroy() noexcept(std::is_nothrow_destructible<T>()) {
                    get().~T();
                }

            private:
                Invoke<std::aligned_storage<sizeof(T), alignof(T)>> storage;
            };
        };
        template <typename T>
        struct storage_for<T&> : private storage_for<T*> {
            struct type {
            private:
                using base = storage_for<T*>;

            public:
                T& get() noexcept {
                    *base::get();
                }
                T const& get() const noexcept {
                    return *base::get();
                }

                T& construct(T& t) noexcept {
                    return *base::construct(std::addressof(t));
                }

                T& construct_u(T& t) noexcept {
                    return construct(t);
                }

                void destroy() noexcept {
                    base::destroy();
                }
            };
        };
        template <typename T>
        using StorageFor = Invoke<storage_for<T>>;
    } // namespace meta
} // namespace wheels

#endif // WHEELS_STORAGE_FOR_HPP

