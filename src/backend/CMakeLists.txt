cmake_minimum_required(VERSION "3.19.2")

set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/llvm")
project("LLVMcodegenerator")
set(CMAKE_CXX_STANDARD 17)
find_package(LLVM REQUIRED CONFIG)
add_executable(main "llvmgen.cpp")


