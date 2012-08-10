
//  Copyright (c) 2012 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef OCLM_PROGRAM_HPP
#define OCLM_PROGRAM_HPP

#include <oclm/config.hpp>

#include <string>
// #include <boost/filesystem/path.hpp>
#include <boost/range.hpp>

namespace oclm {

    struct program
    {
        /// \brief Creates a program from a string
        template <typename Range>
        program(Range const & src)
            : content_(boost::begin(src), boost::end(src))
        {}

        /// \brief Creates a program from a string and provide some build args
        template <typename RangeSrc, typename RangeArgs>
        program(RangeSrc const & src, RangeArgs const & args)
            : content_(boost::begin(src), boost::end(src))
            , buildArgs_(boost::begin(args), boost::end(args))
        {}

        //program(std::vector<std::string> const &);
        // Creates a program from a files ...
        //program(boost::filesystem::path const &);
        //program(std::vector<boost::filesystem::path> const &);

        // TODO: add constructors for binaries
 
        std::vector<char> content_;
        std::vector<char> buildArgs_;
    };
}

#endif
