# CMakeList.txt : projet CMake pour ProjetSuperDur, incluez la source et définissez
# la logique spécifique au projet ici.
#

# Ajoutez une source à l'exécutable de ce projet.

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_executable (BoostBeast 
    "src/BoostBeast.cpp"
    "include/BoostBeast.h"
    "src/pch.h"
    "src/pch.cpp"
    "include/export.h")

target_include_directories(BoostBeast PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BoostBeast PROPERTY CXX_STANDARD 20)
endif()

if(WIN32)
    target_compile_definitions(BoostBeast PRIVATE BOOSTPYTHON_EXPORTS)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.

find_package(Boost REQUIRED COMPONENTS beast)
target_link_libraries(BoostBeast PRIVATE Boost::beast)

find_package(Boost REQUIRED COMPONENTS json)
target_link_libraries(BoostBeast PRIVATE Boost::json)

find_program(CLANG_FORMAT_EXE clang-format)

if(NOT CLANG_FORMAT_EXE)
  message(FATAL_ERROR "clang-format not found")
endif()

add_clang_format_target(boost-beast
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

