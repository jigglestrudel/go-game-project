#include <stdio.h>
#include <stdlib.h>
#include "conio2.h"

#define LEGEND_X 2
#define LEGEND_Y 2

#define BOARD_X 35
#define BOARD_Y 4
#define BOARD_SIZE 19

#define NO_HIGHLIGHT 0
#define WHITE_STONE 1
#define BLACK_STONE 2
#define RED_HIGHLIGHT 3
#define GREEN_HIGHLIGHT 4

int *board;

void legend_printout()
{
    textcolor(WHITE);
    gotoxy(LEGEND_X, LEGEND_Y);
    cputs("Tomasz Krepa 193047");
    gotoxy(LEGEND_X, LEGEND_Y + 2);
    cputs("Functionality:");
    gotoxy(LEGEND_X, LEGEND_Y + 4);
    cputs("Key uses:");
}

void change_color(int color)
{
    switch (color)
    {
    case NO_HIGHLIGHT:
        /* code */
        break;
    
    default:
        break;
    }
}

void board_tile_printout(int x, int y, int highlight = NO_HIGHLIGHT)
{
    gotoxy(BOARD_X + 2 + x * 2, BOARD_Y + 1 + y);
    switch (board[x + y * BOARD_SIZE])
    {
    case 0:
        textcolor(LIGHTGRAY);
        textbackground(DARKGRAY);
        if ((x % 2 && y % 2) || (!(x % 2) && !(y % 2)))
        {
            putch(220);
            putch(223);
        }
        else
        {
            putch(223);
            putch(220);
        }

        break;

    case 1:
        textcolor(WHITE);
        textbackground(BLACK);
        putch(219);
        putch(219);
        break;

    case 2:
        textcolor(BLACK);
        textbackground(WHITE);
        putch(219);
        putch(219);
        break;

    default:
        break;
    }
}

void board_printout()
{
    int x, y, i;

    gotoxy(BOARD_X, BOARD_Y);
    textcolor(BROWN);
    textbackground(BLACK);
    for (i = 0; i < BOARD_SIZE + 2; i++)
    {
        putch(178);
        putch(178);
    }

    for (y = 0; y < BOARD_SIZE; y++)
    {
        gotoxy(BOARD_X, BOARD_Y + y + 1);

        textcolor(BROWN);
        textbackground(BLACK);
        putch(178);
        putch(178);

        for (x = 0; x < BOARD_SIZE; x++)
        {

            textbackground(BLACK);
            switch (board[x + y * BOARD_SIZE])
            {
            case 0:
                textcolor(LIGHTGRAY);
                textbackground(DARKGRAY);
                if ((x % 2 && y % 2) || (!(x % 2) && !(y % 2)))
                {
                    putch(220);
                    putch(223);
                }
                else
                {
                    putch(223);
                    putch(220);
                }

                break;

            case 1:
                textcolor(WHITE);
                textbackground(BLACK);
                putch(219);
                putch(219);
                break;

            case 2:
                textcolor(BLACK);
                textbackground(WHITE);
                putch(219);
                putch(219);
                break;

            default:
                break;
            }
        }
        textcolor(BROWN);
        textbackground(BLACK);
        putch(178);
        putch(178);
    }
    gotoxy(BOARD_X, BOARD_Y + BOARD_SIZE + 1);
    textcolor(BROWN);
    textbackground(BLACK);
    for (i = 0; i < BOARD_SIZE + 2; i++)
    {
        putch(178);
        putch(178);
    }
}

void cursor_move(int *x, int *y, int dx, int dy)
{

    board_tile_printout(*x, *y);

    *x = (*x + dx) >= BOARD_SIZE ? BOARD_SIZE - 1 : ((*x + dx) < 0 ? 0 : (*x + dx));
    *y = (*y + dy) >= BOARD_SIZE ? BOARD_SIZE - 1 : ((*y + dy) < 0 ? 0 : (*y + dy));

    gotoxy(BOARD_X + 2 + *(x)*2, BOARD_Y + 1 + *(y));
    textcolor(LIGHTGREEN);
    textbackground(GREEN);
    if ((*x % 2 && *y % 2) || (!(*x % 2) && !(*y % 2)))
    {
        putch(220);
        putch(223);
    }
    else
    {
        putch(223);
        putch(220);
    }
}

void place_stone(int x, int y, int color)
{
    board[x + BOARD_SIZE * y] = color;
    board_tile_printout(x, y);
}

int main()
{

    settitle("Tomasz Krepa 193047");

    _setcursortype(_NOCURSOR);

    int input = 0;

    board = (int *)malloc(sizeof(int) * BOARD_SIZE * BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
        board[i] = 0;

    int cursor_x = BOARD_SIZE / 2, cursor_y = BOARD_SIZE / 2;

    textbackground(BLACK);                  
    clrscr();                               // Printing out the background
    legend_printout();                      // 
    board_printout();                       // It won't be updated
    cursor_move(&cursor_x, &cursor_y, 0, 0);// 

    while (true)
    {
        /*
            check which button was clicked
            
        
        
        */



        input = getch();
        if (input == 0)
        {
            input = getch();
            if (input == 0x48) // down arrow
            {
                cursor_move(&cursor_x, &cursor_y, 0, -1);
            }
            else if (input == 0x50) // up arrow
            {
                cursor_move(&cursor_x, &cursor_y, 0, 1);
            }
            else if (input == 0x4b) // left arrow
            {
                cursor_move(&cursor_x, &cursor_y, -1, 0);
            }
            else if (input == 0x4d) // right arrow
            {
                cursor_move(&cursor_x, &cursor_y, 1, 0);
            }
        }
        else
        {
            if (input == 'i')
            {
                place_stone(cursor_x, cursor_y, 1);
            }
        }
    }

    _setcursortype(_NORMALCURSOR);
    return 0;
}
