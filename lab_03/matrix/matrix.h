#pragma once
#include <initializer_list>

#include <concepts>
#include <cstddef>
#include <memory>

template <typename T>
concept ConvertibleToDouble = (std::same_as<T, double> || std::convertible_to<T, double>);

template <ConvertibleToDouble T>
class Matrix
{
protected:
#pragma region MatrixRow

    class MatrixRow
    {
    private:
        std::shared_ptr<T[]> row;
        size_t size;

    public:
        MatrixRow(T *row, const size_t size) : row(row), size(size) { }

        MatrixRow() : row(nullptr), size(0) { }

        T &operator[](size_t index);
        const T &operator[](size_t index) const;
        void reset();
        void reset(T *row, size_t size);
    };

#pragma endregion

private:
    std::shared_ptr<MatrixRow[]> m_matrix = nullptr;
    std::shared_ptr<MatrixRow[]> allocMatrix(size_t rows, size_t cols);

    size_t m_rows, m_cols;

public:
#pragma region Constructors
    Matrix() = delete;
    Matrix(size_t rows, size_t cols);
    Matrix(size_t rows, size_t cols, const T &filler);
    Matrix(std::initializer_list<std::initializer_list<T>> ilist);

    Matrix(const Matrix<T> &other);
    Matrix(Matrix<T> &&other) noexcept;
#pragma endregion

#pragma region Destructor
    ~Matrix() = default;
#pragma endregion

#pragma region Info
    size_t getColsCount() const noexcept;
    size_t getRowsCount() const noexcept;
#pragma endregion

#pragma region Assign
    Matrix<T> &operator=(const Matrix<T> &other);
    Matrix<T> &operator=(Matrix<T> &&other) noexcept;
    Matrix<T> &operator=(std::initializer_list<std::initializer_list<T>> ilist);
#pragma endregion

#pragma region Operators
    Matrix<T> make_sum(const Matrix<T> &other) const;
    Matrix<T> operator+(const Matrix<T> &other) const;

    Matrix<T> &add(const Matrix<T> &other);
    Matrix<T> &operator+=(const Matrix<T> &other);

    Matrix<T> make_diff(const Matrix<T> &other) const;
    Matrix<T> operator-(const Matrix<T> &other) const;

    Matrix<T> &subtract(const Matrix<T> &other);
    Matrix<T> &operator-=(const Matrix<T> &other);

    Matrix<T> make_product(const Matrix<T> &other) const;
    Matrix<T> operator*(const Matrix<T> &other) const;

    Matrix<T> &multiply(const Matrix<T> &other);
    Matrix<T> &operator*=(const Matrix<T> &other);

    Matrix<T> make_product(const T &elem) const;
    Matrix<T> operator*(const T &elem) const;
    
    Matrix<T> &multiply(const T &elem) noexcept;
    Matrix<T> &operator*=(const T &elem) noexcept;

    // Matrix<T> negate() const;
    // Matrix<T> operator-() const;

    MatrixRow &operator[](size_t row);
    const MatrixRow &operator[](size_t row) const;
#pragma endregion

// #pragma region MathOperations
//     T determinant() const;
//     Matrix<T> getTransposed() const;
//     Matrix<T> getAdjoint() const;
//     Matrix<T> getInverse() const;
// #pragma endregion
};

#include "matrix.hpp"
