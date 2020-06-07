cmake_minimum_required(VERSION 3.16)
project(c_programming LANGUAGES C)

set( CMAKE_C_STANDARD 99 )
set( CMAKE_BUILD_TYPE Debug )
set( CMAKE_CXX_FLAGS_DEBUG  "-g" )

add_executable( c_programming main.c config.c include/iconv.h types.h)

target_compile_definitions( c_programming PRIVATE -DPDC_DLL_BUILD )

target_include_directories( c_programming PRIVATE ${CMAKE_SOURCE_DIR}/include )

target_link_libraries( c_programming ${CMAKE_SOURCE_DIR}/lib/pdcurses.lib ${CMAKE_SOURCE_DIR}/lib/libxml2.lib ${CMAKE_SOURCE_DIR}/lib/libiconv.lib )

set_target_properties( c_programming PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS 1 )