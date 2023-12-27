#pragma once

#include "gf256.hpp"

class Bits
{
public:
    char *array;
    short length;

    Bits(short amount);
    ~Bits();
    short count_ones();
    void show_bits();
    void fill(char *bits);
};