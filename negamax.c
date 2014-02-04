#include<limits.h>
#include<math.h>
#include<stdint.h>
#include<stdlib.h>

#define SIZE 9
#define LENGTH 3

#define REALLY_BIG_NUMBER INT_MAX

#define EMPTY 0
#define X 1
#define O 2

char* playerAsChar(int player) {
    if (player == X) {
      return "x";
    }
    if (player == O) {
      return "o";
    }

    return "_";
}

int isPlayed(int value) {
  if (value == X || value == O) {
    return 1;
  } else {
    return 0;
  }
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

  return 0;
}

int tied(uint8_t board[]) {
  for (int i=0; i < SIZE; i++) {
    if (isPlayed(board[i]) == 0) {
      return 0;
    }
  }

  if (winner(board)) {
    return 0;
  }

  return 1;
}

int over(uint8_t board[]) {
  if (winner(board) != 0) {
    return 1;
  }

  if (tied(board) == 1) {
    return 1;
  }

  return 0;
}

int opponent(int player) {
  return (player == X) ? O : X;
}

int emptyCount(uint8_t board[]) {
  int emptyCount = 0;
  for (int i=0; i < SIZE; i++) {
    if (isPlayed(board[i]) == 0) {
      emptyCount += 1;
    }
  }
  return emptyCount;
}

int turn(uint8_t board[]) {
  return (emptyCount(board) % 2 == 1) ? X : O;
}

int analysis(uint8_t board[], int depth) {
  if (winner(board)) {
    return -depth;
  }

  if (tied(board)) {
    return 0;
  }

  return REALLY_BIG_NUMBER;
}

int negamax_recursive(uint8_t board[], int player, int depth, int alpha, int beta) {
  int bestWeight = -1 * REALLY_BIG_NUMBER;

  if (over(board) == 1 || depth > 6) {
    return analysis(board, depth);
  }

  for (int i=0; i < SIZE; i++) {
    if (isPlayed(board[i] == 0)) {
      board[i] = player;
      int playResult = -1 * negamax_recursive(board, opponent(player), depth+1, -beta, -alpha);
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
  if (emptyCount(board) == SIZE) {
    result[0] = result[2] = result[4] = result[6] = result[8] = SIZE;
  } else {
    int player = turn(board);
    int initialDepth = 1;
    for (int i=0; i < SIZE; i++) {
      if (isPlayed(board[i] == 0)) {
        board[i] = player;
        int playResult = -1 * negamax_recursive(board, opponent(player), initialDepth, -REALLY_BIG_NUMBER, REALLY_BIG_NUMBER);
        result[i] = playResult;
        board[i] = 0;
      }
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
    /* printf("%d: %d\n", i, result[i]); */
  }
}
