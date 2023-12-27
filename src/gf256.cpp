#include "gf256.hpp"

// static function
static char xor_char(char a, char b)
{
    return a == b? '0': '1';
}

void GF256::polynomial_div()
{
    short im;
    short jm;
    short km;
    bool over = false;

    // put the product in the first line to initialize the process
    for (short i = 0; i < product->length; i++)
        division->matrix[0][i] = product->array[i];
    im = 0;
    jm = 0;
    while (!over)
    {
        // jump over the zeros from the begining
        for (; division->matrix[im][jm] == '0'; jm++);
        
        // check if the divider fits inside the matrix
        if (jm + 9 <= division->cols)
        {
            // put the divider under the number
            km = jm;
            for (short id = 0; id < divider->length && km < division->cols; id++, km++)
                division->matrix[im + 1][km] = divider->array[id];

            // descend the complementary digits
            for (short c = km - 1; division->matrix[im][c] == '.'; c--)
                division->matrix[im][c] = division->matrix[0][c];

            // xor the 2 numbers and place the result below
            km = jm;
            for (short id = 0; id < divider->length; id++, km++)
                division->matrix[im + 2][km] = xor_char(division->matrix[im][km], division->matrix[im + 1][km]);
            im += 2;
            if (jm + 9 == division->cols)
                over = true;
        }
        else
        {
            // descend the complementary digits
            km = division->cols;
            for (short c = km - 1; division->matrix[im][c] == '.'; c--)
                division->matrix[im][c] = division->matrix[0][c];   
            over = true;
        }
    }
    km--;
    for (jm = reminder->length - 1; jm >= 0; jm--, km--)
        reminder->array[jm] = division->matrix[im][km];
        
    // deleting the remaining unused rows
    division->rows = im + 1;
    for (im = im + 1; division->matrix[im]; im++)
        delete[] division->matrix[im];
}

void GF256::xor_all()
{
    char result;
    short jm;
    short im;
    for (jm = multiplication->cols - 1; jm >= 0; jm--)
    {
        if (multiplication->matrix[0][jm] == '.')
            result = '0';
        else
            result = multiplication->matrix[0][jm];
        for (im = 1; im < multiplication->rows; im++)
        {
            if (multiplication->matrix[im][jm] == '.')
                result = xor_char(result, '0');
            else
                result = xor_char(result, multiplication->matrix[im][jm]);
        }
        product->array[jm] = result;
    }
}

void GF256::digit_by_digit()
{
    short im = 0;
    short jm = multiplication->cols - 1;
    short km;
    for (short i = octet2->length - 1; i >= 0 && multiplication->matrix[im]; i--)
    {
        if (octet2->array[i] == '1')
        {
            km = jm;
            for (short j = octet1->length - 1; j >= 0; j--)
                multiplication->matrix[im][km--] = octet1->array[j];
            im++;
        }
        jm--;
    }
}

GF256::GF256(char *octet1, char *octet2, char *divider)
{
    // aloca octetii, aloca matricele
    this->octet1 = new Bits(8);
    this->octet2 = new Bits(8);
    this->product = new Bits(15);
    this->divider = new Bits(9);
    this->reminder = new Bits(8);

    this->octet1->fill(octet1);
    this->octet2->fill(octet2);
    this->divider->fill(divider);

    this->multiplication = new Matrix(this->octet2->count_ones(), product->length);
    this->division = new Matrix((product->length - this->divider->length) * 2 + 1, product->length);
}

GF256::~GF256()
{
    delete octet1;
    delete octet2;
    delete product;
    delete divider;
    delete reminder;
    delete multiplication;
    delete division;
}

void GF256::compute()
{
    digit_by_digit();
    xor_all();
    polynomial_div();
}

void GF256::display()
{
    short line = 0;
    short i;
    short j;
    short k;

// multiplication panel
    screen.next();
    screen.draw_text(line++, 0, "First, we will multiply the octets digit by digit:");
    line++;
    screen.draw_pattern(line++, 52, '-', 2, 21);
    screen.draw_text(line, 43, "Octet1:");
    screen.draw_content(line, 54, octet1->array);
    screen.panel[line++][96] = '*';
    screen.draw_pattern(line++, 52, '-', 2, 21);
    screen.draw_text(line, 43, "Octet2:");
    screen.draw_content(line++, 54, octet2->array);
    screen.draw_pattern(line++, 52, '-', 2, 21);
    screen.show(line);

    screen.next();
    screen.draw_pattern(line++, 10, '=', 1, 83);
    screen.show(line);
    
    b1 = new Box(2, 87, 1);
    b2 = new Box(4, 87, 1);
    b1->draw_box(screen);
    b2->draw_box(screen);

// digit by digit
    for (i = octet2->length - 1; i >= 0; i--)
    {
        if (octet2->array[i] == '1')
        {
            screen.draw_pattern(line++, 17, '-', 2, 38);
            for (j = octet1->length - 1; j >= 0; j--)
            {
                b1->redraw_box(screen, 2, 5*j + 52, 1);
                b2->redraw_box(screen, 4, 5*i + 52, 1);
                screen.panel[line][(5*j + 54) - (-5*i + 35)] = octet1->array[j];
                screen.next();
                screen.show(line + 1);
            }
            line++;
            b1->hide_box(screen);
        }
        else
        {
            b2->redraw_box(screen, 4, 5*i + 52, 1);
            screen.next();
            screen.show(line + 1);
        }
    }
    screen.draw_pattern(line++, 17, '-', 2, 38);
    b1->hide_box(screen);
    b2->hide_box(screen);
    screen.draw_pattern(line++, 10, '=', 1, 83);

// vertical XOR
    short start;
    short amount;
    screen.draw_text(9, 96, "XOR");
    for (i = product->length - 1; i >= 0; i--)
    {
        start = 0;
        amount = 0;
        j = 0;
        for (start = 0; (start < multiplication->rows) && (multiplication->matrix[start][i] == '.'); start++);
        for (k = 0; k < multiplication->rows; k++)
            if (multiplication->matrix[k][i] != '.')
                amount++;
        if (amount != 0)
            b1->redraw_box(screen, 8 + start * 2, 5*i + 17, amount);
        screen.panel[line][5*i + 19] = product->array[i];
        screen.next();
        screen.show(line + 1);
    }
    b1->hide_box(screen);
    line += 2;

// polynomial division
    screen.draw_text(line++, 0, "Now, the polynomial division (via XOR):");
    screen.next();
    screen.show(line + 1);
    screen.draw_pattern(line, 2, '-', 2, 62);
    screen.panel[line++][80] = '|';
    screen.draw_content(line, 5, product->array);
    screen.panel[line][80] = '|';
    start = line - 1;
    screen.draw_content(line++, 83, divider->array);
    screen.draw_pattern(line, 2, '-', 2, 62);
    screen.panel[line++][80] = '|';
    screen.next();
    screen.show(line + 1);

// XOR one by one
    for (i = 1; i < division->rows; i += 2)
    {
        for (j = 0; division->matrix[i][j] == '.' || division->matrix[i][j] == '0'; j++);
        screen.draw_content(line, 5*j + 5, divider->array);
        screen.panel[line++][80] = '|';
        screen.draw_pattern(line, 2, '-', 2, 40);
        screen.panel[line++][80] = '|';
        for (; division->matrix[i][j] != '\0' && division->matrix[i][j] != '.'; j++)
        {
            b1->redraw_box(screen, line - 5, 5*j + 3, 2);
            screen.panel[line][5*j + 5] = division->matrix[i + 1][j];
            screen.next();
            screen.show(line + 1);
        }
        for (; division->matrix[i + 1][j] != '\0' && division->matrix[i + 1][j] != '.'; j++)
        {
            b1->redraw_box(screen, start, 5*j + 3, 1);
            screen.panel[line][5*j + 5] = division->matrix[i + 1][j];
            screen.next();
            screen.show(line + 1);
        }
        screen.panel[line++][80] = '|';
        screen.draw_pattern(line, 2, '-', 2, 40);
        screen.panel[line++][80] = '|';
    }
    line++;
    b1->hide_box(screen);
    screen.next();
    screen.show(line + 1);
}