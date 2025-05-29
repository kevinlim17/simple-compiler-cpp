# Compiler Implementation Tutorial

This tutorial helps you to get hands-on experiences in designing a toy compiler. 


## Source Language

This tutorial assumes a simple calculator language whose program consists of a sequence of statements.

```
ADD 2, 3
SUB 3
MUL 10
PRINT
```

The language has two types of statements: arithmetic statement and printing statement. The arithmetic statement performs the corresponding claculation with the given operands and updates an internal accumulator. For the arithmetic statement, it supports four arithmetic operators:`ADD`, `SUB`, `MUL`, `DIV`). The first arithmetic statement must take two operands and the following ones must take one operand. The printing statement takes no operand and prints out the accumulator value. 

Currently, the compiler can handle a single arithmatic statement only. The goal of this tutorial is to **extend the current compiler implementation** for the full language support.

## Tasks

### Lexer

You will first extend the lexer to handle the `PRINT` token.

- Modify `include/Lex/Token.h` to add a new token.
- Modify `lib/Lex/Lexer.cpp` to handle the `PRINT` token.

You may change any other files if you need.

### Parser

You will extend the parser to handle compound and printing statements.

- Modify `include/Parse/AST.h` to declare new AST nodes for compound and printing statmenets.
- Modify `include/Parse/Parser.h` to declare new functions to handle compound and printing statements.
- Modify `lib/Parse/Parser.cpp' to implement the new functions. 

### CodeGen

You will extend the code generator to handle compound and printing statements.

- Modify `include/CodeGen/CodeGenFunction.h` to declare new functions to emit code for compound and printing statements.
- Modify `include/CodeGen/CodeGenFunction.cpp` to implement the new functions.

