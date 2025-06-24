# CMakeList.txt : projet CMake pour HelloWorldCMake, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

# Activez Rechargement à chaud pour les compilateurs MSVC si cela est pris en charge.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("HelloWorldCMake")

set(VCPKG_FEATURE_FLAGS "manifests")

# Ajoutez une source à l'exécutable de ce projet.
add_executable (HelloWorldCMake "HelloWorldCMake.cpp" "HelloWorldCMake.h" "HelloWorld3.cpp" "HelloWorld2.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET HelloWorldCMake PROPERTY CXX_STANDARD 20)
endif()

find_package(plog CONFIG REQUIRED)
target_link_libraries(HelloWorldCMake PRIVATE plog::plog)


# TODO: Ajoutez des tests et installez des cibles si nécessaire.

find_package(Catch2 CONFIG REQUIRED)
add_executable(tests HelloWorld_test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(tests)
