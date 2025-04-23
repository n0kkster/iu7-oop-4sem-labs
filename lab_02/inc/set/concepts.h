#pragma once

#include <compare>
#include <concepts>
#include <iterator>

template <typename From, typename To>
concept Convertible = (std::same_as<From, To> || std::convertible_to<From, To>);

template <typename T, typename U>
concept HasCommon = requires { typename std::common_type_t<T, U>; };

template <typename T>
concept Assignable = requires(T &lv, T &rv) { lv = rv; };

template <typename T>
concept CopyMoveAssignable = std::copy_constructible<T> && std::move_constructible<T> && Assignable<T>;

template <typename T, typename U>
concept EqualityComparable = requires(T t, U u) {
    { t == u } noexcept -> std::same_as<bool>;
    { t != u } noexcept -> std::same_as<bool>;
    { u == t } noexcept -> std::same_as<bool>;
    { u != t } noexcept -> std::same_as<bool>;
};

template <typename C>
concept CopyConstructible = requires(const C &c) {
    { C(c) } -> std::same_as<C>;
};

template <CopyMoveAssignable T>
class Set;

template <typename C>
concept IsSet = std::same_as<Set<typename C::value_type>, C>;

template <typename C>
concept Container =
    CopyConstructible<C> && std::move_constructible<C> && std::destructible<C> && requires(C c) {
        typename std::remove_reference_t<C>::value_type;
        typename std::remove_reference_t<C>::reference;
        typename std::remove_reference_t<C>::const_reference;
        typename std::remove_reference_t<C>::const_iterator;
        typename std::remove_reference_t<C>::difference_type;
        typename std::remove_reference_t<C>::size_type;

        { c.cbegin() } noexcept -> std::same_as<typename std::remove_reference_t<C>::const_iterator>;
        { c.cend() } noexcept -> std::same_as<typename std::remove_reference_t<C>::const_iterator>;

        { c.size() } noexcept -> std::same_as<typename std::remove_reference_t<C>::size_type>;
        { c.empty() } noexcept -> std::same_as<bool>;
    };

template <typename It>
concept InputIterator = std::input_iterator<It>;

template <typename It, typename T>
concept ConvertibleInputIterator = InputIterator<It> && Convertible<typename It::value_type, T>;

template <typename It, typename T>
concept EqualityComparableInputIterator = InputIterator<It> && EqualityComparable<typename It::value_type, T>;

template <typename S, typename It>
concept Sentinel = std::sentinel_for<S, It>;

template <typename R>
concept Range = std::ranges::input_range<R>;

template <typename R, typename T>
concept ConvertibleRange =
    !IsSet<R> && Range<R> && Convertible<std::ranges::range_value_t<R>, T> && !Container<R>;

template <typename C, typename T>
concept ConvertibleContainer =
    !IsSet<C> && Container<C> && Convertible<typename std::remove_reference_t<C>::value_type, T>;

template <typename R, typename T>
concept EqualityComparableRange =
    !IsSet<R> && Range<R> && EqualityComparable<std::ranges::range_value_t<R>, T> && !Container<R>;

template <typename C, typename T>
concept EqualityComparableContainer =
    !IsSet<C> && Container<C> && EqualityComparable<typename std::remove_reference_t<C>::value_type, T>;

template <typename C, typename T>
concept CommonContainer =
    !IsSet<C> && Container<C> && HasCommon<typename std::remove_reference_t<C>::value_type, T>;

template <typename R, typename T>
concept CommonRange =
    !IsSet<R> && !Container<R> && Range<R> && HasCommon<typename std::remove_reference_t<R>::value_type, T>;
