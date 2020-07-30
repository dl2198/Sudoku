void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);
bool is_complete(const char board[9][9]);
bool make_move(const char position[], char digit, char board[9][9]);
bool save_board(const char filename[], char board[9][9]);
bool solve_board(char board[9][9]);
bool solve_mystery_board(char board[9][9], int steps);
bool final_check(char board[9][9]);
bool search_array(const char board[9][9], int start_row, int finish_row, int start_column, int finish_column, char target);
bool is_valid_position(const char position[], int length);
int convert_position(char character);
void convert_index(char* position, int row, int column);
bool is_valid_move(const char board[9][9], int row, int column, char digit);
void find_empty_cell(char* position, const char board[9][9]);

