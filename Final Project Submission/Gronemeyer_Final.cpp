//Program Name: Smart Tic Tac Toe
//Purpose: Play tic tac toe with a friend or against an easy or hard computer
//Author: Jake Gronemeyer
//Date Last Modified: 4/30/19

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>

#ifdef _WIN32
#include <windows.h>
const char *CLEAR_SCREEN_COMMAND = "CLS";
#elif defined (__APPLE__)
const char *CLEAR_SCREEN_COMMAND = "clear";
#elif defined (__linux__)
const char *CLEAR_SCREEN_COMMAND = "clear";
#endif


using namespace std;

const int ROWS = 3;
const int COLS = 3;

//**FUNCTION outputs the board
void displayBoard(char board[][COLS])
{
    cout << setw(16) << "\nColumns\n" << setw(16)
         << "       1    2    3\n";
  	cout << "     ----++---++----" << endl;
  	cout << "Row 1| " << board[0][0] << " || " << board[0][1] << " || " << board[0][2] << " |" << endl;
  	cout << "     ----++---++----" << endl;
  	cout << "Row 2| " << board[1][0] << " || " << board[1][1] << " || " << board[1][2] << " |" << endl;
  	cout << "     ----++---++----" << endl;
  	cout << "Row 3| " << board[2][0] << " || " << board[2][1] << " || " << board[2][2] << " |" << endl;
  	cout << "     ----++---++----" << endl;
}

//**FUNCTION clears the screen
void clear_the_screen ()
{
   system (CLEAR_SCREEN_COMMAND);
}

//**FUNCTION displays menu and returns user's option as an int
int displayMenu()
{
  int menuChoice; //variable corresponds to menu options

  cout <<"\n~~~~~~~~~~~~Tic Tac Toe~~~~~~~~~~~~\n";
  cout <<  "|_________________________________|\n"
       << " 1: Play versus a friend!\n"
       << " 2: Play versus an easy computer!\n"
       << " 3: Play versus a hard computer!\n"
       << " 4: Quit\n"
       << "|_________________________________|\n";
  cin >> menuChoice;
  while (cin.fail() || menuChoice > 4 || menuChoice < 1)
  {
    cout << "Bad entry, please try again:\n ";
    cin.clear();
    cin.ignore();
    cin >> menuChoice;
  }
  return menuChoice;
}

//**FUNCTION checks if a a row/col coordinate is available to place a user move
bool locationAvailability(char board[][COLS], int row, int col)
{
  if (board[row - 1][col - 1] == '*')
    return true;
  else
    return false;
}

//**FUNCTION takes user input coordinates and adds them to the board array
void playerTurn(char board[][COLS], char player, int &turn)
{
    int row = 1, col = 1;

    cout << "Enter a row and column to place an " << player << endl;

    cout << "Row: ";
    cin >> row;
    while (cin.fail() || row > ROWS || row <= 0)
    {
      cout << "Bad entry, please try again\nRow: ";
      cin.clear();
      cin.ignore();
      cin >> row;
    }

    cout << "Column: ";
    cin >> col;
    while (cin.fail() || col > COLS || col <= 0)
    {
      cout << "Bad entry, please try again\nColumn: ";
      cin.clear();
      cin.ignore();
      cin >> col;
    }

    if (player == 'X' && locationAvailability(board, row, col))
      { board[row - 1][col - 1] = 'X';}
    else if (player == 'O' && locationAvailability(board, row, col))
      { board[row - 1][col - 1] = 'O';}
    else
      {
        cout << "That location is not available...\n";
        turn--;
      }
}

//**FUNCTION output random tic tac toe move to board array
void easyComputerTurn(char board[][COLS])
{

  bool stop = false;
    while (!stop)
    {
      int compChoiceRow = 1 + rand() % ROWS;
      int compChoiceCol = 1 + rand() % COLS;
      //cout << "Computer on easy chose row: " << compChoiceRow << " and column: " << compChoiceCol << endl; //un-comment to trace computer's choices           //TRACING TRACING TRACING
      if (locationAvailability(board, compChoiceRow, compChoiceCol))
      {
        board[compChoiceRow - 1][compChoiceCol - 1] = 'O';
        stop = true;
      }
    }
}

//**FUNCTION outputs computer chosen move based on more intelligent conditions
void compSmartMove(char board[][COLS])
{
  int row = -1;
  int col = -1;

  // Prefer middle if it is available
  if (board[1][1] == '*') { row = 1; col = 1; }
  else
  {
    // Prefer corners if they are available
    if (board[0][0] == '*')      { row = 0; col = 0; }
    else if (board[0][2] == '*') { row = 0; col = 2; }
    else if (board[2][0] == '*') { row = 2; col = 0; }
    else if (board[2][2] == '*') { row = 2; col = 2; }
    else
    {
      // Resort to random available location
      easyComputerTurn(board);
      row = -1;
      col = -1; // set to prevent later logic
    }
  }

  if (row >= 0 && col >= 0)
  {
    //cout << "MEDIUM computer chose row " << row << " and col " << col << endl;           //TRACING TRACING TRACING
    board[row][col] = 'O';
  }
}

int hardComputerTurn(char board[][COLS])
{
    // Iterate through the 8 possible winning axes:
    // Diagonals:
    int sum_rtl1 = board[0][0] + board[1][1] + board[2][2];
    cout << "sum of diag: " << sum_rtl1;                           //TRACING TRACING TRACING

    //diagonal (topleft to bottomright) defense
    if (sum_rtl1 == 200 /*This is ASCII SUM of ('O + O + *') */) {
      //cout << "HARD computer ON TARGET diagnonal move 1";           //TRACING TRACING TRACING
      if (board[0][0] == '*') { board[0][0] = 'O'; return 0; }
      if (board[1][1] == '*') { board[1][1] = 'O'; return 0; }
      if (board[2][2] == '*') { board[2][2] = 'O'; return 0; }
    }
    //diagonal (topleft to bottomright) offense
    if (sum_rtl1 == 218 /*This is ASCII SUM of ()'X + X + *') */) {
      //cout << "HARD computer ON TARGET diagnonal move 2";           //TRACING TRACING TRACING
      if (board[0][0] == '*') { board[0][0] = 'O'; return 0; }
      if (board[1][1] == '*') { board[1][1] = 'O'; return 0; }
      if (board[2][2] == '*') { board[2][2] = 'O'; return 0; }
    }

    int sum_rtl2 = board[0][2] + board[1][1] + board[2][0];
    cout << "sum of diag: " << sum_rtl2;                           //TRACING TRACING TRACING

    //diagonal (bottomleft to topright) defense
    if (sum_rtl2 == 200 /*This is ASCII SUM of ('O + O + *') */) {
      //cout << "HARD computer ON TARGET diagnonal move 3";           //TRACING TRACING TRACING
      if (board[0][2] == '*') { board[0][2] = 'O'; return 0; }
      if (board[1][1] == '*') { board[1][1] = 'O'; return 0; }
      if (board[2][0] == '*') { board[2][0] = 'O'; return 0; }
    }
    //diagonal (bottomleft to topright) defense
    if (sum_rtl2 == 218 /*This is ASCII SUM of ()'X + X + *') */) {
      //cout << "HARD computer ON TARGET diagnonal move 4";           //TRACING TRACING TRACING
      if (board[0][2] == '*') { board[0][2] = 'O'; return 0; }
      if (board[1][1] == '*') { board[1][1] = 'O'; return 0; }
      if (board[2][0] == '*') { board[2][0] = 'O'; return 0; }
    }

    // Rows for offense
    for (int r = 0; r < 3; r++) {
      int sum  = board[r][0] + board[r][1] + board[r][2];
      if (sum == 200 ) {
        for (int c = 0; c < 3; c++) {
          if (board[r][c] == '*') { board[r][c] = 'O'; return 0; }
        }
      }
    }

    // Columns for offense
    for (int c = 0; c < 3; c++) {
      int sum  = board[0][c] + board[1][c] + board[2][c];
      if (sum == 200) {
        for (int r = 0; r < 3; r++) {
          if (board[r][c] == '*') { board[r][c] = 'O'; return 0; }
        }
      }
    }

    //Rows for defense
    for (int r = 0; r < 3; r++) {
      int sum  = board[r][0] + board[r][1] + board[r][2];
      if (sum == 218) {
        for (int c = 0; c < 3; c++) {
          if (board[r][c] == '*') { board[r][c] = 'O'; return 0; }
        }
      }
    }

    // Rows for defense
    for (int c = 0; c < 3; c++) {
      int sum  = board[0][c] + board[1][c] + board[2][c];
      if (sum == 218) {
        for (int r = 0; r < 3; r++) {
          if (board[r][c] == '*') { board[r][c] = 'O'; return 0; }
        }
      }
    }

      //if no necessary offensive or defensive move, comp will make 'smart' move
     compSmartMove(board);
     return 0;

}

//**FUNCTION checks for win in row, column, or diagonal
int checkForWinner(char board[][COLS], char player)
{
  int win = 0;
  int diagWin1 = 0;
  int diagWin2 = 0;

//Test for row win
  for (int row = 0; row < ROWS; row++)
    {
      win = 0;
      for (int col = 0; col < COLS; col++)
      {
          if (board[row][col] == player)
            win++;
          if (win == 3)
            return 1;
      }
    }
  //Test for column win
  for (int col = 0; col < COLS; col++)
    {
      win = 0;
      for (int row = 0; row < ROWS; row++)
      {
          if (board[row][col] == player)
            win++;
          if (win == 3)
            return 1;
      }
    }

  //Test for diagonal win
  for (int i = 0; i < ROWS; i++)
    {
      for(int j = 0; j < ROWS; j++)
        {
          if(i == j)
          {
            if (board[i][j] == player)
              diagWin1++;
            if (diagWin1 == 3)
              return 1;
          }
          if((i + j) == (ROWS - 1))
          {
            if (board[i][j] == player)
              diagWin2++;
            if (diagWin2 == 3)
              return 1;
          }
        }
    }
    return 0;
}

//**FUNCTION checks if any moves are available
bool isBoardFull(char board[][COLS])
{
  for (int row = 0; row < ROWS; row++)
    {
      for (int col = 0; col < COLS; col++)
      {
          if (board[row][col] == '*')
            return false;
      }
    }
    return true;
}

//**FUNCTION resets board to empty
void resetBoard(char board[][COLS])
{
  for (int row = 0; row < ROWS; row++)
    {
      for (int col = 0; col < COLS; col++)
      {
        board[row][col] = '*';
      }
    }
}

//**FUNCTION returns true if player chooses to play again
bool playAgain()
{
  char answer;
  cout << "Would you like to play again? (y/n) ";
  cin >> answer;
  while (cin.fail())
  {
    cout << "Please enter lower-case 'y' or 'n':\n ";
    cin.clear();
    cin.ignore();
    cin >> answer;
  }
  if (answer == 'y')
    return true;
  else
    return false;
}

int main ()
{
  int turn = 2; //shift variable to change turns
  int menuChoice = 1;
  bool replay = true;
  //char playAgain, playerCharacter;
  char board[ROWS][COLS] = {
     { '*', '*', '*' },
     { '*', '*', '*' },
     { '*', '*', '*' } };


  while (menuChoice != 4)
  {
    clear_the_screen(); //clears initial menu
    menuChoice = displayMenu();
    switch (menuChoice)
    {
      case 1:   while (!isBoardFull(board) || replay != false) //loops player turns until the array is full
                {
                  displayBoard(board); //displays initial board

                  if (turn % 2 == 0) //change to '== 1' if you want to change who goes first
                  {
                    cout << "Player X's turn.\n";
                    playerTurn(board, 'X', turn);
                    if (checkForWinner(board, 'X')) //check for winner
                    {
                      turn = 2; //reset turns
                      displayBoard(board);
                      cout << "Player 1 (X) wins!!\n\n";
                      resetBoard(board);
                      replay = playAgain();
                      //system( "read -n 1 -s -p \"Press any key to continue...\"" );
                    }
                    clear_the_screen(); //clears board from previous turn
                    turn++;
                  }
                  else //Player O turn
                  {
                    cout << "Player O's turn.\n";
                    playerTurn(board, 'O', turn);
                    if (checkForWinner(board, 'O')) //check for winner
                    {
                      turn = 2; //reset turns
                      displayBoard(board);
                      cout << "Player 2 (O) wins!!\n\n";
                      resetBoard(board);
                      //system( "read -n 1 -s -p \"Press any key to continue...\"" );
                    }
                    clear_the_screen(); //clears board from previous turn
                      turn++;
                  }
                  if(isBoardFull(board)) //check if tie occurs
                  {
                    cout << "Its a tie!\n";
                    resetBoard(board);
                    turn = 2;
                    menuChoice = displayMenu();
                  }
                }
                break;
      case 2:   while (!isBoardFull(board) || menuChoice != 2) //loops turns until the array is full
                {
                  displayBoard(board);

                  if (turn % 2 == 0) //change to '== 1' if you want to change who goes first
                  {
                    cout << "Player X's turn.\n";
                    playerTurn(board, 'X', turn);
                    if (checkForWinner(board, 'X'))
                    {
                      turn = 2;
                      displayBoard(board);
                      cout << "Player 1 (X) wins!!\n\n";
                      resetBoard(board);
                      system( "read -n 1 -s -p \"Press any key to continue...\"" );
                      menuChoice = displayMenu();
                    }
                    clear_the_screen();
                    turn++;
                  }
                  else  //computer's turn
                  {
                    cout << "Computer's turn.\n";
                    easyComputerTurn(board);
                    if (checkForWinner(board, 'O'))
                    {
                      turn = 2;
                      displayBoard(board);
                      cout << "Computer (O) wins!!\n\n";
                      resetBoard(board);
                      system( "read -n 1 -s -p \"Press any key to continue...\"" );
                      menuChoice = displayMenu();
                    }
                    clear_the_screen();
                      turn++;
                  }
                  if(isBoardFull(board)) //check if tie occurs
                  {
                    cout << "Its a tie!\n";
                    resetBoard(board);
                    turn = 2;
                    menuChoice = displayMenu();
                  }
                }
      case 3:   while (!isBoardFull(board) || menuChoice != 3) //loops turns until the array is full
                {
                  displayBoard(board);
                  if (turn % 2 == 0) //change to '== 1' if you want to change who goes first
                  {
                    cout << "Player X's turn.\n";
                    playerTurn(board, 'X', turn);
                    if (checkForWinner(board, 'X'))
                    {
                      turn = 2;
                      displayBoard(board);
                      cout << "Player 1 (X) wins!!\n\n";
                      resetBoard(board);
                      system( "read -n 1 -s -p \"Press any key to continue...\"" );
                      menuChoice = displayMenu();
                    }
                    clear_the_screen();
                    turn++;
                  }
                  else  //computer's turn
                  {
                    cout << "Computer's turn.\n";
                    hardComputerTurn(board);
                    if (checkForWinner(board, 'O'))
                    {
                      turn = 2;
                      displayBoard(board);
                      cout << "Computer (O) wins!!\n\n";
                      resetBoard(board);
                      system( "read -n 1 -s -p \"Press any key to continue...\"" );
                      menuChoice = displayMenu();
                    }
                    clear_the_screen();
                    turn++;
                  }
                  if(isBoardFull(board)) //check if tie occurs
                  {
                    cout << "Its a tie!\n";
                    resetBoard(board);
                    turn = 2;
                    system( "read -n 1 -s -p \"Press any key to continue...\"" );
                    menuChoice = displayMenu();
                  }
                }
      }
  }

}
