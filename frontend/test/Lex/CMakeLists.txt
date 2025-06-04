add_executable(TestLexer
  TestLexer.cpp
)

target_link_libraries(TestLexer PRIVATE Lex)
target_link_libraries(TestLexer PRIVATE c++ c++abi)