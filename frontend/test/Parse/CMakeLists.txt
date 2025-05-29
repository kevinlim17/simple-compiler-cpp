add_executable(TestParser
  TestParser.cpp
)

target_link_libraries(TestParser PRIVATE Lex Parse)
