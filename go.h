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

/// @brief a struct containing information about cursor's position and color
typedef struct Cursor
{
    int x;
    int y;
    int color;
} Cursor;

/// @brief prints out information about the controls
void legend_printout();

/// @brief changes the color of the printed text in my set style
/// @param stone_type which stone's color should be applied
/// @param cursor_color which of the cursors highlight should be applied (default: none)
void change_color(int stone_type, int cursor_color);

/// @brief prints out the specified board tile
/// @param game_state pointer to the one-dimensional intiger array containing the placed stones
/// @param x the first coordinate of the tile
/// @param y the second coordinate of the tile
/// @param cursor_color applying the cursor's highlight (default none)
void board_tile_printout(int* gamestate,int x, int y, int cursor_color);

/// @brief prints out a cosmetic border tile 
void border_tile_printout();

/// @brief function to print out the whole board with all the tiles
/// @param gamestate pointer to the one-dimensional intiger array containing the placed stones
void board_printout(int* gamestate);

/// @brief prints out information about which player's turn it is above the board
/// @param player the player to print the message about
void turn_printout(int player);

/// @brief prints out a message from a set of predefined messages under the board
/// @param message_id 
void message_printout(int message_id);

/// @brief moves the cursor and redraws the cursor
/// @param gamestate pointer to the one-dimensional intiger array containing the placed stones
/// @param cur pointer to the cursor variable 
/// @param dx the distance the cursor should be moved on the x axis
/// @param dy the distance the cursor should be moved on the y axis
void cursor_move(int* gamestate, Cursor* cur, int dx, int dy);

/// @brief places a stone and redraws the tile
/// @param gamestate pointer to the one-dimensional intiger array containing the placed stones
/// @param cur pointer to the cursor variable 
/// @param player the player's stone color
void place_stone(int* gamestate, Cursor* cur, int player);

/// @brief removes a stone and redraws the tile
/// @param gamestate pointer to the one-dimensional intiger array containing the placed stones
/// @param x the first coordinate of the tile
/// @param y the second coordinate of the tile
void remove_stone(int* gamestate, int x, int y);

/// @brief redraws the cursor on the tile it points to
/// @param gamestate pointer to the one-dimensional intiger array containing the placed stones
/// @param cur pointer to the cursor variable 
void cursor_draw(int* gamestate, Cursor* cur);

/// @brief checks whether the player can place a stone in the place the cursor is pointing to
/// @param gamestate pointer to the one-dimensional intiger array containing the placed stones
/// @param cur pointer to the cursor variable 
/// @param player the player's stone color
/// @return if placing a stone of player's color would be a valid move
bool is_valid_position(int* gamestate, Cursor* cur, int player);

/// @brief chekcs whether the tile has liberties for the player's stone
/// @param gamestate pointer to the one-dimensional intiger array containing the placed stones
/// @param x the first coordinate of the tile
/// @param y the second coordinate of the tile
/// @param player the player's stone color
/// @return if a stone of this color would have liberties in this place on the board
bool has_liberties(int* gamestate, int x, int y, int player);

/// @brief checks whether or not a move would be an obvious suicide
/// @param gamestate pointer to the one-dimensional intiger array containing the placed stones
/// @param x the first coordinate of the tile
/// @param y the second coordinate of the tile
/// @param player the player's stone color
/// @return if the stone placed on the tile would kill any of opponents stones
bool can_kill_surroundings(int* gamestate, int x, int y, int player);

/// @brief recursive function calculating the liberties of a chain of stones
/// @param gamestate pointer to the one-dimensional intiger array containing the placed stones
/// @param counted_stones pointer to a one-dimensional boolean array used for chechikng if stone's liberties have already been calculated
/// @param x the first coordinate of the tile
/// @param y the second coordinate of the tile
/// @param player the player's stone color
/// @return 1 if the chain doesn't have liberties and 0 if the chain has them
int chain_check_suffocation(int* gamestate, bool* counted_stones, int x, int y, int player);

/// @brief function removing surrounding stones in chains with no liberties
/// @param gamestate pointer to the one-dimensional intiger array containing the placed stones
/// @param x the first coordinate of the tile
/// @param y the second coordinate of the tile
/// @param player the player's stone color
void capture_surrounding_chains(int *gamestate, int x, int y, int player);


void capture_chain(int* gamestate, int x, int y, int player);

bool check_chain(int* gamestate, int x, int y, int player);

#endif