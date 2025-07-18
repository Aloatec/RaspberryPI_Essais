﻿# CMakeList.txt : projet CMake pour ProjetSuperDur, incluez la source et définissez
# la logique spécifique au projet ici.
#

# Ajoutez une source à l'exécutable de ce projet.

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library (ProjetSuperDurDll SHARED 
    "src/ProjetSuperDurDll.cpp" 
    "include/ProjetSuperDurDll.h"
    "include/export.h")

target_include_directories(ProjetSuperDurDll PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ProjetSuperDurDll PROPERTY CXX_STANDARD 20)
endif()

if(WIN32)
    target_compile_definitions(ProjetSuperDurDll PRIVATE MYLIBRARY_EXPORTS)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.

find_package(boost_locale REQUIRED CONFIG)
target_link_libraries(ProjetSuperDurDll PRIVATE Boost::locale)


if(WIN32)

    add_custom_command(TARGET ProjetSuperDurDll POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:ProjetSuperDurApp>
    COMMAND ${CMAKE_COMMAND} -E copy 
    $<TARGET_FILE:ProjetSuperDurDll> 
    $<TARGET_FILE_DIR:ProjetSuperDurApp>
    COMMAND ${CMAKE_COMMAND} -E copy 
    $<TARGET_RUNTIME_DLLS:ProjetSuperDurDll> 
    $<TARGET_FILE_DIR:ProjetSuperDurApp>
    COMMAND_EXPAND_LISTS)

endif()

file(GLOB_RECURSE PROJ_A_SOURCES
  CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/.clang-format.stamp
  COMMAND ${CLANG_FORMAT_EXE} -i -style=Microsoft ${PROJ_A_SOURCES}
  COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_BINARY_DIR}/.clang-format.stamp
  DEPENDS ${PROJ_A_SOURCES}
  COMMENT "Clang-format Dll"
)

add_custom_target(run-clang-format-projet-super-dur-dll
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/.clang-format.stamp
)



add_custom_command(TARGET ProjetSuperDurDll POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:ProjetSuperDurApp>
    COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:ProjetSuperDurApp>/locales
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/ProjetSuperDurDll/locales
        $<TARGET_FILE_DIR:ProjetSuperDurApp>/locales
)

if(WIN32)

    add_custom_command(TARGET ProjetSuperDurDll POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:ProjetSuperDurTest>
    COMMAND ${CMAKE_COMMAND} -E copy 
    $<TARGET_FILE:ProjetSuperDurDll> 
    $<TARGET_FILE_DIR:ProjetSuperDurTest>
    COMMAND ${CMAKE_COMMAND} -E copy 
    $<TARGET_RUNTIME_DLLS:ProjetSuperDurDll> 
    $<TARGET_FILE_DIR:ProjetSuperDurTest>
    COMMAND_EXPAND_LISTS)

endif()

