#pragma once

#include "gf256.hpp"

class Matrix
{
public:
    char **matrix;
    short rows;
    short cols;

    Matrix(short rows, short cols);
    ~Matrix();
    void show_matrix();
};
