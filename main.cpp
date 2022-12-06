#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "go.h"
#include "conio2.h"



int main()
{
    settitle("Tomasz Krepa 193047");

    _setcursortype(_NOCURSOR);

    int i;
    int* board;

    board = (int *)malloc(sizeof(int) * BOARD_SIZE * BOARD_SIZE);
    if (board == nullptr)
    {
        return 1;
    }

    Cursor* cursor = (Cursor*)malloc(sizeof(Cursor));
    if (cursor == nullptr)
    {
        return 1;
    }

    int input = 0;
    int current_player = STONE_BLACK;
    int last_placed_x = 0;
    int last_placed_y = 0;
    bool board_pending = false;
    bool game_running = true;
    bool valid_position;

    for (i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
        board[i] = STONE_NO;
    
    cursor->x = BOARD_SIZE / 2;
    cursor->y = BOARD_SIZE / 2;
    cursor->color = CURSOR_GREEN;

    textbackground(BLACK);
    clrscr();
    legend_printout();
    board_printout(board);
    turn_printout(current_player);
    cursor_move(board, cursor, 0, 0);

    while (game_running)
    {
        // GAME UPDATE
        if(!board_pending)
        {
            capture_surrounding_chains(board, last_placed_x, last_placed_y, current_player);
        }
            
        //  CURSOR UPDATE
        valid_position = is_valid_position(board, cursor, current_player);
        if (board_pending)
        {
            cursor->color = CURSOR_NONE;
        }
        else if (!valid_position)
        {
            cursor->color = CURSOR_RED;
        }
        else
        {
            cursor->color = CURSOR_GREEN;
        }
        cursor_draw(board, cursor);
        
        //  MESSAGE UPDATES
        turn_printout(current_player);
        message_printout(MESSAGE_NONE);
        if(board_pending)
        {
            message_printout(MESSAGE_STONE_PLACED);
        }
        else if (!is_valid_position(board, cursor, current_player))
        {
            message_printout(MESSAGE_INVALID_PLACE);
        }

        // GETTING THE INPUT
        input = getch();
        // checking for special characters (arrows)
        if (input == 0)
        {
            input = getch();
            if (input == 0x48) // down arrow
            {
                cursor_move(board, cursor, 0, -1);
            }
            else if (input == 0x50) // up arrow
            {
                cursor_move(board, cursor, 0, 1);
            }
            else if (input == 0x4b) // left arrow
            {
                cursor_move(board, cursor, -1, 0);
            }
            else if (input == 0x4d) // right arrow
            {
                cursor_move(board, cursor, 1, 0);
            }
        }
        else
        {
            switch (input)
            {
                case 'i':
                if (!board_pending)
                    {
                        if (valid_position)
                        {
                            place_stone(board, cursor, current_player);
                            last_placed_x = cursor->x;
                            last_placed_y = cursor->y;
                            board_pending = true;
                        }      
                    }
                break;
                
                case 'n':
                    input = 0;
                    current_player = STONE_BLACK;
                    last_placed_x = 0;
                    last_placed_y = 0;
                    board_pending = false;
                    game_running = true;
                    valid_position;
                    
                    for (i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
                        board[i] = STONE_NO;
                    
                    cursor->x = BOARD_SIZE / 2;
                    cursor->y = BOARD_SIZE / 2;
                    cursor->color = CURSOR_GREEN;

                break;


                case 'q':
                    game_running = false;
                break;

                case 0x0d: // enter
                    if (board_pending)
                    {
                        board_pending = false;
                        if (current_player == STONE_BLACK) 
                            current_player = STONE_WHITE;
                        else 
                            current_player = STONE_BLACK;
                    }   
                break;

                case 0x1b: // esc
                    if (board_pending)
                    {
                        board_pending = false;
                        remove_stone(board, last_placed_x, last_placed_y);
                    }
                break;
            }
        }
    }

    free(board);
    free(cursor);

    _setcursortype(_NORMALCURSOR);
    textbackground(BLACK);        
    textcolor(LIGHTGRAY);
    clrscr();                   
    gotoxy(1,1);
    return 0;
}
