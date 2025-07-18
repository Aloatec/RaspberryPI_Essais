# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.21)

# Activez Rechargement à chaud pour les compilateurs MSVC si cela est pris en charge.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

find_program(CLANG_FORMAT_EXE NAMES clang-format)

project ("ProjetSuperDur")
set(VCPKG_FEATURE_FLAGS "manifests")

add_compile_definitions()

if(MSVC)
    add_compile_options(/EHsc)
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=modernize-*,bugprone-*, cppcoreguidelines-*, boost-*, portability-*, readability-*, concurrency-*, performance-*, -modernize-use-trailing-return-type;-warnings-as-errors=*;-extra-arg=-Qunused-arguments;-extra-arg=/EHsc;-header-filter=^(?!.*vcpkg_installed).*$")
else()
    add_compile_options(-fexceptions)
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=modernize-*,bugprone-*, cppcoreguidelines-*, boost-*, portability-*, readability-*, concurrency-*, performance-*, -modernize-use-trailing-return-type;-warnings-as-errors=*;-extra-arg=-Qunused-arguments;-extra-arg=-fexceptions;-header-filter=^(?!.*vcpkg_installed).*$")
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


# Cible globale pour lancer tous les formats
add_custom_target(run-clang-format-all
  DEPENDS run-clang-format-boost-python 
          run-clang-format-projet-super-dur-dll
          run-clang-format-projet-super-dur-app
          run-clang-format-projet-super-dur-test
)



set_property(TARGET ProjetSuperDurTest PROPERTY FOLDER " ${CMAKE_SOURCE_DIR}/ProjetSuperDurTest/src")
set_property(TARGET ProjetSuperDurTest PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")


#set(CPPCHECK_DIRS
#    ${CMAKE_SOURCE_DIR}/ProjetSuperDurDll
#    ${CMAKE_SOURCE_DIR}/ProjetSuperDurApp
#    ${CMAKE_SOURCE_DIR}/ProjetSuperDurTest
#    ${CMAKE_SOURCE_DIR}/BoostPython
#    ${CMAKE_SOURCE_DIR}/BoostApplication
#)
#
#
## Création de la cible "run-cppcheck"
#add_custom_target(run-cppcheck ALL
#    COMMAND cppcheck
#        --enable=style
#        --inconclusive
#        --std=c++20
#        --force
#        --suppress=missingInclude
#        --suppress=missingIncludeSystem
#        --quiet
#        ${CPPCHECK_DIRS}
#    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
#    COMMENT "Analyse statique avec cppcheck sur tous les sous-projets"
#)
