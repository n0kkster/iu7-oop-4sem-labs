#pragma once

#include "../exceptions/matrix/MatrixException.h"
#include "matrix.h"

#include <QDebug>
#include <iostream>

#pragma region MatrixRow

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

template <ConvertibleToDouble T>
T &Matrix<T>::MatrixRow::operator[](size_t index)
{
    if (index >= m_size)
        throw MatrixOutOfRangeException("Column index out of range!");

    return m_row[index];
}

template <ConvertibleToDouble T>
const T &Matrix<T>::MatrixRow::operator[](size_t index) const
{
    if (index >= m_size)
        throw MatrixOutOfRangeException("Column index out of range!");

    return m_row[index];
}

template <ConvertibleToDouble T>
void Matrix<T>::MatrixRow::reset(T *row, const size_t size)
{
    m_size = size;
    m_row.reset(row);
}

template <ConvertibleToDouble T>
void Matrix<T>::MatrixRow::reset()
{
    m_size = 0;
    m_row.reset();
}

#pragma endregion

#pragma region Constructors

template <ConvertibleToDouble T>
Matrix<T>::Matrix(size_t rows, size_t columns)
{
    m_rows = rows;
    m_cols = columns;
    m_matrix = allocMatrix(rows, columns);
}

template <ConvertibleToDouble T>
Matrix<T>::Matrix(size_t rows, size_t columns, const T &filler)
{
    m_rows = rows;
    m_cols = columns;
    m_matrix = allocMatrix(rows, columns);

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

    m_rows = rows_cnt;
    m_cols = cols_cnt;
    m_matrix = allocMatrix(m_rows, m_cols);
    size_t i = 0;
    for (const auto &row : ilist)
    {
        for (const auto &elem : row)
        {
            m_matrix[i / m_cols][i % m_cols] = elem;
            i++;
        }
    }
}

template <ConvertibleToDouble T>
Matrix<T>::Matrix(const Matrix &other) : Matrix(other.m_rows, other.m_cols)
{
    for (size_t i = 0; i < m_rows; ++i)
        for (size_t j = 0; j < m_cols; ++j)
            m_matrix[i][j] = other[i][j];
}

template <ConvertibleToDouble Type>
Matrix<Type>::Matrix(Matrix &&matrix) noexcept
{
    m_rows = matrix.m_rows;
    m_cols = matrix.m_cols;
    m_matrix = std::move(matrix.m_matrix);
}

#pragma endregion

#pragma region Info

template <ConvertibleToDouble T>
size_t Matrix<T>::getColsCount() const noexcept
{
    return m_cols;
}

template <ConvertibleToDouble T>
size_t Matrix<T>::getRowsCount() const noexcept
{
    return m_rows;
}

#pragma endregion

#pragma region Assign

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::operator=(const Matrix &matrix)
{
    m_rows = matrix.m_rows;
    m_cols = matrix.m_cols;
    m_matrix = allocMatrix(matrix.m_rows, matrix.m_cols);
    for (size_t i = 0; i < m_rows; ++i)
        for (size_t j = 0; j < m_cols; ++j)
            m_matrix[i][j] = matrix[i][j];
    return *this;
}

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::operator=(Matrix<T> &&matrix) noexcept
{
    m_rows = matrix.m_rows;
    m_cols = matrix.m_cols;
    m_matrix = matrix.m_matrix;
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
    if (row >= m_rows)
        throw MatrixOutOfRangeException("Row index out of range!");

    return m_matrix[row];
}

template <ConvertibleToDouble Type>
const typename Matrix<Type>::MatrixRow &Matrix<Type>::operator[](size_t row) const
{
    if (row >= m_rows)
        throw MatrixOutOfRangeException("Row index out of range!");
    
    return m_matrix[row];
}

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::add(const Matrix<T> &other)
{
    if (other.m_rows != m_rows || other.m_cols != m_cols)
    {
        throw IncompatibleDimensionsException("Can't add two matrices: sizes are different!");
    }

    for (size_t i = 0; i < other.m_rows; i++)
        for (size_t j = 0; j < other.m_cols; j++)
            m_matrix[i][j] += other[i][j];

    return *this;
}

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &other)
{
    add(other);
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
    return make_sum(other);
}

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::subtract(const Matrix<T> &other)
{
    if (other.m_rows != m_rows || other.m_cols != m_cols)
        throw IncompatibleDimensionsException("Can't subtract two matrices: sizes are different!");

    for (size_t i = 0; i < other.m_rows; i++)
        for (size_t j = 0; j < other.m_cols; j++)
            m_matrix[i][j] -= other[i][j];

    return *this;
}

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &other)
{
    subtract(other);
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
    return make_diff(other);
}

template <ConvertibleToDouble T>
Matrix<T> Matrix<T>::make_product(const Matrix<T> &other) const
{
    if (m_cols != other.m_rows)
        throw IncompatibleDimensionsException("Can't multiply two matrices: sizes are incompatible!");

    Matrix<T> result(m_rows, other.m_cols);
    for (size_t i = 0; i < m_rows; i++)
    {
        for (size_t k = 0; k < other.m_cols; k++)
        {
            result[i][k] = 0;
            for (size_t j = 0; j < m_cols; j++)
                result[i][k] += m_matrix[i][j] * other[j][k];
        }
    }
    return result;
}

template <ConvertibleToDouble T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &other) const
{
    return make_product(other);
}

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::multiply(const Matrix<T> &other)
{
    *this = make_product(other);
    return *this;
}

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &other)
{
    multiply(other);
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
    return make_product(elem);
}

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::multiply(const T &elem) noexcept
{
    for (size_t i = 0; i < m_rows; i++)
        for (size_t j = 0; j < m_cols; j++)
            m_matrix[i][j] *= elem;

    return *this;
}

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::operator*=(const T &elem) noexcept
{
    return multiply(elem);
}

#pragma endregion

template <ConvertibleToDouble T>
QDebug &operator<<(QDebug &os, const Matrix<T> &matrix)
{
    os << "[";
    for (size_t i = 0; i < matrix.getRowsCount(); ++i)
    {
        for (size_t j = 0; j < matrix.getColsCount() - 1; ++j)
        {
            os << matrix[i][j] << ", ";
        }
        os << matrix[i][matrix.getColsCount() - 1] << "\n";
    }
    os << "]";

    return os;
}


template <ConvertibleToDouble T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix)
{
    os << "[";
    for (size_t i = 0; i < matrix.getRowsCount(); ++i)
    {
        for (size_t j = 0; j < matrix.getColsCount() - 1; ++j)
        {
            os << matrix[i][j] << ", ";
        }
        os << matrix[i][matrix.getColsCount() - 1] << "\n";
    }
    os << "]";

    return os;
}
