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

// Shared ownership array

#ifndef WHEELS_MEM_DETAIL_SHARED_ARRAY_HPP
#define WHEELS_MEM_DETAIL_SHARED_ARRAY_HPP

#include <memory> // shared_ptr, default_delete
#include <utility> // forward
#include <cstddef> // nullptr_t, size_t

namespace wheels {
    namespace mem {
        namespace detail {
            template <typename T>
            struct weak_array;
            template <typename T>
            struct shared_array : private std::shared_ptr<T> {
            private:
                using impl = std::shared_ptr<T>;
            public:
                using typename impl::pointer;
                using typename impl::element_type;

                constexpr shared_array() noexcept = default;
                explicit shared_array(pointer p) : impl(p, std::default_delete<T[]>{}) {}
                explicit shared_array(weak_array<T> const& w) : impl(w) {}
                template <typename D>
                shared_array(pointer p, D&& d) : impl(p, std::forward<D>(d)) {}
                template <typename D, typename A>
                shared_array(pointer p, D&& d, A&& a) : impl(p, std::forward<D>(d), std::forward<A>(a)) {}
                constexpr shared_array(std::nullptr_t) noexcept : shared_array() {}
                template <typename D>
                shared_array(std::nullptr_t, D&& d) : impl(nullptr, std::forward<D>(d)) {}
                template <typename D, typename A>
                shared_array(std::nullptr_t, D&& d, A&& a) : impl(nullptr, std::forward<D>(d), std::forward<A>(a)) {}

                shared_array& operator=(std::nullptr_t) noexcept {
                    impl::operator=(nullptr);
                    return *this;
                }

                T& operator[](std::size_t i) const noexcept {
                    return get()[i];
                }
                std::shared_ptr<T> share(std::size_t i) const noexcept {
                    return { *this, get()[i] };
                }
                using impl::get;
                using impl::use_count;
                using impl::unique;
                using impl::operator bool;

                void swap(shared_array& that) noexcept {
                    impl::swap(that);
                }
                void reset() noexcept {
                    impl::reset();
                }
                void reset(pointer p) {
                    impl::reset(p, std::default_delete<T[]>{});
                }
                template <typename D>
                void reset(pointer p, D&& d) {
                    impl::reset(p, std::forward<D>(d));
                }
                template <typename D, typename A>
                void reset(pointer p, D&& d, A&& a) {
                    impl::reset(p, std::forward<D>(d), std::forward<A>(a));
                }
                friend class weak_array<T>;
            };
        } // namespace detail
    } // namespace mem
} // namespace wheels

#endif // WHEELS_MEM_DETAIL_SHARED_ARRAY_HPP

