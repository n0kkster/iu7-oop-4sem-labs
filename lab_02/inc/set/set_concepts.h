#pragma once

#include <compare>
#include <concepts>

template <typename From, typename To>
concept Convertible = std::convertible_to<From, To>;

template <typename Type>
concept Assignable = requires(Type &lv, Type &rv) { lv = rv; };

template <typename Type>
concept CopyMoveAssignable =
    std::copy_constructible<Type> && std::move_constructible<Type> && Assignable<Type>;

template <typename C>
concept CopyConstructible = requires(const C &c) {
    { C(c) } -> std::same_as<C>;
};

template <typename C>
concept Container =
    CopyConstructible<C> && std::move_constructible<C> && std::destructible<C> && requires(C c) {
        typename C::value_type;
        typename C::reference;
        typename C::const_reference;
        typename C::const_iterator;
        typename C::difference_type;
        typename C::size_type;

        { c.cbegin() } noexcept -> std::same_as<typename C::const_iterator>;
        { c.cend() } noexcept -> std::same_as<typename C::const_iterator>;

        { c.size() } noexcept -> std::same_as<typename C::size_type>;
        { c.empty() } noexcept -> std::same_as<bool>;
    };
