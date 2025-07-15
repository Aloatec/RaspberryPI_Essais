# CMakeList.txt : projet CMake pour ProjetSuperDur, incluez la source et définissez
# la logique spécifique au projet ici.
#

# Ajoutez une source à l'exécutable de ce projet.


set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library (BoostPython STATIC 
    "src/BoostApplication.cpp" 
    "src/pch.h"
    "src/pch.cpp"
    "include/BoostApplication.h")

target_include_directories(BoostPython PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BoostPython PROPERTY CXX_STANDARD 20)
endif()

if(WIN32)
    target_compile_definitions(BoostPython PRIVATE BOOSTPYTHON_EXPORTS)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
