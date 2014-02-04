#include<limits.h>
#include<math.h>
#include<stdbool.h>
#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>

#define SIZE 9
#define LENGTH 3

#define REALLY_BIG_NUMBER INT_MAX

#define EMPTY 0
#define X 1
#define O 2

bool isPlayed(int value) {
  return (value == X || value == O);
}

int winner(uint8_t board[]) {
  // rows
  for (int i=0; i < SIZE; i += LENGTH) {
    if (isPlayed(board[i]) && board[i] == board[i+1] && board[i] == board[i+2]) {
      return board[i];
    }
  }

  // columns
  for (int i=0; i < LENGTH; i++) {
    if (isPlayed(board[i]) && board[i] == board[i+LENGTH] && board[i] == board[i+2*LENGTH]) {
      return board[i];
    }
  }

  // diagonals
  if (isPlayed(board[0]) && board[0] == board[4] && board[0] == board[8]) {
    return board[0];
  }

  if (isPlayed(board[2]) && board[2] == board[4] && board[2] == board[6]) {
    return board[2];
  }

  return EMPTY;
}

bool won(uint8_t board[]) {
  return winner(board) != 0;
}

bool tied(uint8_t board[]) {
  for (int i=0; i < SIZE; i++) {
    if (isPlayed(board[i])) {
      return false;
    }
  }

  if (won(board)) {
    return false;
  }

  return true;
}

bool over(uint8_t board[]) {
  return won(board) || tied(board);
}

int opponent(int player) {
  return (player == X) ? O : X;
}

int emptyCount(uint8_t board[]) {
  int emptyCount = 0;
  for (int i=0; i < SIZE; i++) {
    if (!isPlayed(board[i])) {
      emptyCount += 1;
    }
  }
  return emptyCount;
}

int turn(uint8_t board[]) {
  return (emptyCount(board) % 2 == 1) ? X : O;
}

int analysis(uint8_t board[], int depth) {
  if (won(board)) {
    return -depth;
  }

  if (tied(board)) {
    return 0;
  }

  return depth * depth;
}

int negamax_recursive(uint8_t board[], int player, int depth, int alpha, int beta) {
  int bestWeight = -REALLY_BIG_NUMBER;

  if (over(board) || depth > 6) {
    return analysis(board, depth);
  }

  for (int i=0; i < SIZE; i++) {
    if (!isPlayed(board[i])) {
      board[i] = player;
      int playResult = -negamax_recursive(board, opponent(player), depth + 1, -beta, -alpha);
      board[i] = 0;

      if (playResult > bestWeight) {
        bestWeight = playResult;
      }

      if (playResult > alpha) {
        alpha = playResult;
      }

      if (alpha >= beta) {
        return alpha;
      }
    }
  }

  return bestWeight;
}

void negamax(uint8_t board[], int8_t result[]) {
  int player = turn(board);
  int initialDepth = 1;
  for (int i=0; i < SIZE; i++) {
    if (!isPlayed(board[i])) {
      board[i] = player;
      int playResult = -negamax_recursive(board, opponent(player), initialDepth, -REALLY_BIG_NUMBER, REALLY_BIG_NUMBER);
      result[i] = playResult;
      board[i] = 0;
    }
  }
}

// 0 1 2
// 3 4 5
// 6 7 8
int main() {
  uint8_t *board = (uint8_t*)malloc(sizeof(uint8_t) * SIZE);
  int8_t *result = (int8_t*)malloc(sizeof(int8_t) * SIZE);

  /* board[0] = board[6] = X; */
  /* board[3] = board[8] = O; */

  //board[0] = X;

  negamax(board, result);

  for (int i=0; i < SIZE; i++) {
    printf("%d: %d\n", i, result[i]);
  }

  int x = INT_MAX;
  printf("x: %d\n", x);
  x = -x;
  printf("x: %d\n", x);
}
