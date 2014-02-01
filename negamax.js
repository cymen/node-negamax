var Module = require('./module');

module.exports = function(array) {
    var data,
        dataHeap,
        dataPtr,
        fn,
        i,
        size;

    fn = Module.cwrap('negamax', 'undefined', ['number', 'number']);

    data = new Uint8Array(array);
    size = data.length * data.BYTES_PER_ELEMENT;

    dataPtr = Module._malloc(size);

    dataHeap = new Uint8Array(Module.HEAPU8.buffer, dataPtr, size);
    dataHeap.set(data);

    fn(dataHeap.byteOffset, data.length);

    result = [];
    for (i = 0; i < size; i++) {
      result.push(dataHeap.get(i));
    }

    Module._free(dataHeap.byteOffset);

    return result;
};
