project(cpvg LANGUAGES C CXX)

set(PROJECT_VERSION 1.0)
set(PROJECT_DESCRIPTION "cpvg - C/C++ buffered block stdio file copy function
using FTXUI gauge/progress for terminal screen status output")

include(GNUInstallDirs)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-march=native -O3)
add_compile_options(-D_FILE_OFFSET_BITS=64)
add_compile_options(-fdata-sections)
add_compile_options(-ffunction-sections)
add_compile_options(-Wall)
add_compile_options(-Wextra)
add_compile_options(-Wpedantic)
add_link_options(-Wl,--gc-sections)
#add_link_options(-Wl,--print-gc-sections)
add_link_options(-Wl,-s)

add_executable(${PROJECT_NAME} ${PROJECT_NAME}_ftxui.cpp ${PROJECT_NAME}.c)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC -lftxui-component -lftxui-dom  -lftxui-screen)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
