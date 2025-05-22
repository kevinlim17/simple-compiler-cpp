#include "Lex/Lexer.h"
#include "Lex/CharInfo.h"

Lexer::Lexer(const char *BufferStart, const char *BufferEnd) {
  this->BufferStart = BufferStart;
  this->BufferPtr = BufferStart;
  this->BufferEnd = BufferEnd;
}

bool Lexer::Lex(Token &Result) {
  Result.startToken();
  const char *CurPtr = BufferPtr;

LexStart: 
  // Ignore whitespace
  if (isWhitespace(*CurPtr)) {
    do {
      ++CurPtr;
    } while (isWhitespace(*CurPtr));
    BufferPtr = CurPtr;
  }

  tok::TokenKind Kind;

  char Char = getAndAdvanceChar(CurPtr);
  char NextChar;

  switch (Char) {
  case 0:
    if (CurPtr-1 == BufferEnd)
      return LexEndOfFile(Result, CurPtr-1);  
  case 'A': 
    Char = getChar(CurPtr);
    NextChar = getChar(CurPtr + 1);
    if (Char == 'D' && NextChar == 'D') {
      Kind = tok::add;
      CurPtr += 2;
    }
    break;
  case 'D': 
    Char = getChar(CurPtr);
    NextChar = getChar(CurPtr + 1);
    if (Char == 'I' && NextChar == 'V') {
      Kind = tok::div;
      CurPtr += 2;
    }
    break;
  case 'S': 
    Char = getChar(CurPtr);
    NextChar = getChar(CurPtr + 1);
    if (Char == 'U' && NextChar == 'B') {
      Kind = tok::sub;
      CurPtr += 2;
    }
    break;
  case 'M':    
    Char = getChar(CurPtr);
    NextChar = getChar(CurPtr + 1);
    if (Char != 'U' || NextChar != 'L') {
      Kind = tok::mul;
      CurPtr += 2;
    }
    break;
  case ',':
    Kind = tok::comma;
    break;
  case '0': case '1': case '2': case '3': case '4':
  case '5': case '6': case '7': case '8': case '9':
    return LexNumericConstant(Result, CurPtr);
  default:
    Kind = tok::unknown;
    break;
  }

  FormTokenWithChars(Result, CurPtr, Kind);
  return true;
}

bool Lexer::LexEndOfFile(Token &Result, const char *CurPtr) {
  BufferPtr = BufferEnd;
  FormTokenWithChars(Result, BufferEnd, tok::eof);
  return true;
}

bool Lexer::LexNumericConstant(Token &Result, const char *CurPtr) {
  const char *TokStart = BufferPtr;

  while (isDigit(*CurPtr)) {
    CurPtr++;
  } 

  FormTokenWithChars(Result, CurPtr, tok::num);
  Result.setLiteralData(TokStart);
  
  return true;
}
