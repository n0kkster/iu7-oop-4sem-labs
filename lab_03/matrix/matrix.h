#pragma once
#include <concepts>

template <typename T>
concept ConvertibleToDouble = (std::same_as<T, double> || std::convertible_to<T, double>);

template <ConvertibleToDouble T>
class Matrix
{
    
};