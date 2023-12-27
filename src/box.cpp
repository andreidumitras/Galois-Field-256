#include "gf256.hpp"

Box::Box(short ibox, short jbox, short hbox)
{
    this->ibox = ibox;
    this->jbox = jbox;
    this->hbox = hbox;
}

void Box::draw_box(Screen &screen)
{
    short k;

    screen.panel[ibox][jbox] = '+';
    screen.panel[ibox][jbox + 1] = '-';
    screen.panel[ibox][jbox + 2] = '-';
    screen.panel[ibox][jbox + 3] = '-';
    screen.panel[ibox][jbox + 4] = '+';
    for (k = 1; k < hbox*2; k += 2)
    {
        screen.panel[ibox + k][jbox] = '|';
        screen.panel[ibox + k][jbox + 4] = '|';
    }
    k--;
    screen.panel[ibox + k][jbox] = '+';
    screen.panel[ibox + k][jbox + 1] = '-';
    screen.panel[ibox + k][jbox + 2] = '-';
    screen.panel[ibox + k][jbox + 3] = '-';
    screen.panel[ibox + k][jbox + 4] = '+';
}

void Box::hide_box(Screen &screen)
{
    short k;

    screen.panel[ibox][jbox] = '-';
    screen.panel[ibox][jbox + 1] = ' ';
    screen.panel[ibox][jbox + 2] = '-';
    screen.panel[ibox][jbox + 3] = ' ';
    screen.panel[ibox][jbox + 4] = '-';
    for (k = 1; k < hbox*2; k += 2)
    {
        screen.panel[ibox + k][jbox] = ' ';
        screen.panel[ibox + k][jbox + 4] = ' ';
    }
    k--;
    screen.panel[ibox + k][jbox] = '-';
    screen.panel[ibox + k][jbox + 1] = ' ';
    screen.panel[ibox + k][jbox + 2] = '-';
    screen.panel[ibox + k][jbox + 3] = ' ';
    screen.panel[ibox + k][jbox + 4] = '-';
}

void Box::redraw_box(Screen &screen, short newi, short newj, short newh)
{
    hide_box(screen);
    ibox = newi;
    jbox = newj;
    hbox = newh;
    draw_box(screen);
}