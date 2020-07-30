#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

// You are pre-supplied with the functions below. Add your own
// function definitions to the end of this file.

// Constants to define the range of the sudoku board
const int START_ROW = 0;
const int FINISH_ROW = 8;
const int START_COLUMN = 0;
const int FINISH_COLUMN = 8;

// Constant to define the length of a position string e.g. 'A1'
const int POSITION_LENGTH = 2;

//pre-supplied function to load a Sudoku board from a file
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << '\n';
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

// internal helper function
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << '\n';
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << '\n';
}

// internal helper function
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << '\n';
}

// pre-supplied function to display a Sudoku board
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

// TASK 1
// function to check if a sudoku board is complete
bool is_complete(const char board[9][9])
{
  char target1='.'; //standard notation for empty cells
  char target2; //in case non-standard notation is used

  //Searching for a dot
  if (search_array(board, START_ROW, FINISH_ROW, START_COLUMN, FINISH_COLUMN, target1))
    return false;

  //Searching for a non-standard character
  for (target1= 32, target2 = 58; target1 < 49 && target2 < 127; target1++, target2++)
    if (search_array(board, START_ROW, FINISH_ROW, START_COLUMN, FINISH_COLUMN, target1)
	|| (search_array(board, START_ROW, FINISH_ROW, START_COLUMN, FINISH_COLUMN, target2)))
      return false;

  return true;
}

// helper function to search for a target character in a specified section of the sudoku board
bool search_array(const char board[9][9], int start_row, int finish_row, int start_column, int finish_column, char target)
{
  //Define a range of rows
  for (int counter_rows = start_row ; counter_rows <= finish_row; counter_rows++)
    {
      //Define a range of columns
      for (int counter_columns = start_column; counter_columns <= finish_column; counter_columns++)
	//Search for the target
	if (board[counter_rows][counter_columns] == target)
	  return true;
    }
  return false;
}
// END OF TASK 1

// TASK 2
// function to place a digit on a sudoku board at a given position
bool make_move(const char position[], char digit, char board[9][9])
{
  //Check if the position string supplied is valid
  if (is_valid_position(position, POSITION_LENGTH))
    {
      //Convert the position in array indexes
      int row = convert_position(position[0]);
      int column = convert_position(position[1]);

      //Check if digit is valid
      if (digit >= '1' && digit <= '9')
	//Check if the rules allow the move
	if (is_valid_move(board, row, column, digit))
	  {
	    //Make the move
	    board[row][column] = digit;
	    return true;
	  }
    }

  return false;
}

// helper function to check if a position is valid
bool is_valid_position(const char position[], int length)
{
  //Check if the length of the string is valid
  if (strlen(position) == static_cast<size_t>(length))
    //Check if the first character is a letter A-I
    if (position[0] >= 'A' && position[0] <= 'I')
      //Check if the second character is a digit 1-9
      if (position[1] >= '1' && position[1] <= '9')
	return true;

  return false;
}

// helper function to convert from position string to array indexes
int convert_position(char character)
{
  int index = 0;

  //Convert letters into integers 0-8
  if (character >= 'A' && character <= 'I')
    {
      index = character - 'A';
      return index;
    }

  //Convert digits into integers 0-8
  if (character >= '1' && character <= '9')
    {
      index = character - '1';
      return index;
    }

  return index;
}

// helper function to convert from indexes to position string
void convert_index(char* position, int row, int column)
{
  position[0]= static_cast<char>(row) + 'A';
  position[1]= static_cast<char>(column) + '1';
}

// helper function to check if a move is valid
bool is_valid_move(const char board[9][9], int row, int column, char digit)
{
  //Check that the cell is empty (even if characters other than '.' are used for empty cells)
  if (board[row][column] < 49 || board[row][column] > 57)
    //Check that the digit is not on the same line or column
    if (!search_array(board, row, row, START_COLUMN, FINISH_COLUMN, digit)
	  && !search_array(board, START_ROW, FINISH_ROW, column, column, digit))
	{
	  //Move to the top-left cell of a block
	  while (row%3)
	    row--;
	  while (column%3)
	    column--;

	  //Define the range of the 3x3 block
	  int last_row_block = row + 2;
	  int last_column_block = column + 2;

	  //Check that the digit is not in the block
	  if (!search_array(board, row, last_row_block, column, last_column_block, digit))
	    return true;
	}
  
  return false;
}
// END OF TASK 2

// TASK 3
// function to output a sudoku board to a file
bool save_board(const char filename[], char board[9][9])
{
  ofstream out;
  out.open(filename);

  //Check outstream is OK
  if (out)
    {
      //Row by row
      for (int row = 0; row <= 8; row++)
	{
	  //Column by column
	  for (int column = 0; column <= 8; column++)
	    //Write to file
	    out.put(board[row][column]);
	  out.put('\n');
	}
      out.close();
      return true;
    }
  
  out.close();
  return false;
}
// END OF TASK 3

// TASK 4
// function to solve a sudoku board
bool solve_board(char board[9][9])
{
  //Basecase: the board is complete and a valid solution
  if (is_complete(board) && final_check(board))
    return true;
  
  //Look for the first empty cell
  char empty_position[2];
  find_empty_cell(empty_position, board);

  //Define range of digits 1-9
  for (char digit = '1'; digit <= '9'; digit++)
    {
      //Check if the rules allow for the digit to be inserted
      if (make_move(empty_position, digit, board))
	{
	  //Check if making this move leads to a solution (recursion)
	  if (solve_board(board))
	    //Exit the for loop
	    return true;

	  //If there's no solution, make the cell empty again
	  int row = convert_position(empty_position[0]);
	  int column = convert_position(empty_position[1]);
	  board[row][column] = '.';
	}
    }
  
  return false;
}

//helper function to run a final check of the board
bool final_check(char board[9][9])
{
  int row, column;

  for (row = START_ROW; row <= FINISH_ROW; row++)
    for (column = START_COLUMN; column <= FINISH_COLUMN; column++)
      {
	char digit = board[row][column];
	board[row][column] = '.';
	char check_position[POSITION_LENGTH];
	convert_index(check_position, row, column);
	if (!make_move(check_position, digit, board))
	  return false;
	board[row][column] = digit;
      }
  return true;
}

// helper function to find the first empty cell in a sudoku board
void find_empty_cell(char* position, const char board[9][9])
{
  //Row by row
  for (int row = 0; row < 9; row++)
    {
      //Column by column
      for (int column = 0; column < 9; column++)
	{
	  //If cell is empty (even in non-std notation)
	  if (board[row][column]<49 || board[row][column]>57)
	    {
	      //Output the position to a string array
	      convert_index(position, row, column);
	    }
	}
    }
}
// END OF TASK 4

// TASK 5
// function to solve a sudoku board counting the steps
bool solve_mystery_board(char board[9][9], int steps)
{
  //Basecase: the board is complete and a valid solution
  if (is_complete(board) && final_check(board))
    {
      cout << "Number of steps: " << steps << endl;
      return true;
    }

  //Look for the first empty cell in the board
  char empty_position[2];
  find_empty_cell(empty_position, board);

  //Define range of digits 1-9
  for (char digit = '1'; digit <= '9'; digit++)
    {
      //Count a step
      steps++;
      //Check if the rules allow for the digit to be inserted
      if (make_move(empty_position, digit, board))
	{
	  //Check if making this move leads to a solution (by calling the function recursively)
	  if (solve_mystery_board(board, steps))
	    //Exit the for loop
	    return true;

	  //If there's no solution,make the cell empty again
	  int row = convert_position(empty_position[0]);
	  int column = convert_position(empty_position[1]);
	  board[row][column] = '.';
	}
    }
  
  return false;
}
// END OF TASK 5
