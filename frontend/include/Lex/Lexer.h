#ifndef __COMPILER_TUTORIAL_LEX_LEXER__
#define __COMPILER_TUTORIAL_LEX_LEXER__

#include "Lex/Token.h"

class Lexer {
  // Start of the buffer. 
  const char *BufferStart;
  
  // Current pointer into the buffer
  const char *BufferPtr;
 
  // End of the buffer. 
  const char *BufferEnd;

public:
  // Constructor
  Lexer(const char *BufferStart, const char *BufferEnd);

  // Return the next token in the file
  bool Lex(Token &Result);

  // Read a single 'character' from the specified buffer
  char getAndAdvanceChar(const char *&Ptr) {
    return *Ptr++;
  }

  char getChar(const char *Ptr) {
    return *Ptr;
  }

  // Form the token towards TokEnd
  void FormTokenWithChars(Token &Result, const char *TokEnd,
                          tok::TokenKind Kind) {
    unsigned TokLen = TokEnd - BufferPtr;
    Result.setLength(TokLen);
    Result.setLocation(BufferPtr - BufferStart);
    Result.setKind(Kind);
    BufferPtr = TokEnd;
  }
 
  // Helper functions to lex the remainder of a token of the specific type
  bool LexEndOfFile          (Token &Result, const char *CurPtr);
  bool LexNumericConstant    (Token &Result, const char *CurPtr);
};
#endif 
