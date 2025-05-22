#include "Parse/Parser.h"

#include <iostream>
#include <cstring>
#include <string>

bool test(const char *prog) {
  std::cout << "Test Program: " << prog << std::endl;
  
  Lexer TheLexer(prog, prog + strlen(prog));
  Parser TheParser(TheLexer);
 
  int result = true;
  auto AST = TheParser.ParseTopLevelStmt();

  if (!AST) {
    return false;
  }

  std::cout << "Parsing Result: " << std::endl;
  std::cout << AST->toString() << std::endl;

  return result;
}

int main () {
  const char *prog1 = "ADD 3, 100";
  bool result = test(prog1); 
  
  if (!result) {
    std::cout << "Parsing failed with unknown structure" << std::endl;
  }
}
