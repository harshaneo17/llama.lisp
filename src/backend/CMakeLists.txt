cmake_minimum_required(VERSION 3.19.2)
project(LLVMcodegenerator)


set(CMAKE_CXX_STANDARD 17)

find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
add_executable(main llvmgen.cpp)
target_link_libraries(main nlohmann_json::nlohmann_json ${llvm_libs} ${LLVM_LIBRARIES})
