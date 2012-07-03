
//  Copyright (c) 2012 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef OCLM_INIT_HPP
#define OCLM_INIT_HPP

#include <vector>
#include <string>

namespace oclm {
    bool OCLM_EXPORT init();
    bool OCLM_EXPORT init(int argc, char ** argv);
    bool OCLM_EXPORT init(std::vector<std::string> const & args);
}

#endif
