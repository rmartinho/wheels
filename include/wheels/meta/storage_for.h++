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

#include <memory> // addressof
#include <type_traits> // aligned_storage
#include <utility> // forward

namespace wheels {
    namespace meta {
        template <typename T>
        struct storage_for {
            struct type {
            public:
                type() = default;
                type(type const&) = delete;
                type& operator=(type const&) = delete;
                type(type&&) = delete;
                type& operator=(type&&) = delete;

                T& get() {
                    return *static_cast<T*>(static_cast<void*>(&storage));
                }
                T const& get() const {
                    return *static_cast<T const*>(static_cast<void const*>(&storage));
                }

                template <typename... Args>
                T& construct(Args&&... args) {
                    return *::new(&storage) T(std::forward<Args>(args)...);
                }

                template <typename... Args>
                T& construct_braced(Args&&... args) {
                    return *::new(&storage) T{std::forward<Args>(args)...};
                }

                void destroy() {
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
                T& get() {
                    *base::get();
                }
                T const& get() const {
                    return *base::get();
                }

                T& construct(T& t) {
                    return *base::construct(std::addressof(t));
                }

                T& construct_u(T& t) {
                    return construct(t);
                }

                void destroy() {
                    base::destroy();
                }
            };
        };
        template <typename T>
        using StorageFor = Invoke<storage_for<T>>;
    } // namespace meta
} // namespace wheels

#endif // WHEELS_STORAGE_FOR_HPP

