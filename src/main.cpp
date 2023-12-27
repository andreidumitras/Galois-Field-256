#include "gf256.hpp"

std::string get_hexa(char *a)
{
    std::string result = "";
    short i;
    short power;
    short value;
    char hexa[] = "0123456789ABCDEF";
    short values[] = {1, 2, 4, 8};

    power = 3;
    value = 0;
    for (i = 0; i < 4; i++)
    {
        if (a[i] == '1')
            value += values[power];
        power--;
    }
    result += hexa[value];
    power = 3;
    value = 0;
    for (; i < 8; i++)
    {
        if (a[i] == '1')
            value += values[power];
        power--;
    }
    result += hexa[value];
    return result;
}

int main(int ac, char **av)
{
    char div[] = "100011011";

    GF256 gf256(av[1], av[2], div);
    gf256.compute();
    gf256.display();
    std::cout << "The conclusion:\n";
    std::cout << "\x1B[31m" << get_hexa(av[1])
              << "\033[0m * \x1B[31m"
              << get_hexa(av[2]) << "\033[0m = "
              << "\x1B[32m" << get_hexa(gf256.reminder->array) << "\033[0m\n\n";
    return 0;
}