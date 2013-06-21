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

#include <cassert>

namespace wheels {
    struct none_t {} constexpr none {};
    template <typename T>
    struct optional {
    public:
        optional() = default;
        optional(none_t) : optional() {}

        optional(optional const& that) {
            if(that.present) construct(that.get());
        }
        optional(optional&& that) {
            if(that.present) construct(std::move(that.get()));
        }

        optional& operator=(none_t) {
            if(present) destroy();
            return *this;
        }
        optional& operator=(optional const& that) {
            if(present && that.present) get() = that.get();
            else if(present) destroy();
            else if(that.present) construct(that.get());
            return *this;
        }
        optional& operator=(optional&& that) {
            if(present && that.present) get() = std::move(that.get());
            else if(present) destroy();
            else if(that.present) place(std::move(that.get()));
            return *this;
        }

        ~optional() {
            if(present) destroy();
        }

        optional(T const& t) {
            construct(t);
        }
        optional(T&& t) {
            construct(std::move(t));
        }

        optional& operator=(T const& t) {
            if(present) get() = t;
            else construct(t);
            return *this;
        }
        optional& operator=(T&& t) {
            if(present) get() = std::move(t);
            else construct(std::move(t));
            return *this;
        }

        T& operator*() { return get(); }
        T const& operator*() const { return get(); }

        T* operator->() { return &get(); }
        T const* operator->() const { return &get(); }

        explicit operator bool() const {
            return present;
        }

    private:
        template <typename... Args>
        void construct(Args&&... args) {
            storage.construct(std::forward<Args>(args)...);
            present = true;
        }
        void destroy() {
            storage.destroy();
            present = false;
        }
        T& get() {
            assert(present);
            return storage.get();
        }
        T const& get() const {
            assert(present);
            return storage.get();
        }

        bool present = false;
        wheels::meta::StorageFor<T> storage;
    };
} // namespace wheels

#endif // WHEELS_OPTIONAL_HPP


