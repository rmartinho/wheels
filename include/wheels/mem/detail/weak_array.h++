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

// Weak handle for shared ownership array

#ifndef WHEELS_MEM_DETAIL_WEAK_ARRAY_HPP
#define WHEELS_MEM_DETAIL_WEAK_ARRAY_HPP

#include <memory> // weak_ptr

namespace wheels {
    namespace mem {
        namespace detail {
            template <typename T>
            struct shared_array;
            template <typename T>
            struct weak_array : private std::weak_ptr<T> {
            private:
                using impl = std::weak_ptr<T>;
            public:
                using typename impl::element_type;

                constexpr weak_array() noexcept = default;
                weak_array(shared_array<T> const& r) noexcept : impl(r) {}

                weak_array& operator=(shared_array<T> const& r) {
                    impl::operator=(r);
                    return *this;
                }

                void swap(weak_array& that) noexcept {
                    impl::swap(that);
                }
                using impl::reset;
                using impl::expired;
                using impl::use_count;
                shared_array<T> lock() const noexcept {
                    return *this;
                }
                friend class shared_array<T>;
            };
        } // namespace detail
    } // namespace mem
} // namespace wheels

#endif // WHEELS_MEM_DETAIL_WEAK_ARRAY_HPP

