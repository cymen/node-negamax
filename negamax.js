var Module = require('./module'),
    negamax,
    getBestMoves;

negamax = function(board) {
    var dataValues,
        data,
        dataHeap,
        dataPtr,
        dataSize,
        fn,
        i,
        result,
        resultHeap,
        resultPtr,
        resultSize;

    fn = Module.cwrap('negamax', 'undefined', ['number', 'number']);

    // translate ['x', 'o', ... ] --> [1, 2, ... ]
    dataValues = [];
    board.map(function(value) {
        if (value === 'x') {
          dataValues.push(1);
        } else if (value === 'o') {
          dataValues.push(2);
        } else {
          dataValues.push(0);
        }
    });
    data = new Uint8Array(dataValues);
    result = new Int8Array([0, 0, 0, 0, 0, 0, 0, 0, 0]);

    dataSize = data.length * data.BYTES_PER_ELEMENT;
    resultSize = result.length * result.BYTES_PER_ELEMENT;

    dataPtr = Module._malloc(dataSize);
    resultPtr = Module._malloc(resultSize);

    dataHeap = new Uint8Array(Module.HEAPU8.buffer, dataPtr, dataSize);
    dataHeap.set(data);

    resultHeap = new Int8Array(Module.HEAPU8.buffer, resultPtr, resultSize);
    resultHeap.set(result);

    fn(dataHeap.byteOffset, resultHeap.byteOffset);

    result = [];
    for (i = 0; i < resultSize; i++) {
      result.push(resultHeap.get(i));
    }

    Module._free(dataHeap.byteOffset);
    Module._free(resultHeap.byteOffset);

    return result;
};

getBestMoves = function(board) {
  var bestMoves = [],
      maxWeight = -Infinity,
      moveWeights;

  moveWeights = negamax(board);
  moveWeights.map(function(weight) {
    if (weight > maxWeight) {
      maxWeight = weight;
    }
  });

  moveWeights.map(function(weight, index) {
    if (weight == maxWeight) {
      bestMoves.push(index);
    }
  });

  return bestMoves;
};

module.exports = {
  negamax: negamax,
  getBestMoves: getBestMoves
};
