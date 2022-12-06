#include "conio2.h"
#include "go.h"
#include <stdlib.h>

void legend_printout()
{
    textcolor(WHITE);
    textbackground(BLACK);
    gotoxy(LEGEND_X, LEGEND_Y);
    cputs("Tomasz Krepa 193047");
    gotoxy(LEGEND_X, LEGEND_Y + 2);
    cputs("Functionality:");
    gotoxy(LEGEND_X, LEGEND_Y + 3);
    cputs("(a) (b) (c) (d) (e)");
    gotoxy(LEGEND_X, LEGEND_Y + 4);
    cputs("() () () () (j) () ()");
    gotoxy(LEGEND_X, LEGEND_Y + 5);
    cputs("() ()");
    gotoxy(LEGEND_X, LEGEND_Y + 6);
    cputs("Key shortcuts:");
    gotoxy(LEGEND_X, LEGEND_Y + 7);
    cputs(" arrows: moving the cursor");
    gotoxy(LEGEND_X, LEGEND_Y + 8);
    cputs(" q: quit the program");
    gotoxy(LEGEND_X, LEGEND_Y + 9);
    cputs(" n: start a new game");
    gotoxy(LEGEND_X, LEGEND_Y + 10);
    cputs(" enter: confirm player's choice");
    gotoxy(LEGEND_X, LEGEND_Y + 11);
    cputs(" esc: cancel current action");
    gotoxy(LEGEND_X, LEGEND_Y + 12);
    cputs(" i: place stone on the board");
}

void change_color(int stone_type, int cursor_color = CURSOR_NONE)
{
    // if no cursor highlight is given the function will apply usual style colors
    if (cursor_color == CURSOR_NONE)
    {
        switch (stone_type)
        {
        case STONE_NO:
            textcolor(LIGHTGRAY);
            textbackground(DARKGRAY);
            break;
        case STONE_WHITE:
            textcolor(LIGHTGRAY);
            textbackground(WHITE);
            break;
        case STONE_BLACK:
            textcolor(LIGHTGRAY);
            textbackground(BLACK);
            break;

        default:
            break;
        }
    }
    // if a cursor color is given the function will ignore the stone's style color and apply the highlight
    else
    {
        switch (cursor_color)
        {
        case CURSOR_GREEN:
            textcolor(LIGHTGREEN);
            textbackground(GREEN);
            break;
        case CURSOR_RED:
            textcolor(LIGHTRED);
            textbackground(RED);
            break;
        case CURSOR_YELLOW:
            textcolor(YELLOW);
            textbackground(BROWN);
        default:
            break;
        }
    }
}

void board_tile_printout(int *game_state, int x, int y, int cursor_color = CURSOR_NONE)
{
    gotoxy(BOARD_X + 2 + x * 2, BOARD_Y + 1 + y);
    switch (game_state[x + y * BOARD_SIZE])
    {
    case STONE_NO:
        change_color(STONE_NO, cursor_color);
        if (SIMPLIFIED) // a simplified pattern without using extended ASCII
        {
            putch('<');
            putch('>');
        }
        else
        {
            if ((x % 2 && y % 2) || (!(x % 2) && !(y % 2)))
            // creates the checkerboard pattern
            {               // ▄ + ▀ = ▄▀
                putch(220); // ▄
                putch(223); // ▀
            }
            else
            {               // ▀ + ▄ = ▀▄
                putch(223); // ▀
                putch(220); // ▄
            }
        }

        break;

    case STONE_WHITE:
        change_color(STONE_WHITE, cursor_color);
        putch('(');
        putch(')');
        break;

    case STONE_BLACK:
        change_color(STONE_BLACK, cursor_color);
        putch('[');
        putch(']');
        break;

    default:
        break;
    }
}

void border_tile_printout()
{
    textcolor(YELLOW);
    textbackground(DARKGRAY);
    if (SIMPLIFIED) // a simplified pattern without using extended ASCII
    {
        putch('#');
        putch('#');
    }
    else
    {
        putch(178);
        putch(178);
    }
}

void board_printout(int *gamestate)
{
    int x, y, i;

    gotoxy(BOARD_X, BOARD_Y);

    for (i = 0; i < BOARD_SIZE + 2; i++)
    {
        border_tile_printout();
    }

    for (y = 0; y < BOARD_SIZE; y++)
    {
        gotoxy(BOARD_X, BOARD_Y + y + 1);

        border_tile_printout();

        for (x = 0; x < BOARD_SIZE; x++)
        {
            board_tile_printout(gamestate, x, y);
        }

        border_tile_printout();
    }
    gotoxy(BOARD_X, BOARD_Y + BOARD_SIZE + 1);
    for (i = 0; i < BOARD_SIZE + 2; i++)
    {
        border_tile_printout();
    }
}

void cursor_draw(int *gamestate, Cursor *cur)
{
    board_tile_printout(gamestate, cur->x, cur->y, cur->color);
}

void cursor_move(int *gamestate, Cursor *cur, int dx, int dy)
{

    board_tile_printout(gamestate, cur->x, cur->y);

    // limits the cursor position to the board size
    cur->x = (cur->x + dx >= BOARD_SIZE) ? BOARD_SIZE - 1 : ((cur->x + dx) < 0 ? 0 : (cur->x + dx));
    cur->y = (cur->y + dy >= BOARD_SIZE) ? BOARD_SIZE - 1 : ((cur->y + dy) < 0 ? 0 : (cur->y + dy));

    cursor_draw(gamestate, cur);
}

void place_stone(int *gamestate, Cursor *cur, int player)
{
    gamestate[cur->x + BOARD_SIZE * cur->y] = player;
    cursor_draw(gamestate, cur);
}

void remove_stone(int *gamestate, int x, int y)
{
    gamestate[x + y * BOARD_SIZE] = STONE_NO;
    board_tile_printout(gamestate, x, y);
}

void turn_printout(int player)
{
    gotoxy(BOARD_X, BOARD_Y - 1);
    textcolor(WHITE);
    textbackground(BLACK);
    switch (player)
    {
    case STONE_WHITE:
        cputs("It's WHITE's turn");
        break;
    case STONE_BLACK:
        cputs("It's BLACK's turn");
        break;
    default:
        break;
    }
}

void message_printout(int message_id)
{
    gotoxy(BOARD_X, BOARD_Y + BOARD_SIZE + 2);
    switch (message_id)
    {
    case MESSAGE_NONE:
        textcolor(WHITE);
        textbackground(BLACK);
        cputs("                                                    ");
        break;

    case MESSAGE_STONE_PLACED:
        textcolor(WHITE);
        textbackground(BLACK);
        cputs("Press <enter> to confirm or <esc> to cancel");
        break;

    case MESSAGE_INVALID_PLACE:
        textcolor(RED);
        textbackground(BLACK);
        cputs("You can't place a stone here");
        break;

    default:
        break;
    }
}

bool has_liberties(int *gamestate, int x, int y, int player)
{
    if ((x - 1) >= 0)
        if (gamestate[(x - 1) + y * BOARD_SIZE] == STONE_NO || gamestate[(x - 1) + y * BOARD_SIZE] == player)
            return true;
    if ((x + 1) < BOARD_SIZE)
        if (gamestate[(x + 1) + y * BOARD_SIZE] == STONE_NO || gamestate[(x + 1) + y * BOARD_SIZE] == player)
            return true;
    if ((y - 1) >= 0)
        if (gamestate[x + (y - 1) * BOARD_SIZE] == STONE_NO || gamestate[x + (y - 1) * BOARD_SIZE] == player)
            return true;
    if ((y + 1) < BOARD_SIZE)
        if (gamestate[x + (y + 1) * BOARD_SIZE] == STONE_NO || gamestate[x + (y + 1) * BOARD_SIZE] == player)
            return true;

    return false;
}

bool is_valid_position(int *gamestate, Cursor *cur, int player)
{
    if (gamestate[cur->x + cur->y * BOARD_SIZE] != STONE_NO)
        return false;
    else if (!has_liberties(gamestate, cur->x, cur->y, player) && !can_kill_surroundings(gamestate, cur->x, cur->y, player))
        // if the place lacks liberties but will kill opponent's stone
        return false;
    return true;
}

bool can_kill_surroundings(int *gamestate, int x, int y, int player)
{
    // a temporary change invisible to the player
    gamestate[x + y * BOARD_SIZE] = player;

    int second_player = (player == STONE_WHITE) ? STONE_BLACK : STONE_WHITE;
    if ((x - 1) >= 0)
        if (!check_chain(gamestate, x - 1, y, second_player))
        {
            // reversing the temporary placement before returning the result
            gamestate[x + y * BOARD_SIZE] = STONE_NO;
            return true;
        }
    if ((x + 1) < BOARD_SIZE)
        if (!check_chain(gamestate, x + 1, y, second_player))
        {
            // reversing the temporary placement before returning the result
            gamestate[x + y * BOARD_SIZE] = STONE_NO;
            return true;
        }
    if ((y - 1) >= 0)
        if (!check_chain(gamestate, x, y - 1, second_player))
        {
            // reversing the temporary placement before returning the result
            gamestate[x + y * BOARD_SIZE] = STONE_NO;
            return true;
        }
    if ((y + 1) < BOARD_SIZE)
        if (!check_chain(gamestate, x, y + 1, second_player))
        {
            // reversing the temporary placement before returning the result
            gamestate[x + y * BOARD_SIZE] = STONE_NO;
            return true;
        }
    // reversing the temporary placement before returning the result
    gamestate[x + y * BOARD_SIZE] = STONE_NO;
    return false;
}

void capture_surrounding_chains(int *gamestate, int x, int y, int player)
{
    if ((x - 1) >= 0)
        if (gamestate[(x - 1) + y * BOARD_SIZE] == player)
            capture_chain(gamestate, x - 1, y, player);

    if ((x + 1) < BOARD_SIZE)
        if (gamestate[(x + 1) + y * BOARD_SIZE] == player)
            capture_chain(gamestate, x + 1, y, player);

    if ((y - 1) >= 0)
        if (gamestate[x + (y - 1) * BOARD_SIZE] == player)
            capture_chain(gamestate, x, y - 1, player);

    if ((y + 1) < BOARD_SIZE)
        if (gamestate[x + (y + 1) * BOARD_SIZE] == player)
            capture_chain(gamestate, x, y + 1, player);
}

int chain_check_suffocation(int *gamestate, bool *counted_stones, int x, int y, int player)
{
    bool suffocating = 1;

    // checking for liberties around the tile
    if ((x - 1) >= 0)
        if (gamestate[(x - 1) + y * BOARD_SIZE] == STONE_NO)
            return 0;
    if ((x + 1) < BOARD_SIZE)
        if (gamestate[(x + 1) + y * BOARD_SIZE] == STONE_NO)
            return 0;
    if ((y - 1) >= 0)
        if (gamestate[x + (y - 1) * BOARD_SIZE] == STONE_NO)
            return 0;
    if ((y + 1) < BOARD_SIZE)
        if (gamestate[x + (y + 1) * BOARD_SIZE] == STONE_NO)
            return 0;

    // if the stone has a liberty that liberty extends onto the entire chain
    // so the function doesn't futher check other stones for liberties

    counted_stones[x + y * BOARD_SIZE] = true;

    // checking if other stones of the same color have liberties
    if ((x - 1) >= 0)
        if (gamestate[(x - 1) + y * BOARD_SIZE] == player)
            if (!counted_stones[(x - 1) + y * BOARD_SIZE])
                suffocating *= chain_check_suffocation(gamestate, counted_stones, x - 1, y, player);
    if ((x + 1) < BOARD_SIZE)
        if (gamestate[(x + 1) + y * BOARD_SIZE] == player)
            if (!counted_stones[(x + 1) + y * BOARD_SIZE])
                suffocating *= chain_check_suffocation(gamestate, counted_stones, x + 1, y, player);
    if ((y - 1) >= 0)
        if (gamestate[x + (y - 1) * BOARD_SIZE] == player)
            if (!counted_stones[x + (y - 1) * BOARD_SIZE])
                suffocating *= chain_check_suffocation(gamestate, counted_stones, x, y - 1, player);
    if ((y + 1) < BOARD_SIZE)
        if (gamestate[x + (y + 1) * BOARD_SIZE] == player)
            if (!counted_stones[x + (y + 1) * BOARD_SIZE])
                suffocating *= chain_check_suffocation(gamestate, counted_stones, x, y + 1, player);

    return suffocating;
}

bool check_chain(int *gamestate, int x, int y, int player)
{
    bool *counted_stones = (bool *)malloc(sizeof(bool) * BOARD_SIZE * BOARD_SIZE);
    int i;
    for (i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
        counted_stones[i] = false;
    bool result = chain_check_suffocation(gamestate, counted_stones, x, y, player);
    free(counted_stones);
    return !result;
}

void capture_chain(int *gamestate, int x, int y, int player)
{
    bool *counted_stones = (bool *)malloc(sizeof(bool) * BOARD_SIZE * BOARD_SIZE);
    int i;
    for (i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
        counted_stones[i] = false;
    if (chain_check_suffocation(gamestate, counted_stones, x, y, player))
    {
        for (i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
        {
            if (counted_stones[i])
            {
                remove_stone(gamestate, i % BOARD_SIZE, i / BOARD_SIZE);
            }
        }
    }
    free(counted_stones);
}
