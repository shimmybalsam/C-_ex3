//
// Created by Shimmy on 1/10/2019.
//

#ifndef EX3_MATRIX_H
#define EX3_MATRIX_H

#include <vector>
#include <iostream>
#include "Complex.h"

#define BAD_INDEX "index out of bounds"
#define BAD_ALLOC "illegal allocation"
#define BAD_DIMS_ADD "Cannot apply addition on matrices with different dims"
#define BAD_DIMS_SUB "Cannot apply subtraction on matrices with different dims"
#define BAD_DIMS_MULT "bad dims for multiplication"
#define NON_SQUARE_TRANS "cannot transpose non-square matrix"

#define TAB "\t"
#define NEW_LINE "\n"
using namespace std;

/**
 * Matrix class
 * @tparam T generic type of Matrix
 */
template <class T>
class Matrix
{
public:

    /**
     * Default constructor, initializes a 1X1 Matrix with a 0 in it.
     */
    Matrix()
    {
        _mat = vector<T>(1, 0);
        _n_rows = 1;
        _m_cols = 1;
    }

    /**
     * Constructor a matrix of zeros size (given) rows*cols
     * throws bad alloc if given rows or cols are zero or negative
     * @param rows amount of rows
     * @param cols amount of columns
     */
    Matrix(unsigned int rows, unsigned int cols)
    {
        if (rows > 0 && rows < 32769 && cols > 0 && cols < 32769)
        {
            _n_rows = rows;
            _m_cols = cols;
            _mat = vector<T>(rows * cols, 0);
        }
        else
        {
            throw length_error(BAD_ALLOC);
        }
    }

    /**
     * default destructor (due to rule of three).
     */
    ~Matrix() = default;


    /**
     * default copy constructor (due to rule of three)
     * @param other , matrix to be copied.
     */
    Matrix(const Matrix &other) = default;

    /**
     * Constructor copying values from a vector
     * throws bad alloc if given rows or cols are zero or negative or if their dims dont amount
     * to vector size.
     * @param rows amount of rows for new matrix
     * @param cols amount of columns for new matrix
     * @param cells the vector from which to copy the values
     */
    Matrix(unsigned int rows, unsigned int cols, const vector<T>&cells)
    {
        if (cells.size() == rows * cols && rows > 0 && rows < 32769 && cols > 0 && cols < 32769)
        {
            _n_rows = rows;
            _m_cols = cols;
            _mat = vector<T>(rows * cols, 0);
            for (unsigned int i = 0; i < rows * cols; i++)
            {
                _mat[i] = cells[i];
            }
        }
        else
        {
            throw length_error(BAD_ALLOC);
        }
    }

    /**
     * default operator= (due to rule of three)
     * @param other matrix to copy values from
     * @return Matrix with copied values
     */
    Matrix &operator=(const Matrix &other) = default;

    /**
     * addition between two matrices
     * throws exception if matrices dont have the same dims
     * @param other second matrix to add to current matrix
     * @return new matrix which is the result of the addition
     */
    Matrix operator+(const Matrix &other)
    {
        if (_n_rows == other._n_rows && _m_cols == other._m_cols)
        {
            Matrix m = Matrix(_n_rows, _m_cols);
            for (unsigned int i = 0; i < _n_rows * _m_cols; i++)
            {
                m._mat[i] = _mat[i] + other._mat[i];
            }
            return m;
        }
        else
        {
            throw length_error(BAD_DIMS_ADD);
        }
    }

    /**
     *
     * subtraction between two matrices
     * throws exception if matrices dont have the same dims
     * @param other second matrix to sub from current matrix
     * @return new matrix which is the result of the subtraction
     */
    Matrix operator-(const Matrix &other)
    {
        if (_n_rows == other._n_rows && _m_cols == other._m_cols)
        {
            Matrix m = Matrix(_n_rows, _m_cols);
            for (unsigned int i = 0; i < _n_rows * _m_cols; i++)
            {
                m._mat[i] = _mat[i] - other._mat[i];
            }
            return m;
        }
        else
        {
            throw length_error(BAD_DIMS_SUB);

        }
    }

    /**
     * multiplication of two matrices
     * throws exception if matrices dont have the correct dims for multiplying
     * @param other second matrix to multiply with current matrix
     * @return new matrix which is the result of the multiplication
     */
    Matrix operator*(const Matrix &other)
    {
        if (_m_cols == other._n_rows)
        {
            Matrix m = Matrix(_n_rows, other._m_cols);
            for (unsigned int i = 0; i < _n_rows; i++)
            {
                for (unsigned int j = 0; j < other._m_cols; j++)
                {
                    T sum = 0;
                    for (unsigned int k = 0; k < _m_cols; k++)
                    {
                        int temp1 = i * _m_cols + k;
                        int temp2 = k * other._m_cols + j;
                        sum += _mat[temp1] * other._mat[temp2];
                    }
                    m(i, j) = sum;
                }
            }
            return m;
        }
        else
        {
            throw length_error(BAD_DIMS_MULT);
        }
    }

    /**
     * checks if two matrices are the same
     * @param other second matrix to compare to
     * @return true if both matrices are the same, false otherwise
     */
    bool operator==(const Matrix &other)
    {
        if (_mat.size() != other._mat.size())
        {
            return false;
        }
        if (_n_rows != other._n_rows)
        {
            return false;
        }
        if (_m_cols != other._m_cols)
        {
            return false;
        }
        for (unsigned int i = 0; i < _n_rows * _m_cols; i++)
        {
            if (_mat[i] != other._mat[i])
            {
                return false;
            }
        }
        return true;
    }

    /**
     *
     * checks if two matrices are different
     * @param other second matrix to compare to
     * @return true if matrices are different, false otherwise
     */
    bool operator!=(const Matrix &other)
    {
        if (_mat.size() != other._mat.size())
        {
            return true;
        }
        if (_n_rows != other._n_rows)
        {
            return true;
        }
        if (_m_cols != other._m_cols)
        {
            return true;
        }
        for (unsigned int i = 0; i < _n_rows * _m_cols; i++)
        {
            if (_mat[i] != other._mat[i])
            {
                return true;
            }
        }
        return false;
    }

    /**
     * gets value of matrix at given indexes
     * throws out of range exception if given indexes are out of the matrix bounds
     * @param row index of row in matrix
     * @param col index of column in matrix
     * @return the value at (row, col) of matrix
     */
    T operator()(unsigned int row, unsigned int col) const
    {
        if (row < _n_rows && row >= 0 && col < _m_cols && col >= 0)
        {
            return _mat[row * _m_cols + col];
        }
        else
        {
            throw out_of_range(BAD_INDEX);
        }
    }

    /**
     * gets pointer to value of matrix at given indexes
     * throws out of range exception if given indexes are out of the matrix bounds
     * @param row index of row in matrix
     * @param col index of column in matrix
     * @return pointer to (row, col) of matrix
     */
    T &operator()(unsigned int row, unsigned int col)
    {
        if (row < _n_rows && row >= 0 && col < _m_cols && col >= 0)
        {
            return _mat[row * _m_cols + col];
        }
        else
        {
            throw out_of_range(BAD_INDEX);
        }
    }

    /**
     * checks if matris is square
     * @return true if square, false otherwise
     */
    bool isSquareMatrix() const
    {
        return _n_rows == _m_cols;
    }

    /**
     * prints to stream the values of matrix
     * @param out the out stream
     * @param m the matrix to print
     * @return the out stream after matrix values were added
     */
    friend ostream &operator<<(ostream &out, const Matrix &m)
    {
        for (unsigned int i = 0; i < m._n_rows; i++)
        {
            for (unsigned int j = 0; j < m._m_cols; j++)
            {
                out << m._mat[i * m._m_cols + j] << TAB;
            }
            out << NEW_LINE;
        }
        return out;
    }
    
    typedef typename vector<T>::const_iterator const_iterator;

    /**
     * getting an iterator at the start of the matrix
     * @return const_iterator
     */
    const_iterator begin()
    {
        return _mat.cbegin();
    }

    /**
     * getting an iterator at the start of the matrix
     * @return const_iterator
     */
    const_iterator end()
    {
        return _mat.cend();
    }

    /**
     * get amount of rows in matrix
     * @return amount of rows
     */
    unsigned int rows()
    {
        return _n_rows;
    }

    /**
     * get amount of columns in matrix
     * @return amount of columns
     */
    unsigned int cols()
    {
        return _m_cols;
    }

    /**
     * transposes the matrix
     * throws invalid argument exception if matrix is non-square.
     * @return a new matrix which is the transpose of the current (this)
     */
    Matrix trans() const
    {
        if (isSquareMatrix())
        {
            unsigned int new_rows = _m_cols;
            unsigned int new_cols = _n_rows;
            Matrix m_trans = Matrix(new_rows, new_cols);
            for (unsigned int i = 0; i <new_rows; i++)
            {
                for (unsigned int j = 0; j < new_cols; j++)
                {
                    m_trans(i, j) = _mat[j * _m_cols + i];
                }
            }

            return m_trans;
        }
        else
        {
            throw invalid_argument(NON_SQUARE_TRANS);
        }
    }
    
private:
    vector<T> _mat; // the matrix data structure
    unsigned int _n_rows, _m_cols; // num of rows and cols of matrix
};

/**
 * transposes matrix in the specific case in which the matrix is of type Complex
 * throws invalid argument exception if matrix is non-square.
 * @return a new matrix which is the transpose of the current (this)
 */
template<>
Matrix<Complex> Matrix<Complex>::trans() const
{
    if (isSquareMatrix())
    {
        unsigned int new_rows = _m_cols;
        unsigned int new_cols = _n_rows;
        Matrix m_conj = Matrix(new_rows, new_cols);
        for (unsigned int i = 0; i <new_rows; i++)
        {
            for (unsigned int j = 0; j < new_cols; j++)
            {
                m_conj(i, j) = _mat[j * _m_cols + i].conj();
            }
        }

        return m_conj;

    }
    else
    {
        throw invalid_argument(NON_SQUARE_TRANS);
    }

}
#endif //EX3_MATRIX_H
