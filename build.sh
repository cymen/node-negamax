emcc negamax.c -o module.js -s EXPORTED_FUNCTIONS="['_negamax']" && echo "" >> module.js && echo "module.exports = Module;" >> module.js
