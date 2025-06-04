add_library(Parse SHARED
  Parser.cpp
        CompoundString.cpp
)

target_link_libraries(Parse PRIVATE Lex)
target_link_libraries(Parse PRIVATE c++ c++abi)
