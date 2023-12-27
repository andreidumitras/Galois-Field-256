#include "gf256.hpp"

Matrix::Matrix(short rows, short cols)
{
    this->rows = rows;
    this->cols = cols;

    matrix = new char*[rows + 1];
    for (short i = 0; i < rows; i++)
    {
        matrix[i] = new char[cols + 1];
        for (short j = 0; j < cols; j++)
            matrix[i][j] = '.';
        matrix[i][cols] = '\0';
    }
    matrix[rows] = NULL;
}

Matrix::~Matrix()
{
    for (short i = 0; i < rows; i++)
        delete[] matrix[i];
    delete[] matrix;
}

void Matrix::show_matrix()
{
    std::cout << "Matrix:\n";
    for (short i = 0; i < rows; i++)
    {
        for (short j = 0; j < cols; j++)
            std::cout << " " << matrix[i][j];
        std::cout << "\n";
    } 
}
