# negamax
A C implementation of the negamax algorithm for a 3x3 tic-tac-toe game. It
uses an array of integers to represent the board with this convention:

    0 = unplayed
    1 = X
    2 = O


    0    |1    |2
         |     |
    _____|_____|_____
    3    |4    |5
         |     |              ===        [0, 1, 2, 3, 4, 5, 6, 7, 8]
    _____|_____|_____
    6    |7    |8
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
    > negamax.getBestMoves([_, _, _, _, _, _, _, _, _]);
    [ 0, 2, 4, 6, 8 ]

or:

    node try.js
    negamax.getBestMoves(['x', _, _, 'o', _, _, 'x', _, 'o']): [ 2 ]
    negamax.getBestMoves([_, _, _, _, _, _, _, _, _]): [ 0, 2, 4, 6, 8 ]
