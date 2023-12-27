#pragma once

#include "gf256.hpp"

#define ROWS 65
#define COLS 130

class Screen
{
public:
    char panel[ROWS][COLS];

    Screen();
    void draw_pattern(short line, short start, char chr, short step, short amount);
    void draw_content(short line, short start, char *data);
    void draw_text(short line, short start, const char *text);
    void show(short n);
    void next();
};
