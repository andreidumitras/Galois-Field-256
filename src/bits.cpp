#include "gf256.hpp"

Bits::Bits(short amount)
{
    length = amount;
    array = new char[length + 1];
    for (short i = 0; i < length; i++)
        array[i] = '0';
    array[length] = '\0';
}

Bits::~Bits()
{
    delete[] array;
}

short Bits::count_ones()
{
    short count = 0;
    for (short i = 0; i < length; i++)
        if (array[i] == '1')
            count++;
    return count;
}

void Bits::show_bits()
{
    std::cout << "Bits: \n";
    for (short i = 0; i < length; i++)
        std::cout << " " << array[i];
    std::cout << "\n";
}

void Bits::fill(char *bits)
{
    for (short i = 0; i < length; i++)
        array[i] = bits[i];
}
