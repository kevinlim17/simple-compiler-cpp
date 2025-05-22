#ifndef __COMPILER_TUTORIAL_LEX_TOKEN__
#define __COMPILER_TUTORIAL_LEX_TOKEN__

#include <stdint.h>

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

  bool isNot(tok::TokenKind K) { return Kind != K; }

  tok::TokenKind getKind() const { return Kind; }
  void setKind(tok::TokenKind K) { Kind = K; }
  
  const char* getLiteralData() const { return (const char*) PtrData; }
  void setLiteralData(const char *Ptr) { PtrData = const_cast<char*>(Ptr); }
  
  SourceLocation::UIntTy getLocation() const { return Loc; }
  void setLocation(unsigned L) { Loc = L; }
  
  SourceLocation::UIntTy getLength() const { return Length; }
  void setLength(unsigned L) { Length = L; }
};

#endif 
