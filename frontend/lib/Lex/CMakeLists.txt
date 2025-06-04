add_library(Lex SHARED
  Lexer.cpp
)

target_link_libraries(Lex PRIVATE c++ c++abi)
