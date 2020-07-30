#include <iostream>
#include <cstdio>
#include <chrono>
#include "sudoku.h"
using namespace std;

int main() {

  char board[9][9];
 
  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============= Pre-supplied functions =============" << "\n\n";

  cout << "Calling load_board():" << '\n';
  load_board("easy.dat", board);

  cout << '\n' << "Displaying Sudoku board with display_board():" << '\n';
  display_board(board);
  cout << "Done!" << "\n\n";

  cout << "=================== Question 1 ===================" << "\n\n";
  
  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << "\n\n";

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << "\n\n";
  
  cout << "=================== Question 2 ===================" << "\n\n";

  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  // Should NOT be OK - length of position is >2
  cout << "Putting '1' into I88 is ";
  if (!make_move("I88", '1', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  // Should NOT be OK - position is invalid: J is out of range
  cout << "Putting '1' into J1 is ";
  if (!make_move("J1", '1', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  // Should NOT be OK - E8 is already filled in
  cout << "Putting '2' into E8 is ";
  if (!make_move("E8", '2', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  // Should NOT be OK - 1 is in the same column
  cout << "Putting '1' into D5 is ";
  if (!make_move("D5", '1', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);
  
  // Should NOT be OK - 3 is in the same row
  cout << "Putting '3' into D5 is ";
  if (!make_move("D5", '3', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  // Should NOT be OK - 4 is in the same subsection 
  cout << "Putting '4' into A1 is ";
  if (!make_move("A1", '4', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  // Should be OK
  cout << "Putting '5' into A1 is ";
  if (!make_move("A1", '5', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);
  
  // Should NOT be OK - A1 is already filled in
  cout << "Putting '5' into A1 is ";
  if (!make_move("A1", '5', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);
  
  cout << "=================== Question 3 ===================" << "\n\n";

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board))
    cout << "Save board to 'easy-copy.dat' successful." << '\n';
  else
    cout << "Save board failed." << '\n';
  cout << '\n';

  cout << "=================== Question 4 ===================" << "\n\n";
 
  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:" << '\n';
    display_board(board);
  } else 
    cout << "A solution cannot be found." << '\n';
  cout << '\n';
  
  load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:" << '\n';
    display_board(board);
  } else 
    cout << "A solution cannot be found." << '\n';
  cout << '\n';

  // An easy board
  load_board("testeasy.dat", board);
  if (solve_board(board)) {
    cout << "The easy test board has a solution:" << '\n';
    display_board(board);
  } else
    cout << "A solution cannot be found." << '\n';
  cout << '\n';

  // Non-standard notation used for empty cells
  load_board("testnonstdempty.dat", board);
  if (solve_board(board)) {
    cout << "The non-standard empty notation test board has a solution:" << '\n';
    display_board(board);
  } else
    cout << "A solution cannot be found." << '\n';
  cout << '\n';

  // Another easy board
  load_board("testeasy2.dat", board);
  if (solve_board(board)) {
    cout << "The easy test board has a solution:" << '\n';
    display_board(board);
  } else
    cout << "A solution cannot be found." << '\n';
  cout << '\n';

  // A medium board
  load_board("testmedium.dat", board);
  if (solve_board(board)) {
    cout << "The medium test board has a solution:" << '\n';
    display_board(board);
  } else
    cout << "A solution cannot be found." << '\n';
  cout << '\n';

  // A hard board
  load_board("testhard.dat", board);
  if (solve_board(board)) {
    cout << "The hard test board has a solution:" << '\n';
    display_board(board);
  } else
    cout << "A solution cannot be found." << '\n';
  cout << '\n';

  // Another hard board
  load_board("testhard2.dat", board);
  if (solve_board(board)) {
    cout << "The hard test board has a solution:" << '\n';
    display_board(board);
  } else
    cout << "A solution cannot be found." << '\n';
  cout << '\n';  

  // One of the hardest boards
  load_board("testveryhard.dat", board);
  if (solve_board(board)) {
    cout << "The very hard test board has a solution:" << '\n';
    display_board(board);
  } else
    cout << "A solution cannot be found." << '\n';
  cout << '\n';

  // The "World's hardest sudoku"
  load_board("testveryhard2.dat", board);
  if (solve_board(board)) {
    cout << "The very hard test board has a solution:" << '\n';
    display_board(board);
  } else
    cout << "A solution cannot be found." << '\n';
  cout << '\n';

  // Should NOT work: impossible board
  load_board("impossible.dat", board);
  if (solve_board(board)) {
    cout << "The impossible test board has a solution:" << '\n';
    display_board(board);
  } else
    cout << "A solution cannot be found." << '\n';
  cout << '\n';

  // Should fill in starting with 123456789: empty board
  load_board("testempty.dat", board);
  if (solve_board(board)) {
    cout << "The empty test board has a solution:" << '\n';
    display_board(board);
  } else
    cout << "A solution cannot be found." << '\n';
  cout << '\n';

  // Should NOT work: board full of ones
  load_board("fullone.dat", board);
  if (solve_board(board)) {
    cout << "The board full of ones has a solution:" << '\n';
    display_board(board);
  } else
    cout << "A solution cannot be found for the board in fullone.dat." << '\n';
  cout << '\n';

  // Should NOT work: board is almost full of ones
  load_board("almostfullone.dat", board);
  if (solve_board(board)) {
    cout << "The board almost full of ones has a solution:" << '\n';
    display_board(board);
  } else
    cout << "A solution cannot be found for the board in almostfullone.dat." << '\n';
  cout << '\n';
  
  cout << "=================== Question 5 ===================" << "\n\n";

  //Variables to check how long it takes to reach a solution
  auto t1= chrono::high_resolution_clock::now();
  auto t2= chrono::high_resolution_clock::now();
  auto duration= chrono::duration_cast<chrono::seconds>(t2-t1).count();

  //Variable to count the number of steps needed to reach a solution
  int steps = 0;

  load_board("mystery1.dat", board);
  //Start timer
  t1 = chrono::high_resolution_clock::now();
  if (solve_mystery_board(board, steps)) {
    //Stop timer
    t2 =  chrono::high_resolution_clock::now();
    cout << "The mystery1 board has a solution:" << '\n';
    display_board(board);
    duration = chrono::duration_cast<chrono::milliseconds>(t2-t1).count();
    cout << "It took me " << duration << " milliseconds to complete the board." << endl;
  } else
    cout << "A solution cannot be found for the board in mystery1.dat." << '\n';
  cout << '\n';

  load_board("mystery2.dat", board);
  //Start timer
  t1 = chrono::high_resolution_clock::now();
  steps = 0;
  if (solve_mystery_board(board, steps)) {
    //Stop timer
    t2 =  chrono::high_resolution_clock::now();
    cout << "The mystery2 board has a solution:" << '\n';
    display_board(board);
    duration = chrono::duration_cast<chrono::milliseconds>(t2-t1).count();
    cout << "It took me " << duration << " milliseconds to complete the board." << endl;
  } else
    cout << "A solution cannot be found for the board in mystery2.dat." << '\n';
  cout << '\n';

  load_board("mystery3.dat", board);
  //Start timer
  t1 = chrono::high_resolution_clock::now();
  steps = 0;
  if (solve_mystery_board(board, steps)) {
    //Stop timer
    t2 =  chrono::high_resolution_clock::now();
    cout << "The mystery3 board has a solution:" << '\n';
    display_board(board);
    duration = chrono::duration_cast<chrono::milliseconds>(t2-t1).count();
    cout << "It took me " << duration << " milliseconds to complete the board." << endl;
  } else
    cout << "A solution cannot be found for the board in mystery3.dat." << '\n';
  cout << '\n';

  return 0;
}
