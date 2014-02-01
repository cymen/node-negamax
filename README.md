# negamax
A C implementation of the negamax algorithm for a 3x3 tic-tac-toe game. It
uses an array of integers to represent the board with this convention:

0 = unplayed
1 = X
2 = O


1    |2    |3
     |     |
_____|_____|_____
4    |5    |6
     |     |              ===        [1, 2, 3, 4, 5, 6, 7, 8, 9]
_____|_____|_____
7    |8    |9
     |     |
     |     |

The function returns an array of 9 integers with the best move having the
highest value.

## build

    $ ./build.sh

## try it

    $ node
    > var negamax = require('./negamax');
    undefined
    > negamax([0, 0, 0, 0, 0, 0, 0, 0, 0]);
    [?]

or:

  node try.js
