# CMakeList.txt : projet CMake pour ProjetSuperDur, incluez la source et définissez
# la logique spécifique au projet ici.
#

# Ajoutez une source à l'exécutable de ce projet.

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library (ProjetSuperDurDll SHARED 
    "src/ProjetSuperDurDll.cpp" 
    "include/ProjetSuperDurDll.h"
    "include/export.h")

target_include_directories(ProjetSuperDurDll PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ProjetSuperDurDll PROPERTY CXX_STANDARD 20)
endif()

if(WIN32)
    target_compile_definitions(ProjetSuperDurDll PRIVATE MYLIBRARY_EXPORTS)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.

find_package(boost_locale REQUIRED CONFIG)
target_link_libraries(ProjetSuperDurDll PRIVATE Boost::locale)

add_clang_format_target(projet-super-dur-dll
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

post_build_copy(ProjetSuperDurDll 
                ProjetSuperDurApp 
                ${CMAKE_CURRENT_SOURCE_DIR}/locales 
                locales)

