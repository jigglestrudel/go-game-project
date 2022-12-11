#include "conio2.h"
#include "go.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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
    cputs("(f) (g) (h) (i) (j) (k) ()");
    gotoxy(LEGEND_X, LEGEND_Y + 5);
    cputs("() ()");
    gotoxy(LEGEND_X, LEGEND_Y + 6);
    cputs("Keys:");
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
    gotoxy(LEGEND_X, LEGEND_Y + 13);
    cputs(" s: save the game state");
    gotoxy(LEGEND_X, LEGEND_Y + 14);
    cputs(" l: load the game state");
    gotoxy(LEGEND_X, LEGEND_Y + 15);
    cputs(" f: finish the game");
    gotoxy(LEGEND_X, LEGEND_Y + 16);
    cputs(" h: introduce a handicap");
}

void down_legend_printout(int x, int y, float b, float w)
{
    char txt[32];
    gotoxy(LEGEND_X, LEGEND_Y + LEGEND_HEIGHT + 1);
    sprintf(txt, "position: x =%3d, y =%3d", x, y);
    cputs(txt);
    gotoxy(LEGEND_X, LEGEND_Y + LEGEND_HEIGHT + 2);
    sprintf(txt, "black:white <=> %3.1f:%3.1f", b, w);
    cputs(txt);
}

void change_color(int stone_type, int cursor_color)
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
            textcolor((PRETTY_BOARD_PATTERN) ? LIGHTGRAY : WHITE);
            textbackground((PRETTY_BOARD_PATTERN) ? WHITE : DARKGRAY);
            break;
        case STONE_BLACK:
            textcolor((PRETTY_BOARD_PATTERN) ? LIGHTGRAY : BLACK);
            textbackground((PRETTY_BOARD_PATTERN) ? BLACK : DARKGRAY);
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

void board_tile_printout(screen_size_t *scr, int *game_state, int b_size, int x, int y, int cursor_color)
{
    if (BOARD_X + x * 2 + scr->board_x_offset  < scr->s_w &&
        BOARD_Y + y + scr->board_y_offset < scr->s_h &&
        BOARD_X + x * 2 + scr->board_x_offset  >= BOARD_X &&
        BOARD_Y + y + scr->board_y_offset >= BOARD_Y)
    {
        gotoxy(BOARD_X + x * 2 + scr->board_x_offset, BOARD_Y + y + scr->board_y_offset);
        switch (game_state[x + y * b_size])
        {
        case STONE_NO:
            change_color(STONE_NO, cursor_color);
            if (!PRETTY_BOARD_PATTERN)
            {
                if (x == 0 && y == 0)
                {
                    putch(CHARACTER_CORNER_TOP_LEFT);
                    change_color(STONE_NO, CURSOR_NONE);
                    putch(CHARACTER_LINE);
                }
                else if (x == 0 && y == b_size - 1)
                {
                    putch(CHARACTER_CORNER_BOTTOM_LEFT);
                    change_color(STONE_NO, CURSOR_NONE);
                    putch(CHARACTER_LINE);
                }
                else if (x == b_size - 1 && y == b_size - 1)
                {
                    putch(CHARACTER_CORNER_BOTTOM_RIGHT);
                    change_color(STONE_NO, CURSOR_NONE);
                    putch(' ');
                }
                else if (x == b_size - 1 && y == 0)
                {
                    putch(CHARACTER_CORNER_TOP_RIGHT);
                    change_color(STONE_NO, CURSOR_NONE);
                    putch(' ');
                }
                else if (x == 0)
                {
                    putch(CHARACTER_EDGE_LEFT);
                    change_color(STONE_NO, CURSOR_NONE);
                    putch(CHARACTER_LINE);
                }
                else if (y == 0)
                {
                    putch(CHARACTER_EDGE_TOP);
                    change_color(STONE_NO, CURSOR_NONE);
                    putch(CHARACTER_LINE);
                }
                else if (y == b_size - 1)
                {
                    putch(CHARACTER_EDGE_BOTTOM);
                    change_color(STONE_NO, CURSOR_NONE);
                    putch(CHARACTER_LINE);
                }
                else if (x == b_size - 1)
                {
                    putch(CHARACTER_EDGE_RIGHT);
                    change_color(STONE_NO, CURSOR_NONE);
                    putch(' ');
                }
                else
                {
                    putch(CHARACTER_CROSS_INSIDE);
                    change_color(STONE_NO, CURSOR_NONE);
                    putch(CHARACTER_LINE);
                }
            }
            else
            {
                if ((x % 2 && y % 2) || (!(x % 2) && !(y % 2)))
                // creates the checkerboard pattern
                {
                    putch(CHARACTER_CHECKERBOARD_DOWN);
                    putch(CHARACTER_CHECKERBOARD_UP);
                }
                else
                {
                    putch(CHARACTER_CHECKERBOARD_UP);
                    putch(CHARACTER_CHECKERBOARD_DOWN);
                }
            }

            break;

        case STONE_WHITE:
            change_color(STONE_WHITE, cursor_color);
            if (!PRETTY_BOARD_PATTERN)
            {
                putch(CHARACTER_STONE);
                change_color(STONE_NO, CURSOR_NONE);
                if (x < b_size - 1)
                    putch(CHARACTER_LINE);
                else
                    putch(' ');
            }
            else
            {
                putch('(');
                putch(')');
            }

            break;

        case STONE_BLACK:
            change_color(STONE_BLACK, cursor_color);
            if (!PRETTY_BOARD_PATTERN)
            {
                putch(CHARACTER_STONE);
                change_color(STONE_NO, CURSOR_NONE);
                if (x < b_size - 1)
                    putch(CHARACTER_LINE);
                else
                    putch(' ');
            }
            else
            {
                putch('[');
                putch(']');
            }
            break;

        default:
            break;
        }
    }
}

void border_tile_printout()
{
    textcolor(YELLOW);
    textbackground(DARKGRAY);
    putch(178);
    putch(178);
}

void board_printout(screen_size_t *scr, int *gamestate, int b_size)
{
    int x, y, i;

    if (scr->board_y_offset > 0)
    {
    gotoxy(BOARD_X, BOARD_Y);

        for (i = 0; i < b_size+2 && BOARD_X + i*2 < scr->s_w; i++)
        {
            border_tile_printout();
        }
    }

    for (y = 0; y < b_size; y++)
    {
        if (scr->board_x_offset > 0 &&
            BOARD_Y + y  + scr->board_y_offset < scr->s_h &&
            BOARD_Y + y  + scr->board_y_offset >= BOARD_Y)
        {
            gotoxy(BOARD_X, BOARD_Y + y + scr->board_y_offset);
            border_tile_printout();
        }

        for (x = 0; x < b_size; x++)
        {
            board_tile_printout(scr, gamestate, b_size, x, y, CURSOR_NONE);
        }

        if (BOARD_X + x * 2 + scr->board_x_offset < scr->s_w &&
            BOARD_Y + y  + scr->board_y_offset < scr->s_h &&
            BOARD_Y + y  + scr->board_y_offset >= BOARD_Y)

            border_tile_printout();
    }

    if (BOARD_Y + b_size + scr->board_y_offset < scr->s_h)
    {
        gotoxy(BOARD_X, BOARD_Y + b_size + scr->board_y_offset);

        for (i = 0; i < b_size+2 && BOARD_X + i*2 < scr->s_w; i++)
        {
            border_tile_printout();
        }
    }
}

void reset_game_var(game_var_t *game_var)
{
    game_var->current_player = STONE_BLACK;
    game_var->last_placed_x = 0;
    game_var->last_placed_y = 0;
    game_var->last_captured_x = -1;
    game_var->last_captured_y = -1;
    game_var->black_score = 0;
    game_var->white_score = 0;
    game_var->handicap_mode = false;
}

void redraw_screen(screen_size_t *scr, int *gamestate, int b_size)
{
    textbackground(BLACK);
    textcolor(WHITE);
    clrscr();
    legend_printout();
    board_printout(scr, gamestate, b_size);
}

void cursor_draw(screen_size_t *scr, int *gamestate, int b_size, cursor_t *cur)
{
    board_tile_printout(scr, gamestate, b_size, cur->x, cur->y, cur->color);
}

void cursor_move(screen_size_t *scr, int *gamestate, int b_size, cursor_t *cur, int dx, int dy)
{

    board_tile_printout(scr, gamestate, b_size, cur->x, cur->y, CURSOR_NONE);

    // limits the cursor position to the board size
    cur->x = (cur->x + dx >= b_size) ? b_size - 1 : ((cur->x + dx) < 0 ? 0 : (cur->x + dx));
    cur->y = (cur->y + dy >= b_size) ? b_size - 1 : ((cur->y + dy) < 0 ? 0 : (cur->y + dy));

    if (BOARD_X + 2 + cur->x*2 + scr->board_x_offset +2  >  scr->s_w) scr->board_x_offset -= 2;
    if (BOARD_X  + cur->x*2 + scr->board_x_offset  <  BOARD_X+1) scr->board_x_offset += 2;
    if (BOARD_Y + 1 + cur->y + scr->board_y_offset +1  >  scr->s_h) scr->board_y_offset -= 1;
    if (BOARD_Y  + cur->y + scr->board_y_offset  <  BOARD_Y+1) scr->board_y_offset += 1;

    cursor_draw(scr, gamestate, b_size, cur);
}

void cursor_reset(cursor_t *cur, game_var_t *game_var)
{
    cur->x = game_var->b_size / 2;
    cur->y = game_var->b_size / 2;
    cur->color = CURSOR_GREEN;
}

void place_stone(screen_size_t *scr, int *gamestate, int b_size, cursor_t *cur, int player)
{
    gamestate[cur->x + b_size * cur->y] = player;
    cursor_draw(scr, gamestate, b_size, cur);
}

void remove_stone(screen_size_t *scr, int *gamestate, int b_size, int x, int y)
{
    gamestate[x + y * b_size] = STONE_NO;
    board_tile_printout(scr, gamestate, b_size, x, y, CURSOR_NONE);
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
    case STONE_NO:
        cputs("HANDICAP mode");
        break;
    default:
        break;
    }
}

void message_printout(int message_id)
{
    gotoxy(LEGEND_X, LEGEND_Y + LEGEND_FULL_HEIGHT);
    switch (message_id)
    {
    case MESSAGE_NONE:
        textcolor(WHITE);
        textbackground(BLACK);
        cputs("                               ");
        gotoxy(LEGEND_X, LEGEND_Y + LEGEND_FULL_HEIGHT + 1);
        cputs("                               ");
        break;

    case MESSAGE_PENDING:
        textcolor(WHITE);
        textbackground(BLACK);

        cputs("Press <enter> to confirm");
        gotoxy(LEGEND_X, LEGEND_Y + LEGEND_FULL_HEIGHT + 1);

        cputs("or <esc> to cancel");
        break;

    case MESSAGE_NEW_GAME:
        textcolor(WHITE);
        textbackground(BLACK);

        cputs("board: [1]: 9x9   [2]: 13x13");
        gotoxy(LEGEND_X, LEGEND_Y + LEGEND_FULL_HEIGHT + 1);

        cputs("       [3]: 19x19 [4]: custom");
        break;

    case MESSAGE_INVALID_PLACE:
        textcolor(RED);
        textbackground(BLACK);

        cputs("You can't place a stone here");
        break;

    case MESSAGE_NAME_INVALID:
        textcolor(RED);
        textbackground(BLACK);

        cputs("That's not a valid filename");
        break;

    case MESSAGE_FILENAME_INPUT:
        textcolor(GREEN);
        textbackground(BLACK);

        char txt[30];
        cputs("Enter a valid filename ");
        gotoxy(LEGEND_X, LEGEND_Y + LEGEND_FULL_HEIGHT + 1);

        sprintf(txt, "max %d letters", LONG_INPUT_BUFFER_SIZE - 1);
        cputs(txt);
        break;

    case MESSAGE_SAVEFILE_OVERWRITE:
        textcolor(YELLOW);
        textbackground(BLACK);

        cputs("Savefile will be overwritten ");
        gotoxy(LEGEND_X, LEGEND_Y + LEGEND_FULL_HEIGHT + 1);
        cputs("<enter> to save <esc> to cancel");
        break;

    case MESSAGE_GAME_SAVED:
        textcolor(GREEN);
        textbackground(BLACK);

        cputs("Game saved!");
        break;

    case MESSAGE_GAME_LOADED:
        textcolor(GREEN);
        textbackground(BLACK);

        cputs("Game loaded!");
        break;

    case MESSAGE_HANDICAP_IN_PROGRESS:
        textcolor(YELLOW);
        textbackground(BLACK);

        cputs("Handicap placement mode");
        gotoxy(LEGEND_X, LEGEND_Y + LEGEND_FULL_HEIGHT + 1);
        cputs("<enter> to save <esc> to cancel");
        break;

    default:
        break;
    }
}

bool has_liberties(int *gamestate, int b_size, int x, int y)
{
    if (((x - 1) >= 0 && gamestate[(x - 1) + y * b_size] == STONE_NO) ||
        ((x + 1) < b_size && gamestate[(x + 1) + y * b_size] == STONE_NO) ||
        ((y - 1) >= 0 && gamestate[x + (y - 1) * b_size] == STONE_NO) ||
        ((y + 1) < b_size && gamestate[x + (y + 1) * b_size] == STONE_NO))
        return true;

    return false;
}

bool is_valid_position(int *gamestate, int b_size, int x, int y, int player, int stone_x, int stone_y)
{
    if (gamestate[x + y * b_size] != STONE_NO || // cant place on top of another stone
        (x == stone_x && y == stone_y))          // enforcing the ko rule

        return false;
    else
    {
        // if a place is free and it has liberties you should be able to place a stone there
        if (has_liberties(gamestate, b_size, x, y))
            return true;
        else
        {
            // if a place doesn't offer any liberties but will kill a surrounding opponent's stone
            // or it won't kill itself and/or suffocate any of its own colorred chains it's a valid place
            if (can_kill_surroundings(gamestate, b_size, x, y, player) ||
                !will_kill_itself(gamestate, b_size, x, y, player))
                return true;
            else
                return false;
        }
    }

    return true;
}

bool can_kill_surroundings(int *gamestate, int b_size, int x, int y, int player)
{
    // a temporary change invisible to the player
    gamestate[x + y * b_size] = player;

    int second_player = (player == STONE_WHITE) ? STONE_BLACK : STONE_WHITE;
    if (((x - 1) >= 0 && !check_chain_for_liberties(gamestate, b_size, x - 1, y, second_player)) ||
        ((x + 1) < b_size && !check_chain_for_liberties(gamestate, b_size, x + 1, y, second_player)) ||
        ((y - 1) >= 0 && !check_chain_for_liberties(gamestate, b_size, x, y - 1, second_player)) ||
        ((y + 1) < b_size && !check_chain_for_liberties(gamestate, b_size, x, y + 1, second_player)))
    {
        gamestate[x + y * b_size] = STONE_NO;
        return true;
    }

    gamestate[x + y * b_size] = STONE_NO;
    return false;
}

bool will_kill_itself(int *gamestate, int b_size, int x, int y, int player)
{
    // a temporary change invisible to the player
    gamestate[x + y * b_size] = player;

    if (!check_chain_for_liberties(gamestate, b_size, x, y, player))
    {
        gamestate[x + y * b_size] = STONE_NO;
        return true;
    }

    gamestate[x + y * b_size] = STONE_NO;
    return false;
}

void capture_surrounding_chains(screen_size_t *scr, int *gamestate, int b_size, int x, int y, game_var_t *game_var)
{
    int score = 0;
    if ((x - 1) >= 0 && gamestate[(x - 1) + y * b_size] == game_var->current_player)
        score += capture_chain(scr, gamestate, b_size, x - 1, y, game_var->current_player, &(game_var->last_captured_x), &(game_var->last_captured_y));
    if ((x + 1) < b_size && gamestate[(x + 1) + y * b_size] == game_var->current_player)
        score += capture_chain(scr, gamestate, b_size, x + 1, y, game_var->current_player, &(game_var->last_captured_x), &(game_var->last_captured_y));
    if ((y - 1) >= 0 && gamestate[x + (y - 1) * b_size] == game_var->current_player)
        score += capture_chain(scr, gamestate, b_size, x, y - 1, game_var->current_player, &(game_var->last_captured_x), &(game_var->last_captured_y));
    if ((y + 1) < b_size && gamestate[x + (y + 1) * b_size] == game_var->current_player)
        score += capture_chain(scr, gamestate, b_size, x, y + 1, game_var->current_player, &(game_var->last_captured_x), &(game_var->last_captured_y));

    if (game_var->current_player == STONE_BLACK) // current black turn means white is capturing
        game_var->white_score += score;
    else
        game_var->black_score += score;
}

bool chain_check_suffocation(int *gamestate, int b_size, bool *counted_stones, int x, int y, int player)
{
    bool suffocating = true;

    // checking for liberties around the tile
    if (has_liberties(gamestate, b_size, x, y))
        return false;

    // if the stone has a liberty that liberty extends onto the entire chain
    // so the function doesn't futher check other stones for liberties

    counted_stones[x + y * b_size] = true;

    // checking if other stones of the same color have liberties
    if ((x - 1) >= 0)
        if (gamestate[(x - 1) + y * b_size] == player)
            if (!counted_stones[(x - 1) + y * b_size])
                suffocating *= chain_check_suffocation(gamestate, b_size, counted_stones, x - 1, y, player);
    if (!suffocating)
        return 0;
    if ((x + 1) < b_size)
        if (gamestate[(x + 1) + y * b_size] == player)
            if (!counted_stones[(x + 1) + y * b_size])
                suffocating *= chain_check_suffocation(gamestate, b_size, counted_stones, x + 1, y, player);
    if (!suffocating)
        return 0;
    if ((y - 1) >= 0)
        if (gamestate[x + (y - 1) * b_size] == player)
            if (!counted_stones[x + (y - 1) * b_size])
                suffocating *= chain_check_suffocation(gamestate, b_size, counted_stones, x, y - 1, player);
    if (!suffocating)
        return 0;
    if ((y + 1) < b_size)
        if (gamestate[x + (y + 1) * b_size] == player)
            if (!counted_stones[x + (y + 1) * b_size])
                suffocating *= chain_check_suffocation(gamestate, b_size, counted_stones, x, y + 1, player);

    return suffocating;
}

bool check_chain_for_liberties(int *gamestate, int b_size, int x, int y, int player)
{
    bool *counted_stones = (bool *)malloc(sizeof(bool) * b_size * b_size);
    int i;
    for (i = 0; i < b_size * b_size; i++)
        counted_stones[i] = false;
    bool result = chain_check_suffocation(gamestate, b_size, counted_stones, x, y, player);
    free(counted_stones);
    // the chain_check_suffocation function returns truth when the chain doesn't have liberties
    return !result;
}

int capture_chain(screen_size_t *scr, int *gamestate, int b_size, int x, int y, int player, int *last_captured_x_p, int *last_captured_y_p)
{
    bool *counted_stones = (bool *)malloc(sizeof(bool) * b_size * b_size);
    int i, j;
    // bool only_stone = true;
    int captured_stones = 0;
    for (i = 0; i < b_size * b_size; i++)
        counted_stones[i] = false;
    if (chain_check_suffocation(gamestate, b_size, counted_stones, x, y, player))
    {
        for (i = 0; i < b_size; i++)
            for (j = 0; j < b_size; j++)
                if (counted_stones[i + j * b_size])
                {
                    remove_stone(scr, gamestate, b_size, i, j);
                    captured_stones++;
                    *last_captured_x_p = i;
                    *last_captured_y_p = j;
                }
    }
    free(counted_stones);
    if (captured_stones != 1)
    {
        *last_captured_x_p = -1;
        *last_captured_y_p = -1;
    }
    return captured_stones;
}

int get_long_input(char *buffer)
{
    textcolor(BLACK);
    textbackground(WHITE);
    gotoxy(LEGEND_X, LEGEND_Y + LEGEND_FULL_HEIGHT + 2);
    cputs(">");
    char input;
    int i;
    for (i = 0; i < LONG_INPUT_BUFFER_SIZE; i++)
        buffer[i] = ' ';
    int index = 0;

    do
    {
        input = getch();
        if (index < LONG_INPUT_BUFFER_SIZE - 1 && input != 0x0 &&
            input != 0x0d && input != 0x1b)
        {
            putch(input);
            buffer[index] = input;
            index++;
        }

    } while ((input != 0x0d && input != 0x1b));
    buffer[index] = '\0';
    if (input == 0x0d)
        return LONG_INPUT_ENTER;
    else
        return LONG_INPUT_ESCAPE;
}

bool is_valid_savename(const char *name)
{
    char *unallowed_keys = "*?/<>:|\"\\";
    if (strcspn(name, unallowed_keys) < strlen(name))
        return false;
    else
        return true;
}

void remove_last_spaces_from_savename(char *name)
{
    int i = strlen(name); // we start checking from the end of the string
    while (i > 0)
    {
        i--;
        if (name[i] == ' ')
        {
            name[i] = '\0';
        }
        else // if it finds anything other than a space the loop will break
            break;
    }
}

bool file_exists(char *name)
{
    char filename[64] = {0};
    strcat(filename, name);
    strcat(filename, ".bin");

    FILE *f = fopen(filename, "rb");
    if (f == NULL)
        return false;

    fclose(f);
    return true;
}

bool save_game(char *name, int *gamestate, game_var_t *game_var)
{
    char filename[64] = {0};
    strcat(filename, name);
    strcat(filename, ".bin");

    FILE *f = fopen(filename, "wb");

    if (f == NULL)
        return false;

    fwrite(game_var, sizeof(game_var_t), 1, f);
    fwrite(gamestate, sizeof(int), game_var->b_size * game_var->b_size, f);

    fclose(f);
    return true;
}

bool load_game(char *name, int **gamestate_p, game_var_t *game_var)
{
    char filename[64] = {0};
    strcat(filename, name);
    strcat(filename, ".bin");
    FILE *f = fopen(filename, "rb");

    if (f == NULL)
        return false;

    fread(game_var, sizeof(game_var_t), 1, f);

    create_board(gamestate_p, game_var->b_size);

    fread(*gamestate_p, sizeof(int), game_var->b_size * game_var->b_size, f);

    fclose(f);
    return true;
}

bool create_board(int **gamestate_p, int b_size)
{
    free(*gamestate_p);
    *gamestate_p = (int *)malloc(sizeof(int) * b_size * b_size);
    if (*gamestate_p == NULL)
        return false;

    int i;
    for (i = 0; i < b_size * b_size; i++)
        (*gamestate_p)[i] = STONE_NO;

    return true;
}

void control_the_cursor(screen_size_t *scr, int *gamestate, int b_size, cursor_t *cursor)
{
    char input = getch();
    if (input == SPEC_KEY_DOWN_ARROW) // down arrow
    {
        cursor_move(scr, gamestate, b_size, cursor, 0, -1);
    }
    else if (input == SPEC_KEY_UP_ARROW) // up arrow
    {
        cursor_move(scr, gamestate, b_size, cursor, 0, 1);
    }
    else if (input == SPEC_KEY_LEFT_ARROW) // left arrow
    {
        cursor_move(scr, gamestate, b_size, cursor, -1, 0);
    }
    else if (input == SPEC_KEY_RIGHT_ARROW) // right arrow
    {
        cursor_move(scr, gamestate, b_size, cursor, 1, 0);
    }
}

void new_game(screen_size_t *scr, int **gamestate_p, game_var_t *game_var, cursor_t *cursor)
{
    reset_offsets(scr);
    reset_game_var(game_var);
    create_board(gamestate_p, game_var->b_size);
    cursor_reset(cursor, game_var);
    redraw_screen(scr, *gamestate_p, game_var->b_size);
}

void reset_offsets(screen_size_t *scr)
{
    scr->board_x_offset = 2;
    scr->board_y_offset = 1;
}
