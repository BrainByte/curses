cmake_minimum_required(VERSION 3.16)
project(c_programming LANGUAGES C)

set( CMAKE_C_STANDARD 99 )
set( CMAKE_BUILD_TYPE Debug )
set( CMAKE_CXX_FLAGS_DEBUG  "-g" )

if (UNIX)
    set( CMAKE_IGNORE_PATH ${CMAKE_SOURCE_DIR}/win )

    find_package( Curses REQUIRED )
    find_package( LibXml2 REQUIRED )

    include_directories( ${CURSES_INCLUDE_DIR} )
    include_directories( ${LIBXML2_INCLUDE_DIR} )
endif (UNIX)

if (WIN32)
    include_directories( ${CMAKE_SOURCE_DIR}/win )
    add_executable( c_programming main.c config.c win/iconv.h types.h)
    target_compile_definitions( c_programming PRIVATE -DPDC_DLL_BUILD )
    target_include_directories( c_programming PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/win )
endif (WIN32)

if (UNIX)
    add_executable( c_programming main.c config.c types.h )
    target_include_directories( c_programming PRIVATE ${CMAKE_SOURCE_DIR}/include )
endif (UNIX)

if (UNIX)
    message( "CURSES_LIBRARIES variable: ${CURSES_LIBRARIES}")
    target_link_libraries( c_programming ${CURSES_LIBRARIES} ${LIBXML2_LIBRARIES} )
endif (UNIX)

if (WIN32)
    target_link_libraries( c_programming ${CMAKE_SOURCE_DIR}/lib/pdcurses.lib ${CMAKE_SOURCE_DIR}/lib/libxml2.lib ${CMAKE_SOURCE_DIR}/lib/libiconv.lib )
    set_target_properties( c_programming PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS 1 )
    configure_file( ${CMAKE_SOURCE_DIR}/bin/pdcurses.dll ${CMAKE_BINARY_DIR} COPYONLY)
    configure_file( ${CMAKE_SOURCE_DIR}/bin/libxml2.dll ${CMAKE_BINARY_DIR} COPYONLY)
    configure_file( ${CMAKE_SOURCE_DIR}/bin/SDL2d.dll ${CMAKE_BINARY_DIR} COPYONLY)
    configure_file( ${CMAKE_SOURCE_DIR}/bin/iconv.dll ${CMAKE_BINARY_DIR} COPYONLY)
    configure_file( ${CMAKE_SOURCE_DIR}/bin/zlib1.dll ${CMAKE_BINARY_DIR} COPYONLY)
endif (WIN32)
