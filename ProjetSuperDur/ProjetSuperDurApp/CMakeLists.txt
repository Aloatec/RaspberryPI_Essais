# CMakeList.txt : projet CMake pour ProjetSuperDur, incluez la source et définissez
# la logique spécifique au projet ici.
#

# Ajoutez une source à l'exécutable de ce projet.
add_executable (ProjetSuperDurApp "src/ProjetSuperDur.cpp" "src/ProjetSuperDur.h")

add_dependencies(ProjetSuperDurApp ProjetSuperDurDll)

# Ajoute l'inclusion des headers de la DLL
target_include_directories(ProjetSuperDurApp PRIVATE
    ${CMAKE_SOURCE_DIR}/ProjetSuperDurDll/include
)

if (CMAKE_VERSION VERSION_GREATER 3.21)
  set_property(TARGET ProjetSuperDurApp PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(ProjetSuperDurApp PRIVATE ProjetSuperDurDll)

# TODO: Ajoutez des tests et installez des cibles si nécessaire.

find_package(boost_log REQUIRED CONFIG)
target_link_libraries(ProjetSuperDurApp PRIVATE Boost::log)
