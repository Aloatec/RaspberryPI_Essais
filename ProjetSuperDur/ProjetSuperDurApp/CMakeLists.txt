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

message(STATUS "CMAKE_PREFIX_PATH = ${CMAKE_PREFIX_PATH}")
message(STATUS "CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}")

find_package(SimpleLib CONFIG REQUIRED)
target_link_libraries(ProjetSuperDurApp PRIVATE SimpleLib::SimpleLibDll)


# TODO: Ajoutez des tests et installez des cibles si nécessaire.

find_package(boost_log REQUIRED CONFIG)
target_link_libraries(ProjetSuperDurApp PRIVATE Boost::log)

add_clang_format_target(projet-super-dur-app
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
