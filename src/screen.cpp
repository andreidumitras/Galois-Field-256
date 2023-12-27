#include "gf256.hpp"

Screen::Screen()
{
    short i;
    short j;

    // fill the entire panel with spaces
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS - 1; j++)
            panel[i][j] = ' ';
        panel[i][j] = '\0';
    }
}

void Screen::draw_pattern(short line, short start, char chr, short step, short amount)
{
    // std::cout << "line = " << line << '\n';
    for (short k = start; k < start + (amount * step); k += step)
        panel[line][k] = chr;
    // system("cls");
    // show();
}

void Screen::draw_content(short line, short start, char *data)
{
    short k;
    short i;

    for (k = start, i = 0; data[i]; i++, k += 5)
        panel[line][k] = data[i];
    // system("cls");
    // show();
}

void Screen::show(short n)
{
    short i;
    short j;
    for (i = 0; i < n && i < ROWS; i++)
    {
        for (j = 0; j < COLS - 1; j++)
            std::cout << panel[i][j];
        std::cout << std::endl;
    }
}

void Screen::draw_text(short line, short start, const char *text)
{
    short i;
    short j;

    i = 0;
    j = start;
    while (text[i])
    {
        panel[line][j] = text[i];
        i++;
        j++;
    }
}

void Screen::next()
{
    getch();
    system("cls");
}