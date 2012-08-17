
#  Copyright (c) 2012 Thomas Heller
#
#  Distributed under the Boost Software License, Version 1.0. (See accompanying
#  file LICENSE_1_0.txt or copy at http:#www.boost.org/LICENSE_1_0.txt)

add_executable(vecadd vecadd.cpp)
target_link_libraries(vecadd oclm)

add_executable(printInfos printInfos.cpp)
target_link_libraries(printInfos oclm)

add_executable(speedTest speedTest.cpp)
target_link_libraries(speedTest oclm)
