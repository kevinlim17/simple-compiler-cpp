#ifndef __COMPILER_TUTORIAL_LEX_TOKEN__
#define __COMPILER_TUTORIAL_LEX_TOKEN__

#include <stdint.h>
#include <string>

namespace tok {

enum TokenKind : unsigned short {
  add,
  sub,
  mul,
  div,
  num,
  comma,
  eof,
  unknown,
  NUM_TOKENS
};

}; //namespace tok

class SourceLocation {
public:
  using UIntTy = uint32_t;
  using IntTy = int32_t;
};

class Token {
  tok::TokenKind Kind;
  void *PtrData;
  SourceLocation::UIntTy Loc;
  SourceLocation::UIntTy Length;

public:
  /// Reset all flags to cleared.
  void startToken() {
    Kind = tok::unknown;
    PtrData = nullptr;
    Loc = 0;
    Length = 0;
  }

  bool is(tok::TokenKind K) { return Kind == K; }
  bool isNot(tok::TokenKind K) { return Kind != K; }

  tok::TokenKind getKind() const { return Kind; }
  void setKind(tok::TokenKind K) { Kind = K; }
  
  const char* getLiteralData() const { return (const char*) PtrData; }
  void setLiteralData(const char *Ptr) { PtrData = const_cast<char*>(Ptr); }
  
  SourceLocation::UIntTy getLocation() const { return Loc; }
  void setLocation(unsigned L) { Loc = L; }
  
  SourceLocation::UIntTy getLength() const { return Length; }
  void setLength(unsigned L) { Length = L; }

  std::string toString() const { 
    switch(Kind) {
    case tok::add: return "ADD";
    case tok::sub: return "SUB";
    case tok::mul: return "MUL";
    case tok::div: return "DIV";
    case tok::num: return std::string((char*)PtrData, Length);
    case tok::comma: return "COMMA"; 
    case tok::unknown: return "UNKNOWN";
    case tok::eof:
    default: return "";
    }
  }
};

#endif 
