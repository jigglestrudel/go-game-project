#ifndef GO_H
#define GO_H

#define bool _Bool //stdbool.h

#define CHARACTER_EDGE_LEFT 195           // ├
#define CHARACTER_EDGE_RIGHT 180          // ┤
#define CHARACTER_EDGE_TOP 194            // ┬
#define CHARACTER_EDGE_BOTTOM 193         // ┴
#define CHARACTER_CROSS_INSIDE 197        // ┼
#define CHARACTER_LINE 196                // ─
#define CHARACTER_STONE 254               // ■
#define CHARACTER_CORNER_TOP_LEFT 218     // ┌
#define CHARACTER_CORNER_TOP_RIGHT 191    // ┐
#define CHARACTER_CORNER_BOTTOM_LEFT 192  // └
#define CHARACTER_CORNER_BOTTOM_RIGHT 217 // ┘
#define CHARACTER_CHECKERBOARD_DOWN 220   // ▄
#define CHARACTER_CHECKERBOARD_UP 223     // ▀

#define KEY_ENTER 0x0d
#define KEY_ESCAPE 0x1b
#define SPEC_KEY_UP_ARROW 0x50
#define SPEC_KEY_DOWN_ARROW 0x48
#define SPEC_KEY_LEFT_ARROW 0x4b
#define SPEC_KEY_RIGHT_ARROW 0x4d

#define LEGEND_X 2
#define LEGEND_Y 2
#define LEGEND_HEIGHT 17
#define LEGEND_FULL_HEIGHT 22

#define BOARD_X 40
#define BOARD_Y 3   // needs to be bigger than 1
#define BOARD_SIZE 19
#define PRETTY_BOARD_PATTERN 0 // 0 for a traditional board pattern

#define STONE_NO 0
#define STONE_WHITE 1
#define STONE_BLACK 2

#define CURSOR_NONE -1
#define CURSOR_GREEN 0
#define CURSOR_RED 1
#define CURSOR_YELLOW 2

#define MESSAGE_NONE -1 // clears message space
#define MESSAGE_PENDING 0 // "Press <enter> to confirm or <esc> to cancel"
#define MESSAGE_NEW_GAME 1 // "board: [1]: 9x9   [2]: 13x13 [3]: 19x19 [4]: custom"
#define MESSAGE_INVALID_PLACE 2 // "You can't place a stone here"
#define MESSAGE_NAME_INVALID 3 // "That's not a valid filename"
#define MESSAGE_FILENAME_INPUT 4 // "Enter a valid filename max %d letters"
#define MESSAGE_SAVEFILE_OVERWRITE 5 // "Savefile will be overwritten <enter> to save <esc> to cancel"
#define MESSAGE_GAME_SAVED 6 // "Game saved!"
#define MESSAGE_GAME_LOADED 7 // "Game loaded!"
#define MESSAGE_HANDICAP_IN_PROGRESS 8  // "Handicap placement mode <enter> to save <esc> to cancel"

#define LONG_INPUT_ENTER 0
#define LONG_INPUT_ESCAPE 1
#define LONG_INPUT_BUFFER_SIZE 32

/// @brief a struct containing information about cursor's position and color
typedef struct
{
    int x;
    int y;
    int color;
} cursor_t;

/// @brief a struct with all game variables that need to be saved
typedef struct
{
    int b_size;
    bool handicap_mode;
    int current_player;
    int last_placed_x;
    int last_placed_y;
    int last_captured_x; // used to enforce the ko rule
    int last_captured_y; // used to enforce the ko rule
    float black_score;
    float white_score;
} game_var_t;

/// @brief a struct containing info about window's size and board's offsets
typedef struct 
{
    int s_w;
    int s_h;
    int board_x_offset;
    int board_y_offset;
    int right_border;
} screen_size_t;

/// @brief prints out information about the controls
void legend_printout();

/// @brief prints out the current game info under the legend
/// @param x cursor x position
/// @param y cursor y position
/// @param b black's player score
/// @param w white's player's score
void down_legend_printout(int x, int y, float b, float w);

/// @brief changes the color of the printed text in my set style
/// @param stone_type which stone's color should be applied
/// @param cursor_color which of the cursors highlight should be applied (default: none)
void change_color(int stone_type, int cursor_color);

/// @brief prints out the specified board tile
/// @param scr a struct containing info about the screen (required for drawing)
/// @param game_state pointer to the one-dimensional intiger array containing the placed stones
/// @param b_size size of the board
/// @param x the first coordinate of the tile
/// @param y the second coordinate of the tile
/// @param cursor_color applying the cursor's highlight (default none)
void board_tile_printout(screen_size_t *scr, int *game_state, int b_size, int x, int y, int cursor_color);

/// @brief prints out a cosmetic border tile
void border_tile_printout();

/// @brief function to print out the whole board with all the tiles
/// @param scr a struct containing info about the screen (required for drawing)
/// @param gamestate pointer to the one-dimensional intiger array containing the placed stones
/// @param b_size size of the board
void board_printout(screen_size_t *scr, int *gamestate, int b_size);

/// @brief redraws the whole screen
/// @param scr a struct containing info about the screen (required for drawing)
/// @param gamestate pointer to the one-dimensional intiger array containing the placed stones
/// @param b_size size of the board
void redraw_screen(screen_size_t *scr, int *gamestate, int b_size);

/// @brief prints out information about which player's turn it is above the board
/// @param player the player to print the message about
void turn_printout(int player);

/// @brief prints out a message from a set of predefined messages under the board
/// @param message_id
void message_printout(int message_id);

/// @brief moves the cursor and redraws the cursor
/// @param scr a struct containing info about the screen (required for drawing)
/// @param gamestate pointer to the one-dimensional intiger array containing the placed stones
/// @param cur pointer to the cursor variable
/// @param dx the distance the cursor should be moved on the x axis
/// @param dy the distance the cursor should be moved on the y axis
void cursor_move(screen_size_t *scr, int *gamestate, int b_size, cursor_t *cur, int dx, int dy);

/// @brief defaults the cursor
/// @param cur pointer to the cursor struct
/// @param game_var pointer to the game variables struct
void cursor_reset(cursor_t* cur, game_var_t* game_var);

/// @brief places a stone and redraws the tile
/// @param scr a struct containing info about the screen (required for drawing)
/// @param gamestate pointer to the one-dimensional intiger array containing the placed stones
/// @param b_size size of the board
/// @param cur pointer to the cursor variable
/// @param player the player's stone color
void place_stone(screen_size_t *scr, int *gamestate, int b_size, cursor_t *cur, int player);

/// @brief removes a stone and redraws the tile
/// @param scr a struct containing info about the screen (required for drawing)
/// @param gamestate pointer to the one-dimensional intiger array containing the placed stones
/// @param b_size size of the board
/// @param x the first coordinate of the tile
/// @param y the second coordinate of the tile
void remove_stone(screen_size_t *scr, int *gamestate, int b_size, int x, int y);

/// @brief redraws the cursor on the tile it points to
/// @param scr a struct containing info about the screen (required for drawing)
/// @param gamestate pointer to the one-dimensional intiger array containing the placed stones
/// @param b_size size of the board
/// @param cur pointer to the cursor variable
void cursor_draw(screen_size_t *scr, int *gamestate, int b_size, cursor_t *cur);


/// @brief checks whether the player can place a stone in (x, y)
/// @param gamestate pointer to the one-dimensional intiger array containing the placed stones
/// @param b_size size of the board
/// @param x 1st coordinate of the tile
/// @param y 2nd coordinate of the tile
/// @param player stone color
/// @param stone_x stone's x captured in the last round (ko rule)
/// @param stone_y stone's y captured in the last round (ko rule)
/// @return true if a position fullfills the rules else false
bool is_valid_position(int *gamestate, int b_size, int x, int y, int player, int stone_x, int stone_y);

/// @brief chekcs whether the tile has liberties for the player's stone
/// @param gamestate pointer to the one-dimensional intiger array containing the placed stones
/// @param b_size size of the board
/// @param x the first coordinate of the tile
/// @param y the second coordinate of the tile
/// @return if a stone of this color would have liberties in this place on the board
bool has_liberties(int *gamestate, int b_size, int x, int y);

/// @brief checks whether or not a move would be an obvious suicide
/// @param gamestate pointer to the one-dimensional intiger array containing the placed stones
/// @param b_size size of the board
/// @param x the first coordinate of the tile
/// @param y the second coordinate of the tile
/// @param player the player's stone color
/// @return if the stone placed on the tile would kill any of opponents stones
bool can_kill_surroundings(int *gamestate, int b_size, int x, int y, int player);

/// @brief recursive function calculating the liberties of a chain of stones
/// @param gamestate pointer to the one-dimensional intiger array containing the placed stones
/// @param b_size size of the board
/// @param counted_stones pointer to a one-dimensional boolean array used for chechikng if stone's liberties have already been calculated
/// @param x the first coordinate of the tile
/// @param y the second coordinate of the tile
/// @param player the player's stone color
/// @return true if the chain doesn't have liberties, false - if it has them
bool chain_check_suffocation(int *gamestate, int b_size, bool *counted_stones, int x, int y, int player);

/// @brief function removing surrounding stones in chains with no liberties
/// @param scr a struct containing info about the screen (required for drawing)
/// @param gamestate pointer to the one-dimensional intiger array containing the placed stones
/// @param b_size size of the board
/// @param x the first coordinate of the tile
/// @param y the second coordinate of the tile
/// @param game_var struct with game variables
void capture_surrounding_chains(screen_size_t *scr, int *gamestate, int b_size, int x, int y, game_var_t* game_var);

/// @brief checks if a stone placed on (x,y) by the player would be immedietly captured
/// @param gamestate pointer to the one-dimensional intiger array containing the placed stones
/// @param b_size size of the board
/// @param x the first coordinate of the tile
/// @param y the second coordinate of the tile
/// @param player the player's stone color
/// @return true if (x, y) is a suicidal position for the player
bool will_kill_itself(int *gamestate, int b_size, int x, int y, int player);

/// @brief checks a chain starting in (x,y) and removes it if it doesnt have any liberties
/// @param scr a struct containing info about the screen (required for drawing)
/// @param gamestate pointer to the one-dimensional intiger array containing the placed stones
/// @param b_size size of the board
/// @param x the first coordinate of the tile
/// @param y the second coordinate of the tile
/// @param player the player's stone color
/// @param last_captured_x_p pointer to the variable storing the captured stone (ko rule)
/// @param last_captured_y_p pointer to the variable storing the captured stone (ko rule)
/// @return the number of captured stones
int capture_chain(screen_size_t *scr, int *gamestate, int b_size, int x, int y, int player, int *last_captured_x_p, int *last_captured_y_p);

/// @brief checks if the player's stone on (x, y) is in a chain that has liberties
/// @param gamestate pointer to the one-dimensional intiger array containing the placed stones
/// @param b_size size of the board
/// @param x the first coordinate of the tile
/// @param y the second coordinate of the tile
/// @param player the player's stone color
/// @return true - when chain has a liberty, false - when a chain doesn't have a liberty
bool check_chain_for_liberties(int *gamestate, int b_size, int x, int y, int player);

/// @brief gets a string from the user
/// @param buffer buffer to store the input to
/// @return LONG_INPUT_ENTER if enter finished the input, else LONG_INPUT_ESC
int get_long_input(char *buffer);

/// @brief checks if a savename is a valid file name: without / \ | < > " : ?
/// @param buffer name to check
/// @return true if the name is a valid file name
bool is_valid_savename(const char *name);

/// @brief removes spaces from the end of a savename
/// @param name pointer to a string to edit
void remove_last_spaces_from_savename(char *name);

/// @brief saves a game to the file
/// @param name name of the file
/// @param gamestate the one-dimensional array holding the game state
/// @param game_var game variables struct
/// @return true if saving succeeded
bool save_game(char* name, int* gamestate, game_var_t* game_var);

/// @brief resets game variables (all but b_size) to default
/// @param game_var game_var_t struct of game variables
void reset_game_var(game_var_t* game_var);

/// @brief checks if a file of that name exists
/// @param name string containing the file name
/// @return true if a falie of that name exists
bool file_exists(char* name);

/// @brief loads a game from afile
/// @param name name of the file
/// @param gamestate_p pointer to the one-dimensional array holding the game state
/// @param game_var game variables struct
/// @return true if loading succeeded
bool load_game(char *name, int **gamestate_p, game_var_t *game_var);

/// @brief creates a game board of the desired size
/// @param gamestate_p pointer pointer to the array storing the game state
/// @param b_size size of the new board
/// @return false if the malloc failed
bool create_board(int** gamestate_p, int b_size);

/// @brief a function moving the cursor using the arrow keys
/// @param scr a struct containing info about the screen (required for drawing)
/// @param gamestate one-dimensional array holding the game state
/// @param b_size size of the board
/// @param cursor pointer to the cursor struct
void control_the_cursor(screen_size_t *scr, int* gamestate, int b_size, cursor_t* cursor);

/// @brief creates a new game and redraws the screen
/// @param scr a struct containing info about the screen (required for drawing)
/// @param gamestate_p pointer pointer to the array storing the game state
/// @param game_var game variables struct
/// @param cursor pointer to the cursor struct
void new_game(screen_size_t *scr, int** gamestate_p, game_var_t* game_var, cursor_t* cursor);

/// @brief resets the board drawing offsets
/// @param scr a struct containing info about the screen 
void reset_offsets(screen_size_t *scr);

/// @brief calculates the total score for the players
/// @param gamestate array storing the game state
/// @param game_var game variables struct
void calculate_score(int* gamestate, game_var_t* game_var);

int assign_territory(int* gamestate, bool* counted_spaces, game_var_t* game_var, int x, int y);

#endif 
