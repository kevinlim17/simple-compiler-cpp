#include "Lex/Lexer.h"

#include <iostream>
#include <cstring>
#include <string>

bool test(const char *prog) {
  std::cout << "Test Program: " << prog << std::endl;
  Lexer TheLexer(prog, prog + strlen(prog));
  
  int result = true;
   
  Token CurTok;
  TheLexer.Lex(CurTok);

  std::cout << "Lexing Result: " << std::endl;
  while(true) {
    switch(CurTok.getKind()) {
    case tok::eof:
      std::cout << std::endl;
      return result;
    case tok::add:
      std::cout << "ADD";
      break;
    case tok::sub:
      std::cout << "SUB";
      break;
    case tok::mul:
      std::cout << "MUL";
      break;
    case tok::div:
      std::cout << "DIV";
      break;
    case tok::num: {
      auto *Ptr = CurTok.getLiteralData();
      auto Len = CurTok.getLength();
      std::cout << "NUM(" << std::string(Ptr, Len) << ")";
      break;
    }
    case tok::comma:
      std::cout << "COMMA";
      break;
    case tok::unknown:
      std::cout << "UNKNOWN";
      result = false;
      break;
    default:
      break;
    }
    TheLexer.Lex(CurTok);
    std::cout << " ";
  }

  std::cout << std::endl;
  return result;
}

int main () {
  const char *prog1 = "ADD 3, 100";
  bool result = test(prog1); 
  
  if (!result) {
    std::cout << "Lexing failed with unknown token(s)" << std::endl;
  }
}
