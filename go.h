#ifndef GO_H
#define GO_H

#define LEGEND_X 2
#define LEGEND_Y 2

#define BOARD_X 40
#define BOARD_Y 3
#define BOARD_SIZE 19
#define SIMPLIFIED 0 // 1 for a siplified board pattern

#define STONE_NO 0
#define STONE_WHITE 1
#define STONE_BLACK 2

#define CURSOR_NONE -1
#define CURSOR_GREEN 0
#define CURSOR_RED 1
#define CURSOR_YELLOW 2

#define MESSAGE_NONE -1
#define MESSAGE_VALID_PLACE 0
#define MESSAGE_STONE_PLACED 1
#define MESSAGE_INVALID_PLACE 2

typedef struct Cursor
{
    int x;
    int y;
    int color;
} Cursor;

void legend_printout();

void change_color(int stone_type, int cursor_color);

void board_tile_printout(int* gamestate,int x, int y, int cursor_color);

void board_printout(int* gamestate);

void turn_printout(int player);

void message_printout(int message_id);

void cursor_move(int* gamestate, Cursor* cur, int dx, int dy);

void place_stone(int* gamestate, Cursor* cur, int color);

void remove_stone(int* gamestate, int x, int y);

void cursor_draw(int* gamestate, Cursor* cur);

bool is_valid_position(int* gamestate, Cursor* cur, int player);

bool has_liberties(int* gamestate, int x, int y);

void kill_surroundings(int* gamestate, int x, int y, int player);

#endif