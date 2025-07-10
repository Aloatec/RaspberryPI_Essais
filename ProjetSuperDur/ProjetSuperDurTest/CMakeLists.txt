# CMakeList.txt : projet CMake pour ProjetSuperDur, incluez la source et définissez
# la logique spécifique au projet ici.
#

# Ajoutez une source à l'exécutable de ce projet.

set(CMAKE_POSITION_INDEPENDENT_CODE ON)


add_executable (ProjetSuperDurTest
    "src/main.cpp" 
    "src/unitary_test.cpp" "src/unitary_test_2.cpp" "src/pch.cpp" "src/pch.h")

target_precompile_headers(ProjetSuperDurTest PRIVATE src/pch.h)

target_include_directories(ProjetSuperDurTest PRIVATE
    ${CMAKE_SOURCE_DIR}/ProjetSuperDurDll/include
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ProjetSuperDurTest PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(ProjetSuperDurTest PRIVATE ProjetSuperDurDll)

if(WIN32)
    add_custom_command(TARGET ProjetSuperDurTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:ProjetSuperDurDll>
        $<TARGET_FILE_DIR:ProjetSuperDurTest>)
endif()

find_package(Boost REQUIRED COMPONENTS unit_test_framework)
target_link_libraries(ProjetSuperDurTest PRIVATE Boost::unit_test_framework)

enable_testing()


include(CTest)

set_property(TARGET ProjetSuperDurTest PROPERTY FOLDER " ${CMAKE_SOURCE_DIR}/ProjetSuperDurTest/src")
set_property(TARGET ProjetSuperDurTest PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

