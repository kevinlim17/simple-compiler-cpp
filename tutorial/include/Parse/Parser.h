#ifndef __COMPILER_TUTORIAL_PARSE_PARSER_H__  
#define __COMPILER_TUTORIAL_PARSE_PARSER_H__ 

#include <memory>

#include "Parse/AST.h"
#include "Lex/Token.h"

class Parser {

  // The current token we are p  
  Token Tok;

public:
  bool ParseTopLevelStmt();
  bool ParseExpr();

  bool ParseCalcStmt();
  bool ParseNumExpr();

  ConsumeToken();
};

#endif 
