#pragma once

#include <algorithm>
#include <iostream>

class Matrix {
    int _size;
    double* array;

public:
    explicit Matrix(int size)
        : _size(size)
    {
        array = new double [size * size];
        std::fill(array, array + (size * size), 0);
    }

    ~Matrix()
    {
        delete[] array;
    }

    Matrix(const Matrix& other)
    {
        _size = other._size;
        std::copy(other.array, other.array + other._size, array);
    }

    Matrix& operator=(const Matrix& other)
    {
        if (&other != this) {
            _size = other._size;
            std::copy(other.array, other.array + other._size, array);
        }
        return *this;
    }

    int GetSize() const
    {
        return _size;
    }

    double& operator()(int x, int y) const
    {
#ifdef DEBUG
        return at(x, y);
#else
        return array[x + y * _size];
#endif
    }

    double& operator()(int x, int y)
    {
#ifdef DEBUG
        return at(x, y);
#else
        return array[x + y * _size];
#endif
    }

    double& at(int x, int y) const
    {
        if (x >= _size) {
            throw std::out_of_range("Array out of bound");
        }
        if (y >= _size) {
            throw std::out_of_range("Array out of bound");
        }
        return array[x + y * _size];
    }

    double& at(int x, int y)
    {
        if (x >= _size) {
            throw std::out_of_range("Array out of bound");
        }
        if (y >= _size) {
            throw std::out_of_range("Array out of bound");
        }
        return array[x + y * _size];
    }
};
