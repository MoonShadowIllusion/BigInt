set(Catch2_DIR ${PROJECT_SOURCE_DIR}/Catch2)
include_directories(${PROJECT_SOURCE_DIR} ${Catch2_DIR}/)

add_library(catch2 SHARED
        ${Catch2_DIR}/catch_amalgamated.cpp
        ${Catch2_DIR}/catch_amalgamated.hpp)
link_libraries(catch2)
include(${PROJECT_SOURCE_DIR}/Catch2/extras/Catch.cmake)
aux_source_directory(${PROJECT_SOURCE_DIR}/Test TestSrc)

#添加Test下所有.cpp 为 可执行target
set(all_test_file)
foreach (I ${TestSrc})
    string(APPEND all_test_file "#include \"${I}\"\n")
    string(REGEX REPLACE "^${CMAKE_CURRENT_SOURCE_DIR}/" "" filename ${I})
    string(REGEX REPLACE ".cpp$" "" filename ${filename})
    add_executable(${filename} ${I})
    catch_discover_tests(${filename})
endforeach ()

#添加所有的Catch2单元测试
file(WRITE ${PROJECT_BINARY_DIR}/AllCatch2TestUnit.cpp ${all_test_file})
add_executable(AllCatch2TestUnit ${PROJECT_BINARY_DIR}/AllCatch2TestUnit.cpp)