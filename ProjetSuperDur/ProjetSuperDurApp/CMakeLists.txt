# CMakeList.txt : projet CMake pour ProjetSuperDur, incluez la source et définissez
# la logique spécifique au projet ici.
#

# Ajoutez une source à l'exécutable de ce projet.
add_executable (ProjetSuperDurApp "src/ProjetSuperDur.cpp" "src/ProjetSuperDur.h")

add_dependencies(ProjetSuperDurApp ProjetSuperDurDll)
add_dependencies(ProjetSuperDurApp BoostPython)

# Ajoute l'inclusion des headers de la DLL
target_include_directories(ProjetSuperDurApp PRIVATE
    ${CMAKE_SOURCE_DIR}/ProjetSuperDurDll/include
)

target_include_directories(ProjetSuperDurApp PRIVATE
    ${CMAKE_SOURCE_DIR}/BoostPython/include
)

if (CMAKE_VERSION VERSION_GREATER 3.21)
  set_property(TARGET ProjetSuperDurApp PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(ProjetSuperDurApp PRIVATE ProjetSuperDurDll)
target_link_libraries(ProjetSuperDurApp PRIVATE BoostPython)

# TODO: Ajoutez des tests et installez des cibles si nécessaire.

find_package(boost_log REQUIRED CONFIG)
target_link_libraries(ProjetSuperDurApp PRIVATE Boost::log)

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
  COMMENT "Clang-format App"
)

add_custom_target(run-clang-format-projet-super-dur-app
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/.clang-format.stamp
)
