
add_library(CodeGen SHARED
  CodeGenModule.cpp
  CodeGenFunction.cpp
)

target_link_options(CodeGen PRIVATE -flto -fuse-ld=lld)
target_link_libraries(CodeGen
  PRIVATE
    LLVMCore
    LLVMRemarks
    LLVMBitstreamReader
    LLVMBinaryFormat
    LLVMTargetParser
    LLVMSupport
    LLVMDemangle
    c++
)

