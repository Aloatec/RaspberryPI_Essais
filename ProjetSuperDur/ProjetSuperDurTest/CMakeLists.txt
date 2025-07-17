# CMakeList.txt : projet CMake pour ProjetSuperDur, incluez la source et définissez
# la logique spécifique au projet ici.
#

# Ajoutez une source à l'exécutable de ce projet.

set(CMAKE_POSITION_INDEPENDENT_CODE ON)


add_executable (ProjetSuperDurTest
    "src/main.cpp" 
    "src/unitary_test.cpp" "src/unitary_test_2.cpp")

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

add_test(NAME MesTests 
        COMMAND ProjetSuperDurTest --log_level=all --report_level=detailed)

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
  COMMENT "Clang-format test"
)

add_custom_target(run-clang-format-projet-super-dur-test
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/.clang-format.stamp
)


