# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.21)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

include(CLangFormat)
include(CopyFolder)

#set(CMAKE_BINARY_DIR "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/bin")

# Activez Rechargement à chaud pour les compilateurs MSVC si cela est pris en charge.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

find_program(CLANG_FORMAT_EXE NAMES clang-format)

project ("ProjetSuperDur")
set(VCPKG_FEATURE_FLAGS "manifests")

add_compile_definitions()

set(CLANG_TIDY_CHECKS
    "-checks=modernize-*,bugprone-*,cppcoreguidelines-*,boost-*,portability-*,readability-*,concurrency-*,performance-*,-modernize-use-trailing-return-type,-clang-analyzer-cplusplus.NewDelete,-bugprone-exception-escape"
)
set(CLANG_TIDY_HEADER_FILTER "-header-filter=^(?!.*vcpkg_installed).*$")
set(CLANG_TIDY_COMMON_ARGS "-extra-arg=-Qunused-arguments;-warnings-as-errors=*")

if(MSVC)
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;${CLANG_TIDY_CHECKS};${CLANG_TIDY_COMMON_ARGS};-extra-arg=/EHsc;${CLANG_TIDY_HEADER_FILTER}")
else()
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;${CLANG_TIDY_CHECKS};${CLANG_TIDY_COMMON_ARGS};-extra-arg=-fexceptions;${CLANG_TIDY_HEADER_FILTER}")
endif()

if(CMAKE_CXX_CLANG_TIDY AND UNIX)
  message(STATUS "Désactivation des PCH sur Unix quand Clang-Tidy est actif")
  set(CMAKE_DISABLE_PRECOMPILE_HEADERS ON)
endif()

enable_testing()

# Incluez les sous-projets.
add_subdirectory ("ProjetSuperDurTest")
add_subdirectory ("ProjetSuperDurApp")
add_subdirectory ("ProjetSuperDurDll")
add_subdirectory ("BoostPython")
add_subdirectory("BoostBeast")


# Cible globale pour lancer tous les formats
add_custom_target(run-clang-format-all
  DEPENDS run-clang-format-boost-python 
          run-clang-format-projet-super-dur-dll
          run-clang-format-projet-super-dur-app
          run-clang-format-projet-super-dur-test
          run-clang-format-boost-beast
)

add_dependencies(ProjetSuperDurApp run-clang-format-all)
add_dependencies(ProjetSuperDurTest run-clang-format-all)
add_dependencies(ProjetSuperDurDll run-clang-format-all)
add_dependencies(BoostPython run-clang-format-all)
add_dependencies(BoostBeast run-clang-format-all)

set_property(TARGET ProjetSuperDurTest PROPERTY FOLDER "${CMAKE_SOURCE_DIR}/ProjetSuperDurTest/src")
set_property(TARGET ProjetSuperDurTest PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
