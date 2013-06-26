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

// Unique ownership handling

#ifndef WHEELS_MEM_UNIQUE_HPP
#define WHEELS_MEM_UNIQUE_HPP

#include <wheels/meta/enable_if.h++>
#include <wheels/meta/not.h++>
#include <wheels/meta/bool.h++>
#include <wheels/meta/remove_extent.h++>
#include <wheels/meta/is_deduced.h++>
#include <wheels/meta/if.h++>
#include <wheels/meta/remove_pointer.h++>
#include <wheels/meta/unqual.h++>
#include <wheels/meta/decay.h++>
#include <wheels/named_param.h++>
#include <wheels/names/raw.h++>
#include <wheels/names/deleter.h++>

#include <memory> // unique_ptr, default_delete
#include <type_traits> // is_array

namespace wheels {
    namespace mem {
        template <typename T, typename D = std::default_delete<T>>
        using unique = std::unique_ptr<T, D>;

        // forward arguments, default deleter
        template <typename T, typename... Args,
                  meta::EnableIf<meta::Not<std::is_array<T>>,
                                 no_named_param<Args...>>...,
                  typename Unique = unique<T>>
        Unique make_unique(Args&&... args) {
            return Unique(new T(std::forward<Args>(args)...));
        }

        // runtime-sized array
        template <typename T,
                  meta::EnableIf<std::is_array<T>,
                                 meta::Bool<std::extent<T>() == 0>>...,
                  typename Pointee = meta::RemoveExtent<T>,
                  typename Unique = unique<Pointee[]>>
        Unique make_unique(std::ptrdiff_t size) {
            return Unique(new Pointee[size]);
        }

        // compile-time-sized array
        template <typename T,
                  meta::EnableIf<std::is_array<T>, meta::Bool<std::extent<T>() != 0>>...,
                  typename Pointee = meta::RemoveExtent<T>,
                  std::ptrdiff_t Extent = std::extent<T>(),
                  typename Unique = unique<Pointee[]>>
        Unique make_unique() {
            return Unique(new Pointee[Extent]);
        }

        // from a raw pointer, default deleter
        template <typename Explicit = meta::deduced,
                  typename Raw,
                  typename Pointee = meta::If<meta::is_deduced<Explicit>, meta::RemovePointer<meta::Unqual<Raw>>, Explicit>,
                  typename Unique = unique<Pointee>>
        Unique make_unique(names::raw_param<Raw> const& raw) {
            return Unique(raw.forward());
        }

        // value-initialized, custom deleter
        template <typename T, typename Deleter,
                  typename Unique = unique<T, meta::Decay<Deleter>>>
        Unique make_unique(names::deleter_param<Deleter> const& deleter) {
            return Unique(new T(), deleter.forward());
        }

        // tuple of args, custom deleter
        // TODO needs indices

        // raw pointer, custom deleter
        template <typename Explicit = meta::deduced,
                  typename A0, typename A1,
                  meta::EnableIf<is_named_param<A0>, is_named_param<A1>,
                                 has_param<names::raw_name, A0, A1>,
                                 has_param<names::deleter_name, A0, A1>>...,
                  typename Raw = ParamType<GetParam<names::raw_name, A0, A1>>,
                  typename Deleter = ParamType<GetParam<names::deleter_name, A0, A1>>,
                  typename Pointee = meta::If<meta::is_deduced<Explicit>, meta::RemovePointer<meta::Unqual<Raw>>, Explicit>,
                  typename Unique = unique<Pointee, meta::Decay<Deleter>>>
        Unique make_unique(A0&& a0, A1&& a1) {
            return Unique(forward_named(names::raw, a0, a1), forward_named(names::deleter, a0, a1));
        }

        // TODO allocate_unique?
    } // namespace mem
} // namespace wheels

#endif // WHEELS_MEM_UNIQUE_HPP

