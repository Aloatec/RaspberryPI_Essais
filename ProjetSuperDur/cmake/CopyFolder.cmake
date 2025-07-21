function(post_build_copy from_target to_target source_dir dest_subdir)
  set(dest_dir "$<TARGET_FILE_DIR:${to_target}>/${dest_subdir}")

  add_custom_command(TARGET ${from_target} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${dest_dir}"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${source_dir}" "${dest_dir}"
  )
endfunction()