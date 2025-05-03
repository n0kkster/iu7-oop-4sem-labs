#pragma once

#include "../exceptions/matrix/MatrixException.h"
#include "matrix.h"

template <ConvertibleToDouble T>
std::shared_ptr<typename Matrix<T>::MatrixRow[]> Matrix<T>::allocMatrix(size_t rows, size_t cols)
{
    std::shared_ptr<MatrixRow[]> matrix(new MatrixRow[rows]);
    try
    {
        for (size_t i = 0; i < rows; i++)
            matrix[i].reset(new T[cols], cols);
    }
    catch (std::bad_alloc &err)
    {
        throw MatrixMemoryException("Error allocating memory for matrix!");
    }
    return matrix;
}

#pragma region Constructors

template <ConvertibleToDouble T>
Matrix<T>::Matrix(size_t rows, size_t columns)
{
    this->m_rows = rows;
    this->m_cols = columns;
    this->m_matrix = this->allocMatrix(rows, columns);
}

template <ConvertibleToDouble T>
Matrix<T>::Matrix(size_t rows, size_t columns, const T &filler)
{
    this->m_rows = rows;
    this->m_cols = columns;
    this->m_matrix = allocMatrix(rows, columns);

    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < columns; ++j)
            m_matrix[i][j] = filler;
}

template <ConvertibleToDouble T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> ilist)
{
    size_t rows_cnt = ilist.size();
    auto it = ilist.begin();
    size_t cols_cnt = it->size();

    for (const auto &row : ilist)
    {
        if (row.size() != cols_cnt)
        {
            throw InvalidInitListSizeException("Wrong size of initializer row. All rows must be equal size.");
        }
    }

    this->m_rows = rows_cnt;
    this->m_cols = cols_cnt;
    this->m_matrix = allocMatrix(this->m_rows, this->m_cols);
    size_t i = 0;
    for (const auto &row : ilist)
    {
        for (const auto &elem : row)
        {
            m_matrix[i / this->m_cols][i % this->m_cols] = elem;
            i++;
        }
    }
}

template <ConvertibleToDouble T>
Matrix<T>::Matrix(const Matrix &other) : Matrix(other.m_rows, other.m_cols)
{
    for (size_t i = 0; i < this->m_rows; ++i)
        for (size_t j = 0; j < this->m_cols; ++j)
            m_matrix[i][j] = other[i][j];
}

template <ConvertibleToDouble Type>
Matrix<Type>::Matrix(Matrix &&matrix) noexcept
{
    this->m_rows = matrix.m_rows;
    this->m_cols = matrix.m_cols;
    this->m_matrix = std::move(matrix.m_matrix);
}

#pragma endregion

#pragma region Info

template <ConvertibleToDouble T>
size_t Matrix<T>::getColsCount() const noexcept
{
    return this->m_cols;
}

template <ConvertibleToDouble T>
size_t Matrix<T>::getRowsCount() const noexcept
{
    return this->m_rows;
}

#pragma endregion

#pragma region Assign

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::operator=(const Matrix &matrix)
{
    this->m_rows = matrix.m_rows;
    this->m_cols = matrix.m_cols;
    this->m_matrix = allocMatrix(matrix->m_rows, matrix->m_cols);
    for (size_t i = 0; i < m_rows; ++i)
        for (size_t j = 0; j < m_cols; ++j)
            m_matrix[i][j] = matrix[i][j];
    return *this;
}

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::operator=(Matrix<T> &&matrix) noexcept
{
    this->m_rows = matrix.m_rows;
    this->m_cols = matrix.m_cols;
    this->m_matrix = matrix.m_matrix;
    return *this;
}

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::operator=(std::initializer_list<std::initializer_list<T>> init_list)
{
    Matrix<T> tmp = Matrix(init_list);
    *this = tmp;
    return *this;
}

#pragma endregion

#pragma region Operators
template <ConvertibleToDouble T>
typename Matrix<T>::MatrixRow &Matrix<T>::operator[](size_t row)
{
    return m_matrix[row];
}

template <ConvertibleToDouble Type>
const typename Matrix<Type>::MatrixRow &Matrix<Type>::operator[](size_t row) const
{
    return m_matrix[row];
}

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::add(const Matrix<T> &other)
{
    if (other.m_rows != this->m_rows || other.m_cols != this->m_cols)
    {
        throw IncompatibleDimensionsException("Can't add two matrices: sizes are different!");
    }

    for (size_t i = 0; i < other.m_rows; i++)
        for (size_t j = 0; j < other.m_cols; j++)
            this->m_matrix[i][j] += other[i][j];

    return *this;
}

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &other)
{
    this->add(other);
    return *this;
}

template <ConvertibleToDouble T>
Matrix<T> Matrix<T>::make_sum(const Matrix<T> &other) const
{
    Matrix<T> result;
    result->add(other);
    return *result;
}

template <ConvertibleToDouble T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &other) const
{
    return this->make_sum(other);
}

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::subtract(const Matrix<T> &other)
{
    if (other.m_rows != this->m_rows || other.m_cols != this->m_cols)
        throw IncompatibleDimensionsException("Can't subtract two matrices: sizes are different!");

    for (size_t i = 0; i < other.m_rows; i++)
        for (size_t j = 0; j < other.m_cols; j++)
            this->m_matrix[i][j] -= other[i][j];

    return *this;
}

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &other)
{
    this->subtract(other);
    return *this;
}

template <ConvertibleToDouble T>
Matrix<T> Matrix<T>::make_diff(const Matrix<T> &other) const
{
    Matrix<T> result;
    result.subtract(other);
    return *result;
}

template <ConvertibleToDouble T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &other) const
{
    return this->make_diff(other);
}

template <ConvertibleToDouble Type>
Matrix<Type> Matrix<Type>::make_product(const Matrix<Type> &other) const
{
    if (m_cols != other.m_rows)
        throw IncompatibleDimensionsException("Can't multiply two matrices: sizes are incompatible!");

    Matrix<Type> result(m_rows, other.m_cols);
    for (size_t i = 0; i < m_rows; i++)
    {
        for (size_t k = 0; k < other.m_cols; k++)
        {
            result[i][k] = 0;
            for (size_t j = 0; j < this->m_cols; j++)
                result[i][k] += m_matrix[i][j] * other[j][k];
        }
    }
    return result;
}

template <ConvertibleToDouble T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &other) const
{
    return this->make_product(other);
}

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::multiply(const Matrix<T> &other)
{
    *this = this->make_product(other);
    return *this;
}

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &other)
{
    this->multiply(other);
    return *this;
}

template <ConvertibleToDouble T>
Matrix<T> Matrix<T>::make_product(const T &elem) const
{
    Matrix<T> result(*this);

    for (size_t i = 0; i < result.m_rows; i++)
        for (size_t j = 0; j < result.m_cols; j++)
            result[i][j] *= elem;

    return result;
}

template <ConvertibleToDouble T>
Matrix<T> Matrix<T>::operator*(const T &elem) const
{
    return this->make_product(elem);
}

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::multiply(const T &elem) noexcept
{
    for (size_t i = 0; i < this->m_rows; i++)
        for (size_t j = 0; j < this->m_cols; j++)
            this->m_matrix[i][j] *= elem;

    return *this;
}

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::operator*=(const T &elem) noexcept
{
    return this->multiply(elem);
}

#pragma endregion
