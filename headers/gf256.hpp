#pragma once

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "matrix.hpp"
#include "bits.hpp"
#include "screen.hpp"
#include "box.hpp"

class GF256
{
private:
    void digit_by_digit();
    void xor_all();
    void polynomial_div();

public:
    Bits *octet1;
    Bits *octet2;
    Bits *product;
    Bits *divider;
    Bits *reminder;
    Matrix *multiplication;
    Matrix *division;
    Screen screen;
    Box *b1;
    Box *b2;

    GF256(char *octet1, char *octet2, char *divider);
    ~GF256();
    void compute();
    void display();
};