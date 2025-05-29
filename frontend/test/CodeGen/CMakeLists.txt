add_executable(TestCodeGen
  TestCodeGen.cpp
)

target_link_libraries(TestCodeGen PRIVATE Lex Parse CodeGen)
