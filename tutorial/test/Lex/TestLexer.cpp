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
    std::cout << CurTok.toString();
    if (CurTok.is(tok::eof)) {
      break;
    } else if(CurTok.is(tok::unknown)) {
      result = false;
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
