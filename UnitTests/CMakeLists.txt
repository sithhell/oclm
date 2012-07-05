
#  Copyright (c) 2012 Thomas Heller
#
#  Distributed under the Boost Software License, Version 1.0. (See accompanying
#  file LICENSE_1_0.txt or copy at http:#www.boost.org/LICENSE_1_0.txt)

add_executable(catch_platform catch_platform.cpp)
target_link_libraries(catch_platform oclm)

add_executable(catch_device catch_device.cpp)
target_link_libraries(catch_device oclm)
