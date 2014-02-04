var negamax = require('./negamax'),
    _;

console.log("negamax.getBestMoves(['x', _, _, 'o', _, _, 'x', _, 'o']):", negamax.getBestMoves(['x', _, _, 'o', _, _, 'x', _, 'o']));
console.log("negamax.getBestMoves([_, _, _, _, _, _, _, _, _]):", negamax.getBestMoves([_, _, _, _, _, _, _, _, _]));
