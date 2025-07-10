# CMakeList.txt : projet CMake pour HelloWorldCMake, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.21)

# Activez Rechargement à chaud pour les compilateurs MSVC si cela est pris en charge.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("HelloWorldCMake")

set(VCPKG_FEATURE_FLAGS "manifests")

# Ajoutez une source à l'exécutable de ce projet.
add_library(HelloWorldLib SHARED "HelloWorld3.cpp" "HelloWorld2.h")

target_include_directories(HelloWorldLib
    PUBLIC "HelloWorld2.h"
)
option(BUILD_FMT_DLL "Build FMT as a DLL (export symbols)" ON)

 if(BUILD_FMT_DLL)
    target_compile_definitions(HelloWorldLib PRIVATE FMT_LIB_EXPORT)
else()
    target_compile_definitions(HelloWorldLib PRIVATE FMT_SHARED)
endif()


add_executable (HelloWorldCMake "HelloWorldCMake.cpp" "HelloWorldCMake.h"  "pch.h")

target_link_libraries(HelloWorldCMake PRIVATE HelloWorldLib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET HelloWorldCMake PROPERTY CXX_STANDARD 20)
endif()

find_package(plog CONFIG REQUIRED)
target_link_libraries(HelloWorldCMake PRIVATE plog::plog)


# TODO: Ajoutez des tests et installez des cibles si nécessaire.

find_package(Boost REQUIRED COMPONENTS unit_test_framework)
add_executable(tests 
	tests/main.cpp
	tests/hello_world_test.cpp)
target_link_libraries(tests PRIVATE Boost::unit_test_framework)

target_precompile_headers(HelloWorldCMake PRIVATE pch.h)

enable_testing()

include(CTest)

set_property(TARGET tests PROPERTY FOLDER "tests")
set_property(TARGET tests PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

add_test(NAME boost_unit_tests COMMAND tests --catch_system_errors=yes --log_level=all)
