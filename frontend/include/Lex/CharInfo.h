#ifndef __COMPILER_TUTORIAL_LEX_CHAR_INFO__
#define __COMPILER_TUTORIAL_LEX_CHAR_INFO__

/// Returns true if a byte is an ASCII character.
inline bool isASCII(char c) {
  return static_cast<unsigned char>(c) <= 127;
}

inline bool isDigit(char c) {
  return (c >= '0' && c <= '9');
}

inline bool isWhitespace(char c) {
  return (c >= 9 && c <= 13) || c == ' ';
}

#endif
