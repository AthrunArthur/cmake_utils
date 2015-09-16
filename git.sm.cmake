
macro(init_git_submodule)
  execute_process(COMMAND git submodule update --init --recursive
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
endmacro()

macro(add_git_submodule path proj_name)
  execute_process(
    COMMAND git pull origin master
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${path}
    )
  add_subdirectory(${path})
endmacro()

macro(expose_definitions defs)
  set(${PROJECT_NAME}_DEFINITIONS ${defs}
    CACHE INTERNAL "${PROJECT_NAME}: definitions" FORCE)
endmacro()

macro(expose_include_dirs dirs)
  set(${PROJECT_NAME}_INCLUDE_DIRS ${dirs}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
endmacro()

macro(expose_link_dirs dirs)
  set(${PROJECT_NAME}_LINK_DIRS ${dirs}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
endmacro()

macro(expose_libraries libs)
  set(${PROJECT_NAME}_LIBS ${libs}
    CACHE INTERNAL "${PROJECT_NAME}: Libraries" FORCE)
endmacro()
