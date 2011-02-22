#ifndef BT_OS_NUMBER
#define BT_OS_NUMBER

#include <string>
#include "types.hpp"

/**
 * Return a (base10) word from a hex string.
 */
word hex_to_dec(std::string hex);

// TODO:
// string dec_to_hex(word dec);
// string dec_to_hex(int dec);

#endif
