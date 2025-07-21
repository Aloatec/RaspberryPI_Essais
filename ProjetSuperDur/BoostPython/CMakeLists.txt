# CMakeList.txt : projet CMake pour ProjetSuperDur, incluez la source et définissez
# la logique spécifique au projet ici.
#

# Ajoutez une source à l'exécutable de ce projet.

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library (BoostPython SHARED 
    "src/BoostPython.cpp" 
    "src/pch.h"
    "src/pch.cpp"
    "include/BoostPython.h"
    "include/export.h")

target_include_directories(BoostPython PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BoostPython PROPERTY CXX_STANDARD 20)
endif()

if(WIN32)
    target_compile_definitions(BoostPython PRIVATE BOOSTPYTHON_EXPORTS)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
find_package(boost_python REQUIRED CONFIG COMPONENTS python311)

target_include_directories(BoostPython PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(BoostPython PRIVATE Boost::python Python3::Python)


find_program(CLANG_FORMAT_EXE clang-format)

if(NOT CLANG_FORMAT_EXE)
  message(FATAL_ERROR "clang-format not found")
endif()

add_clang_format_target(boost-python
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

post_build_copy(BoostPython 
                ProjetSuperDurApp 
                ${CMAKE_CURRENT_SOURCE_DIR}/scripts 
                scripts)
