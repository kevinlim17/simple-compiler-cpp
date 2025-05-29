#include "Lex/Lexer.h"
#include "Parse/Parser.h"
#include "CodeGen/CodeGenModule.h"

#include <iostream>
#include <cstring>
#include <string>

void test(const char *prog) {
  std::cout << "Test Program: " << prog << std::endl;

  Lexer TheLexer(prog, prog + strlen(prog));
  Parser TheParser(TheLexer);
 
  auto AST = TheParser.ParseTopLevelStmt();

  llvm::LLVMContext Context;
  llvm::Module M("test", Context);

  CodeGenModule CGM(M);
  CGM.EmitTopLevelStmt(AST.get());

  std::cout << "CodeGen Result: " << std::endl;
  CGM.PrintModule();
}

int main () {
  const char *prog1 = "ADD 3, 100";
  test(prog1);  
}
