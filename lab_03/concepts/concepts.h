#pragma once 

#include <concepts>
#include <utility>

template <typename Derived, typename Base>
concept Derivative = std::is_abstract_v<Base> && std::is_base_of_v<Base, Derived>;

template <typename Type>
concept NotAbstract = !std::is_abstract_v<Type>;

template <typename Type>
concept DefaultConstructible = std::is_default_constructible_v<Type>;

template <typename T, typename... Args>
concept ConstructibleWith = requires(Args &&...args) { T{ std::forward<Args>(args)... }; };

template <typename T>
concept ConvertibleToDouble = (std::same_as<T, double> || std::convertible_to<T, double>);

template <typename T, typename... Supported>
concept IsSupportedArg = (std::is_convertible_v<T, Supported> || ...);;