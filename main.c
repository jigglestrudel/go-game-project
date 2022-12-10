// Tomasz Krępa 193047
// TODO scoring
// TODO scrolling

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "go.h"
#include "conio2.h"

int main()
{
    settitle("Tomasz Krepa 193047");

    _setcursortype(_NOCURSOR);

    int input = 0;
    int i;
    int *board = NULL;
    char buf[LONG_INPUT_BUFFER_SIZE];

    create_board(&board, BOARD_SIZE);

    cursor_t *cursor = (cursor_t *)malloc(sizeof(cursor_t));
    if (cursor == NULL)
    {
        return 1;
    }

    game_var_t *game_var = (game_var_t *)malloc(sizeof(game_var_t));
    if (game_var == NULL)
    {
        return 1;
    }

    game_var->b_size = BOARD_SIZE;
    new_game(&board, game_var, cursor);

    redraw_screen(board, game_var->b_size);
    turn_printout(game_var->current_player);
    cursor_draw(board, game_var->b_size, cursor);

    bool valid_position = true;
    bool valid_name = true;
    bool game_saved = false;
    bool game_running = true;
    bool game_loaded = false;
    
    bool handicap_placing = false;

    // #1

    while (game_running)
    {
        //#2
        
        // GAME UPDATE
        capture_surrounding_chains(board, game_var->b_size, game_var->last_placed_x, game_var->last_placed_y, game_var);

        //  CURSOR UPDATE
        valid_position = is_valid_position(board, game_var->b_size, cursor->x, cursor->y, game_var->current_player, game_var->last_captured_x, game_var->last_captured_y);
        if (!valid_position)
        {
            cursor->color = CURSOR_RED;
        }
        else
        {
            cursor->color = CURSOR_GREEN;
        }
        cursor_draw(board, game_var->b_size, cursor);

        //  MESSAGE UPDATES
        turn_printout(game_var->current_player);
        down_legend_printout(cursor->x, cursor->y, game_var->black_score, game_var->white_score);

        message_printout(MESSAGE_NONE);
        if (!valid_name)
        {
            message_printout(MESSAGE_NAME_INVALID);
            valid_name = true;
        }
        else if (game_saved)
        {
            message_printout(MESSAGE_GAME_SAVED);
            game_saved = false;
        }
        else if (game_loaded)
        {
            message_printout(MESSAGE_GAME_LOADED);
            game_loaded = false;
        }
        else if (!valid_position)
        {
            message_printout(MESSAGE_INVALID_PLACE);
        }

        // GETTING THE INPUT
        input = getch();
        // checking for special characters (arrows)
        if (input == 0)
        {
            control_the_cursor(board, game_var->b_size, cursor);
        }
        else
        {
            switch (input)
            {
            case 'i':
                if (valid_position)
                {
                    cursor->color = CURSOR_YELLOW;
                    place_stone(board, game_var->b_size, cursor, game_var->current_player);
                    do
                    {
                        message_printout(MESSAGE_PENDING);
                        input = getch();
                    } 
                    while (input != KEY_ENTER && input != KEY_ESCAPE);
                    
                    if (input == KEY_ENTER)
                    {
                        game_var->last_placed_x = cursor->x;
                        game_var->last_placed_y = cursor->y;
                        game_var->last_captured_x = -1;
                        game_var->last_captured_y = -1;

                        if (game_var->current_player == STONE_BLACK)
                            game_var->current_player = STONE_WHITE;
                        else
                            game_var->current_player = STONE_BLACK;
                    }
                    else
                        remove_stone(board, game_var->b_size, cursor->x, cursor->y);
                }

                break;

            case 'n':
                message_printout(MESSAGE_NEW_GAME);
                input = getch();
                switch (input)
                {
                case '1':
                    game_var->b_size = 9;
                    break;
                case '2':
                    game_var->b_size = 13;
                    break;
                case '3':
                    game_var->b_size = 19;
                    break;
                case '4':
                    get_long_input(buf);
                    // TODO limit the change to the visible screen
                    game_var->b_size = atoi(buf);
                    break;

                default:
                    break;
                }

                new_game(&board, game_var, cursor);

                break;

            case 's':
                message_printout(MESSAGE_NONE);
                message_printout(MESSAGE_FILENAME_INPUT);
                if (get_long_input(buf) == LONG_INPUT_ENTER)
                {
                    if (is_valid_savename(buf))
                    {
                        if (file_exists(buf))
                        {
                            message_printout(MESSAGE_SAVEFILE_OVERWRITE);
                            do
                            {
                                input = getch();
                            } while (input != KEY_ENTER && input != KEY_ESCAPE);

                            if (input == KEY_ENTER)
                                save_game(buf, board, game_var);
                        }
                        else if (!save_game(buf, board, game_var))
                            return 1;
                    }
                    else
                        valid_name = false;
                }
                redraw_screen(board, game_var->b_size);
                break;

            case 'l':
                message_printout(MESSAGE_NONE);
                message_printout(MESSAGE_FILENAME_INPUT);
                if (get_long_input(buf) == LONG_INPUT_ENTER)
                {
                    if (is_valid_savename(buf) && file_exists(buf))
                    {
                        if (!load_game(buf, &board, game_var))
                            return 1;
                        else
                            game_loaded = true;
                    }
                }
                cursor_reset(cursor, game_var);
                redraw_screen(board, game_var->b_size);
                break;

            case 'q':
                game_running = false;
                break;

            case 'h':
                new_game(&board, game_var, cursor);
                message_printout(MESSAGE_HANDICAP_IN_PROGRESS);
                turn_printout(STONE_NO);
                cursor->color = CURSOR_YELLOW;
                do
                {
                    input = getch();
                    if (input == 0)
                    {
                        control_the_cursor(board, game_var->b_size, cursor);
                    }
                    else
                    {
                        if (input == 'i')
                            place_stone(board, game_var->b_size, cursor, STONE_BLACK);
                    }

                } while (input != KEY_ENTER && input != KEY_ESCAPE);

                if (input == KEY_ENTER) 
                {
                    game_var->handicap_mode = true;
                    game_var->current_player = STONE_WHITE;
                }
                else new_game(&board, game_var, cursor);
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
    gotoxy(1, 1);
    return 0;
}