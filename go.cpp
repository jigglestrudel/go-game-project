#include "conio2.h"
#include "go.h"

void legend_printout()
{
    textcolor(WHITE);
    gotoxy(LEGEND_X, LEGEND_Y);
    cputs("Tomasz Krepa 193047");
    gotoxy(LEGEND_X, LEGEND_Y + 2);
    cputs("Functionality:");
    gotoxy(LEGEND_X, LEGEND_Y + 3);
    cputs("(a) (b) (c) (d) (e)");
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

void change_color(int stone_type, int cursor_color = -1)
{
    if (cursor_color == -1)
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

void board_tile_printout(int* game_state, int x, int y, int cursor_color = CURSOR_NONE)
{
    gotoxy(BOARD_X + 2 + x * 2, BOARD_Y + 1 + y);
    switch (game_state[x + y * BOARD_SIZE])
    {
    case STONE_NO:
        change_color(STONE_NO, cursor_color);
        if (SIMPLIFIED)
        {
            putch('<');
            putch('>');
        }
        else
        {   
            if ((x % 2 && y % 2) || (!(x % 2) && !(y % 2))) 
            // this creates the pattern checkerboard pattern
            {
                putch(220); 
                putch(223); // ▄▀
                //putch(191);
                //putch(192); // ┐└
                //putch(180); 
                //putch(195); // ┤├
            }
            else
            {
                putch(223); 
                putch(220); // ▀▄
                //putch(217);
                //putch(218); // ┘┌
                //putch(180); 
                //putch(195); // ┤├
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
    if (SIMPLIFIED)
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

void board_printout(int* gamestate)
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

void cursor_draw(int* gamestate, Cursor* cur)
{
    board_tile_printout(gamestate, cur->x, cur->y, cur->color);
}

void cursor_move(int* gamestate, Cursor* cur, int dx, int dy)
{

    board_tile_printout(gamestate, cur->x, cur->y);

    cur->x = (cur->x + dx) >= BOARD_SIZE ? BOARD_SIZE - 1 : ((cur->x + dx) < 0 ? 0 : (cur->x + dx));
    cur->y = (cur->y + dy) >= BOARD_SIZE ? BOARD_SIZE - 1 : ((cur->y + dy) < 0 ? 0 : (cur->y + dy));

    cursor_draw(gamestate, cur);
}

void place_stone(int* gamestate, Cursor* cur, int color)
{
    gamestate[cur->x + BOARD_SIZE * cur->y] = color;
    cursor_draw(gamestate, cur);
}

void remove_stone(int* gamestate, int x, int y)
{
    gamestate[x + y*BOARD_SIZE] = STONE_NO;
    board_tile_printout(gamestate, x, y);
}

void turn_printout(int player)
{
    gotoxy(BOARD_X, BOARD_Y-1);
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
    gotoxy(BOARD_X, BOARD_Y+BOARD_SIZE+2);
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

bool has_liberties(int* gamestate, int x, int y, int player)
{
    if ((x-1) >= 0)
        if (gamestate[(x-1) + y*BOARD_SIZE] == STONE_NO || gamestate[(x-1) + y*BOARD_SIZE] == player)
            return true;
    if ((x+1) < BOARD_SIZE)
        if (gamestate[(x+1) + y*BOARD_SIZE] == STONE_NO || gamestate[(x+1) + y*BOARD_SIZE] == player )
            return true;
    if ((y-1) >= 0)
        if (gamestate[x + (y-1)*BOARD_SIZE] == STONE_NO || gamestate[x + (y-1)*BOARD_SIZE] == player)
            return true;
    if ((y+1) < BOARD_SIZE)
        if (gamestate[x + (y+1)*BOARD_SIZE] == STONE_NO || gamestate[x + (y+1)*BOARD_SIZE] == player)
            return true;

    return false;
}

bool is_valid_position(int* gamestate, Cursor* cur, int player)
{
    if (gamestate[cur->x + cur->y * BOARD_SIZE] != STONE_NO)
        return false;
    else if (!has_liberties(gamestate, cur->x, cur->y, player))
        return false;
    return true;
}

void kill_surroundings(int* gamestate, int x, int y, int player)
{
    if ((x-1) >= 0)
        if (!has_liberties(gamestate, x-1, y, player))
            remove_stone(gamestate, x-1, y);
    if ((x+1) < BOARD_SIZE)
        if (!has_liberties(gamestate, x+1, y, player))
            remove_stone(gamestate, x+1, y);
    if ((y-1) >= 0)
        if (!has_liberties(gamestate, x, y-1, player))
            remove_stone(gamestate, x, y-1);
    if ((y+1) < BOARD_SIZE)
        if (!has_liberties(gamestate, x, y+1, player))
            remove_stone(gamestate, x, y+1);
}
