
#  Copyright (c) 2012 Thomas Heller
#
#  Distributed under the Boost Software License, Version 1.0. (See accompanying
#  file LICENSE_1_0.txt or copy at http:#www.boost.org/LICENSE_1_0.txt)

add_definitions(-Doclm_EXPORTS)

set(
    OCLM_LIBRARY_INCLUDES
    ${CMAKE_SOURCE_DIR}/include/oclm/util/safe_bool.hpp
    ${CMAKE_SOURCE_DIR}/include/oclm/util/static.hpp
    ${CMAKE_SOURCE_DIR}/include/oclm/and_selector.hpp
    ${CMAKE_SOURCE_DIR}/include/oclm/async.hpp
    ${CMAKE_SOURCE_DIR}/include/oclm/buffer.hpp
    ${CMAKE_SOURCE_DIR}/include/oclm/command_queue.hpp
    ${CMAKE_SOURCE_DIR}/include/oclm/config.hpp
    ${CMAKE_SOURCE_DIR}/include/oclm/context.hpp
    ${CMAKE_SOURCE_DIR}/include/oclm/context_info.hpp
    ${CMAKE_SOURCE_DIR}/include/oclm/context_properties.hpp
    ${CMAKE_SOURCE_DIR}/include/oclm/device.hpp
    ${CMAKE_SOURCE_DIR}/include/oclm/device_info.hpp
    ${CMAKE_SOURCE_DIR}/include/oclm/exception.hpp
    ${CMAKE_SOURCE_DIR}/include/oclm/function.hpp
    ${CMAKE_SOURCE_DIR}/include/oclm/get_info.hpp
    ${CMAKE_SOURCE_DIR}/include/oclm/host.hpp
    ${CMAKE_SOURCE_DIR}/include/oclm/info.hpp
    ${CMAKE_SOURCE_DIR}/include/oclm/info_selector.hpp
    ${CMAKE_SOURCE_DIR}/include/oclm/init.hpp
    ${CMAKE_SOURCE_DIR}/include/oclm/kernel.hpp
    ${CMAKE_SOURCE_DIR}/include/oclm/oclm.hpp
    ${CMAKE_SOURCE_DIR}/include/oclm/or_selector.hpp
    ${CMAKE_SOURCE_DIR}/include/oclm/packaged_kernel.hpp
    ${CMAKE_SOURCE_DIR}/include/oclm/platform.hpp
    ${CMAKE_SOURCE_DIR}/include/oclm/platform_info.hpp
    ${CMAKE_SOURCE_DIR}/include/oclm/program.hpp
    ${CMAKE_SOURCE_DIR}/include/oclm/range.hpp
    ${CMAKE_SOURCE_DIR}/include/oclm/selector.hpp
)

set(
    OCLM_LIBRARY_SOURCES
    ${CMAKE_SOURCE_DIR}/src/context.cpp
    ${CMAKE_SOURCE_DIR}/src/context_info.cpp
    ${CMAKE_SOURCE_DIR}/src/command_queue.cpp
    ${CMAKE_SOURCE_DIR}/src/device.cpp
    ${CMAKE_SOURCE_DIR}/src/device_info.cpp
    ${CMAKE_SOURCE_DIR}/src/platform.cpp
    ${CMAKE_SOURCE_DIR}/src/platform_info.cpp
    ${CMAKE_SOURCE_DIR}/src/program.cpp
)

if(UNIX)
  add_library(oclm SHARED ${OCLM_LIBRARY_SOURCES} ${OCLM_LIBRARY_INCLUDES})
  target_link_libraries(oclm ${OCLM_LIBRARIES})
  install(TARGETS ${oclm})
endif()
if(MSVC)
  add_library(oclm SHARED ${OCLM_LIBRARY_SOURCES} ${OCLM_LIBRARY_INCLUDES})
  target_link_libraries(oclm opencl)
  install(TARGETS ${oclm})
endif()
