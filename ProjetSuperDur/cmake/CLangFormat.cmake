function(add_clang_format_target target_name source_dirs)
  if(NOT CLANG_FORMAT_EXE)
    find_program(CLANG_FORMAT_EXE NAMES clang-format REQUIRED)
  endif()

  # Collecter les sources de manière récursive
  set(PROJ_SOURCES "")
  foreach(dir IN LISTS source_dirs)
    file(GLOB_RECURSE TMP_SOURCES
      CONFIGURE_DEPENDS
      ${dir}/*.cpp
      ${dir}/*.hpp
      ${dir}/*.cxx
      ${dir}/*.h
    )
    list(APPEND PROJ_SOURCES ${TMP_SOURCES})
  endforeach()

  # Enlever les doublons éventuels
  list(REMOVE_DUPLICATES PROJ_SOURCES)

  set(STAMP_FILE ${CMAKE_CURRENT_BINARY_DIR}/.${target_name}.clang-format.stamp)

  add_custom_command(
    OUTPUT ${STAMP_FILE}
    COMMAND ${CLANG_FORMAT_EXE} -i -style=Microsoft ${PROJ_SOURCES}
    COMMAND ${CMAKE_COMMAND} -E touch ${STAMP_FILE}
    DEPENDS ${PROJ_SOURCES}
    COMMENT "Clang-format ${target_name}"
  )

  add_custom_target(run-clang-format-${target_name}
    DEPENDS ${STAMP_FILE}
  )
endfunction()