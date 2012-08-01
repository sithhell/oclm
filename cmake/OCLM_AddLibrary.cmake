# Copyright (c) 2012 Thomas Heller
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

macro(oclm_add_library LIB)
    if(OCLM_LIBRARIES)
        set(OCLM_LIBRARIES ${OCLM_LIBRARIES} ${LIB})
    else()
        set(OCLM_LIBRARIES ${LIB})
    endif()
endmacro()
