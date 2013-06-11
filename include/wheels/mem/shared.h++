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

// Shared ownership handling

#ifndef WHEELS_MEM_SHARED_HPP
#define WHEELS_MEM_SHARED_HPP

#include <wheels/meta/enable_if.h++>
#include <wheels/meta/not.h++>
#include <wheels/meta/bool.h++>
#include <wheels/meta/remove_extent.h++>
#include <wheels/meta/is_deduced.h++>
#include <wheels/meta/if.h++>
#include <wheels/meta/remove_pointer.h++>
#include <wheels/meta/unqual.h++>
#include <wheels/named_param.h++>
#include <wheels/names/raw.h++>
#include <wheels/names/deleter.h++>

#include <wheels/mem/detail/shared_array.h++>
#include <wheels/mem/detail/weak_array.h++>

#include <memory> // shared_ptr, weak_ptr
#include <type_traits> // is_array
#include <utility> // forward

namespace wheels {
    namespace mem {
        template <typename T>
        using shared = meta::If<std::is_array<T>,
                                detail::shared_array<meta::RemoveExtent<T>>,
                                std::shared_ptr<T>>;

        template <typename T>
        using weak = meta::If<std::is_array<T>,
                              detail::weak_array<meta::RemoveExtent<T>>,
                              std::weak_ptr<T>>;

        // forward arguments, default deleter
        template <typename T, typename... Args,
                  meta::EnableIf<meta::Not<std::is_array<T>>,
                                 no_named_param<Args...>>...,
                  typename Shared = shared<T>>
        Shared make_shared(Args&&... args) {
            return Shared(new T(std::forward<Args>(args)...));
        }

        // runtime-sized array
        template <typename T,
                  meta::EnableIf<std::is_array<T>,
                                 meta::Bool<std::extent<T>() == 0>>...,
                  typename Pointee = meta::RemoveExtent<T>,
                  typename Shared = shared<Pointee[]>>
        Shared make_shared(std::ptrdiff_t size) {
            return Shared(new Pointee[size]);
        }

        // compile-time-sized array
        template <typename T,
                  meta::EnableIf<std::is_array<T>, meta::Bool<std::extent<T>() != 0>>...,
                  typename Pointee = meta::RemoveExtent<T>,
                  std::ptrdiff_t Extent = std::extent<T>(),
                  typename Shared = shared<Pointee[]>>
        Shared make_shared() {
            return Shared(new Pointee[Extent]);
        }

        // from a raw pointer, default deleter
        template <typename Explicit = meta::deduced,
                  typename Raw,
                  typename Pointee = meta::If<meta::is_deduced<Explicit>, meta::RemovePointer<meta::Unqual<Raw>>, Explicit>,
                  typename Shared = shared<Pointee>>
        Shared make_shared(names::raw_parameter<Raw> const& raw) {
            return Shared(raw.forward());
        }

        // value-initialized, custom deleter
        template <typename T, typename Deleter,
                  typename Shared = shared<T>>
        Shared make_shared(names::deleter_parameter<Deleter> const& deleter) {
            return Shared(new T(), deleter.forward());
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
                  typename Pointee = meta::If<is_deduced<Explicit>, meta::RemovePointer<meta::Unqual<Raw>>, Explicit>,
                  typename Shared = shared<Pointee>>
        Shared make_shared(A0&& a0, A1&& a1) {
            return Shared(forward_named(names::raw, a0, a1), forward_named(names::deleter, a0, a1));
        }

        // TODO allocate_shared?
    } // namespace mem
} // namespace wheels

#endif // WHEELS_MEM_SHARED_HPP

