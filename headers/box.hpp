#pragma once

#include "gf256.hpp"

class Box
{
public:
    short ibox;
    short jbox;
    short hbox;

    Box(short ibox, short jbox, short hbox);
    void draw_box(Screen &screen);
    void hide_box(Screen &screen); 
    void redraw_box(Screen &screen, short newi, short newj, short newheigth);
};