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

namespace wheels {
    struct none_t {} constexpr none {};
    template <typename T>
    struct optional {
    public:
        optional() = default;
        optional(none_t) : optional() {}

        optional(optional const& that) : present(that.present) {
            if(present) storage.construct(that.storage.get());
        }
        optional(optional&& that) : present(that.present) {
            if(present) storage.construct(std::move(that.storage.get()));
        }

        optional& operator=(none_t) {
            if(present) {
                storage.destroy();
                present = false;
            }
            return *this;
        }
        optional& operator=(optional const& that) {
            if(present && that.present) storage.get() = that.storage.get();
            else if(present) storage.destroy();
            else if(that.present) storage.construct(that.storage.get());
            present = that.present;
            return *this;
        }
        optional& operator=(optional&& that) {
            if(present && that.present) storage.get() = std::move(that.storage.get());
            else if(present) storage.destroy();
            else if(that.present) place(std::move(that.storage.get()));
            present = that.present;
            return *this;
        }

        ~optional() {
            if(present) storage.destroy();
        }

        optional(T const& t) : present(true) {
            storage.construct(t);
        }
        optional(T&& t) : present(true) {
            storage.construct(std::move(t));
        }

        optional& operator=(T const& t) {
            if(present) storage.get() = t;
            else storage.construct(t);
            return *this;
        }
        optional& operator=(T&& t) {
            if(present) storage.get() = std::move(t);
            else storage.construct(std::move(t));
            return *this;
        }

        T& operator*() { return storage.get(); }
        T const& operator*() const { return storage.get(); }

        T* operator->() { return &storage.get(); }
        T const* operator->() const { return &storage.get(); }

        explicit operator bool() const {
            return present;
        }

    private:
        bool present = false;
        wheels::meta::StorageFor<T> storage;
    };
} // namespace wheels

#endif // WHEELS_OPTIONAL_HPP


