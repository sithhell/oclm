# Copyright (c) 2007-2012 Hartmut Kaiser
# Copyright (c) 2010-2011 Matt Anderson
# Copyright (c) 2011      Bryce Lelbach
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(OCLM_FINDPACKAGE_LOADED TRUE)

include(OCLM_Include)
oclm_include(ParseArguments)

macro(oclm_find_headers _name)

  string(TOUPPER ${_name} name)
  if(NOT ${name}_HEADER_SEARCHED)
    oclm_debug("find_headers.${name}" "Finding headers for package ${name}.")

    oclm_parse_arguments(${name}
      "HEADERS;HEADER_PATHS;LIBRARIES;LIBRARY_PATHS" "ESSENTIAL" ${ARGN})

    ##########################################################################
    # Check if ${name}_ROOT is defined and use that path first if
    # ${name}_USE_SYSTEM is not defined.
    if(NOT ${name}_USE_SYSTEM)
      if(NOT ${name}_ROOT AND NOT $ENV{${name}_ROOT} STREQUAL "")
        set(${name}_ROOT $ENV{${name}_ROOT})
      endif()
    endif()

    set(rooted_header_paths)
    foreach(path ${${name}_HEADER_PATHS})
      list(APPEND rooted_header_paths ${${name}_ROOT}/${path})
    endforeach()

    if(${name}_ROOT)
      find_path(${name}_INCLUDE_DIR
        NAMES ${${name}_HEADERS}
        PATHS ${rooted_header_paths}
        NO_DEFAULT_PATH)

      if(NOT ${name}_INCLUDE_DIR)
        oclm_warn("find_headers.${name}" "Header not found in ${${name}_ROOT}, trying system path.")
      else()
        set(${name}_HEADER_SEARCHED ON CACHE INTERNAL "Searched for ${name} headers.")
        oclm_info("find_headers.${name}" "Header found in ${${name}_INCLUDE_DIR}.")
      endif()
    endif()

    # if not found, retry using system path
    if(NOT ${name}_ROOT)
      find_path(${name}_INCLUDE_DIR NAMES ${${name}_HEADERS}
                                    PATH_SUFFIXES ${${name}_HEADER_PATHS})

      if(NOT ${name}_INCLUDE_DIR)
        if(${name}_ESSENTIAL)
          oclm_error("find_headers.${name}" "Header not found in system path.")
        else()
          oclm_warn("find_headers.${name}" "Header not found in system path.")
        endif()
      else()
        set(${name}_HEADER_SEARCHED ON CACHE INTERNAL "Searched for ${name} headers.")
        oclm_info("find_headers.${name}" "Header found in system path.")
      endif()
    endif()

  endif()
endmacro()

macro(oclm_find_package _name)
  string(TOUPPER ${_name} name)

  if(${name}_DISABLE)
    oclm_info("find_package.${name}" "Library search disabled by user.")

    if(NOT ${name}_ROOT)
      set(${name}_ROOT ${name}_ROOT-NOTFOUND)
    endif()

    if(NOT ${name}_LIBRARY)
      set(${name}_LIBRARY ${name}_LIBRARY-NOTFOUND)
    endif()

    if(NOT ${name}_LIBRARY_DIR)
      set(${name}_LIBRARY_DIR ${name}_LIBRARY_DIR-NOTFOUND)
    endif()

    if(NOT ${name}_INCLUDE_DIR)
      set(${name}_INCLUDE_DIR ${name}_INCLUDE_DIR-NOTFOUND)
    endif()

    set(${name}_FOUND OFF CACHE BOOL "Found ${name}.")

    set(${name}_ROOT ${${name}_ROOT} CACHE PATH "${name} root directory.")
    set(${name}_LIBRARY ${${name}_LIBRARY} CACHE FILEPATH "${name} shared library.")
    set(${name}_LIBRARY_DIR ${${name}_LIBRARY_DIR} CACHE PATH "${name} library directory.")
    set(${name}_INCLUDE_DIR ${${name}_INCLUDE_DIR} CACHE PATH "${name} include directory.")
    mark_as_advanced(FORCE ${name}_ROOT ${name}_LIBRARY ${name}_LIBRARY_DIR ${name}_INCLUDE_DIR)
  else()
    if(NOT ${name}_SEARCHED)
      oclm_info("find_package.${name}" "Searching for package ${name}.")

      if(NOT ${name}_HEADERS_SEARCHED)
        oclm_find_headers(${name} ${ARGN})
      endif()

      set(rooted_paths)
      foreach(path ${${name}_LIBRARY_PATHS})
        list(APPEND rooted_paths ${${name}_ROOT}/${path})
      endforeach()

      if(${name}_ROOT)
        oclm_print_list("DEBUG" "find_package.${name}" "Library names" ${name}_LIBRARIES)
        oclm_print_list("DEBUG" "find_package.${name}" "Library paths" rooted_paths)
        find_library(${name}_LIBRARY
          NAMES ${${name}_LIBRARIES}
          PATHS ${rooted_paths}
          NO_DEFAULT_PATH)

        if(NOT ${name}_LIBRARY)
          oclm_warn("find_package.${name}" "Library not found in ${${name}_ROOT}, trying system path.")
        else()
          set(${name}_SEARCHED ON CACHE INTERNAL "Searched for ${name} library.")
          oclm_info("find_package.${name}" "Library found in ${${name}_ROOT}.")
        endif()
      endif()

      # if not found, retry using system path
      if(NOT ${name}_ROOT)
        oclm_print_list("DEBUG" "find_package.${name}" "Library names" ${name}_LIBRARIES)
        oclm_print_list("DEBUG" "find_package.${name}" "Library paths" ${name}_LIBRARY_PATHS)
        find_library(${name}_LIBRARY NAMES ${${name}_LIBRARIES}
                                     PATH_SUFFIXES ${${name}_LIBRARY_PATHS})

        if(NOT ${name}_LIBRARY)
          if(${name}_ESSENTIAL)
            oclm_error("find_package.${name}" "Library not found in system path.")
          else()
            oclm_warn("find_package.${name}" "Library not found in system path.")
          endif()
        else()
          set(${name}_SEARCHED ON CACHE INTERNAL "Searched for ${name} library.")
          oclm_info("find_package.${name}" "Library found in system path.")
        endif()
      endif()

      set(${name}_FIND_QUIETLY TRUE)
      include(FindPackageHandleStandardArgs)
      find_package_handle_standard_args(${name}
        DEFAULT_MSG ${name}_LIBRARY ${name}_INCLUDE_DIR)

      oclm_info("find_package.${name}" "${name}_LIBRARY ${${name}_LIBRARY}.")
      oclm_info("find_package.${name}" "${name}_LIBRARY_DIR ${${name}_LIBRARY_DIR}.")
      oclm_info("find_package.${name}" "${name}_INCLUDE_DIR ${${name}_INCLUDE_DIR}.")

      if(${name}_FOUND)
        get_filename_component(${name}_ROOT ${${name}_INCLUDE_DIR} PATH)
        get_filename_component(${name}_LIBRARY_DIR ${${name}_LIBRARY} PATH)
        set(${name}_FOUND ${${name}_FOUND} CACHE BOOL "Found ${name}.")
      else()
        if(NOT ${name}_ROOT)
          set(${name}_ROOT ${name}_ROOT-NOTFOUND)
        endif()

        if(NOT ${name}_LIBRARY)
          set(${name}_LIBRARY ${name}_LIBRARY-NOTFOUND)
        endif()

        if(NOT ${name}_LIBRARY_DIR)
          set(${name}_LIBRARY_DIR ${name}_LIBRARY_DIR-NOTFOUND)
        endif()

        if(NOT ${name}_INCLUDE_DIR)
          set(${name}_INCLUDE_DIR ${name}_INCLUDE_DIR-NOTFOUND)
        endif()

        set(${name}_FOUND OFF CACHE BOOL "Found ${name}.")
      endif()

      set(${name}_ROOT ${${name}_ROOT} CACHE PATH "${name} root directory.")
      set(${name}_LIBRARY ${${name}_LIBRARY} CACHE FILEPATH "${name} shared library.")
      set(${name}_LIBRARY_DIR ${${name}_LIBRARY_DIR} CACHE PATH "${name} library directory.")
      set(${name}_INCLUDE_DIR ${${name}_INCLUDE_DIR} CACHE PATH "${name} include directory.")
      mark_as_advanced(FORCE ${name}_ROOT ${name}_LIBRARY ${name}_LIBRARY_DIR ${name}_INCLUDE_DIR)
    endif()
  endif()
endmacro()

