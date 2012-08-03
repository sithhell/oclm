# Copyright (c) 2012 Hartmut Kaiser
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

if(NOT OCLM_FINDPACKAGE_LOADED)
  oclm_include(FindPackage)
endif()

oclm_find_package(OpenCL
    LIBRARIES opencl.lib cl libcl OpenCL libOpenCL
  LIBRARY_PATHS lib/x86_64 lib/x64
  HEADERS CL/opencl.h
  HEADER_PATHS include inc)

