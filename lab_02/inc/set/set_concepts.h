#pragma once

#include <compare>
#include <concepts>
#include <iterator>

template <typename From, typename To>
concept Convertible = std::convertible_to<From, To>;

template <typename T>
concept Assignable = requires(T &lv, T &rv) { lv = rv; };

template <typename T>
concept CopyMoveAssignable =
    std::copy_constructible<T> && std::move_constructible<T> && Assignable<T>;

template<typename T, typename U>
    concept EqualityComparable = std::equality_comparable_with<T, U>;

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

template <typename Container>
    concept Comparable = requires(Container cont1, Container cont2) {
        { cont1 == cont2 } noexcept -> std::same_as<bool>;
        { cont1 != cont2 } noexcept -> std::same_as<bool>;
};

template <typename It>
    concept BidirectionalIterator = std::bidirectional_iterator<It>;
    
template <typename It, typename T>
    concept ConvertibleInputIterator = BidirectionalIterator<It> && Convertible<typename It::value_type, T>;

template <typename R>
    concept Range = std::ranges::bidirectional_range<R>;

template <typename R, typename T>
    concept ConvertibleRange = Range<R> && Convertible<std::ranges::range_value_t<R>, T>;

template <typename C, typename T>
    concept ConvertibleContainer = Container<C> && Convertible<typename C::value_type, T> && Comparable<C>;