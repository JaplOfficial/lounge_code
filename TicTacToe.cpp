#include<bits/stdc++.h>
using namespace std;

int X, Y; // AI optimal coordinates

#define infinity 100

char Game_Over (char board[3][3]) { // check if game state reached an end

  bool ended = false;
  bool diagonal1 = (board[0][0] == board[1][1]) && (board[1][1] == board[2][2]);
  bool diagonal2 = (board[2][0] == board[1][1]) && (board[1][1] == board[0][2]);
  bool board_full = true;

  char state = 'W'; // W - Pending game , P - Player won , A - AI won, T - It's a tie

  if ( (diagonal1 || diagonal2) && board[1][1] != ' ') { // if one of the diagonals is completed the game is over
    if (board[1][1] == 'X') {
      state = 'A';
    } else {
      state = 'P';
    }
    ended = true;
  }

  for (int i = 0 ; i < 3 ; i++) {
     for(int j = 0 ; j < 3 ; j++) {
        if (board[i][j] == ' ') {
          board_full = false;
        }
        if (i == 0) {
          // if the current column is completed the game is over
          bool equal = (board[i][j] == board[i + 1][j]) && (board[i + 1][j] == board[i + 2][j]) && board[i][j] != ' ';
          if (equal) {
            if (board[i][j] == 'X') {
              state = 'A';
            } else {
              state = 'P';
            }
            ended = true;
          }
        }
        if (j == 0) {
          // if the current line is completed the game is over
          bool equal = (board[i][j] == board[i][j + 1]) && (board[i][j + 1] == board[i][j + 2]) && board[i][j] != ' ';
          if (equal) {
            if (board[i][j] == 'X') {
              state = 'A';
            } else {
              state = 'P';
            }
            ended = true;
          }
        }
      }
   }
   // return true if any column / row / diagonal is completed
   if (board_full && state == 'W') { // if no one won and board is full
     state = 'T';                    // results in a tie
   }
   return state; // return the state of the game
}


void Display_Board (char board[3][3]) {
  cout << "-------" << endl;
  for (int i = 0 ; i < 3 ; i++) {
    for (int j = 0 ; j < 3 ; j++) {
      if (j == 0) {
        cout << "|";
      }
      cout << board[i][j] << "|";
    }
    cout << endl;
  }
  cout << "-------" << endl;
  cout << endl << endl << endl;
}

int Minimax (char board[3][3], int current_player) {
    char winner = Game_Over(board);
    if (winner == 'A') { // AI won this board state
      return 1;
    } else if (winner == 'P'){ // Player won this board state
      return -1;
    } else if (winner == 'T') { // This board state is a tie
      return 0;
    }
    if (current_player) { // Maximizing player turn
      int bestScore = -infinity;
      for (int i = 0 ; i < 3 ; i++) {
        for (int j = 0 ; j < 3 ; j++) {
          if (board[i][j] == ' ') {
            board[i][j] = 'X'; // change board state
            int score = Minimax(board, 1 - current_player); // recall minimax switching turns
            board[i][j] = ' ';
            bestScore = max(bestScore, score);
          }
        }
      }
      return bestScore;
    } else { // Minimizing player turn
      int bestScore = infinity;
      for (int i = 0 ; i < 3 ; i++) {
        for (int j = 0 ; j < 3 ; j++) {
          if (board[i][j] == ' ') {
            board[i][j] = 'O';  // change board state
            int score = Minimax(board, 1 - current_player); // recall minimax switching turns
            board[i][j] = ' ';
            bestScore = min(bestScore, score);
          }
        }
      }
      return bestScore;
    }
}

int main(){

  cout << endl << "Welcome to the Japl's Lounge Tic-Tac-Toe AI" << endl << endl;

  char board[3][3]; // 3x3 tic tac toe board

  // Initialize board values as empty chars
  for (int i = 0 ; i < 3 ; i++) {
    for (int j = 0 ; j < 3 ; j++) {
      board[i][j] = ' ';
    }
  }

  srand(time(NULL));
  int current_player = rand() % 2;  // Randomly pick who starts the game
                                    // 1 - The AI starts , 0 - The player starts
  while (Game_Over(board) == 'W') {
    if (current_player) { // AI's turn
      cout << "It's the AI's turn !" << endl;
      int bestMove = -infinity;
      for (int i = 0 ; i < 3 ; i++) {
        for (int j = 0 ; j < 3 ; j++) {
          if (board[i][j] == ' ') {
            board[i][j] = 'X';
            int score = Minimax(board, 1-current_player);
            board[i][j] = ' ';
            if (score > bestMove) {
              bestMove = score;
              X = j , Y = i;
            }
          }
        }
      }
      board[Y][X] = 'X'; // AI's optimal play board update
    } else { // Player's turn
      int line, column;
      cout << "It's the player's turn !" << endl;
      do {
        cout << "Introduce line : ";
        cin >> line;
        cout << "Introduce column : ";
        cin >> column;
        line--, column--;
      } while(board[line][column] != ' ');
      board[line][column] = 'O'; // Players's play board update
    }
    Display_Board(board); // Print board state at every turn
    current_player = 1 - current_player; // swaps turns
  }


  return 0;
}
