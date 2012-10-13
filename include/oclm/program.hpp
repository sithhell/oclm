
//  Copyright (c) 2012 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef OCLM_PROGRAM_HPP
#define OCLM_PROGRAM_HPP

#include <oclm/config.hpp>
#include <oclm/info.hpp>

#include <string>
#include <vector>

// #include <boost/filesystem/path.hpp>
#include <boost/range.hpp>

namespace oclm {

    template <int Name, typename T>
    struct program_info
        : info<
            ::cl_program
          , T
          , ::clGetProgramInfo
          , Name
        >
    {};
    
    template <typename>
    struct is_program_info
        : boost::mpl::false_
    {};

    template <int Name, typename T>
    struct is_program_info<program_info<Name, T> >
        : boost::mpl::true_
    {};

    extern OCLM_EXPORT const program_info<CL_PROGRAM_REFERENCE_COUNT, cl_uint>              program_reference_count;
    extern OCLM_EXPORT const program_info<CL_PROGRAM_CONTEXT, cl_context>                   program_context;
    extern OCLM_EXPORT const program_info<CL_PROGRAM_NUM_DEVICES, cl_uint>                  program_num_devices;
    extern OCLM_EXPORT const program_info<CL_PROGRAM_DEVICES, std::vector<cl_device_id>>    program_devices;
    extern OCLM_EXPORT const program_info<CL_PROGRAM_SOURCE, std::string>                   program_source;
    extern OCLM_EXPORT const program_info<CL_PROGRAM_BINARY_SIZES, std::vector< ::size_t>>  program_binary_sizes;
    extern OCLM_EXPORT const program_info<CL_PROGRAM_BINARIES, std::vector< unsigned char*>>    program_binaries;
    extern OCLM_EXPORT const program_info<CL_PROGRAM_NUM_KERNELS, ::size_t>                 program_num_kernels;
    extern OCLM_EXPORT const program_info<CL_PROGRAM_KERNEL_NAMES, std::string>             program_kernel_names;

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

        // template <typename Info>
        // typename boost::enable_if<
        //     typename is_program_info<Info>::type
        //   , typename Info::result_type
        // >::type
        // get(Info) const
        // {
        //     return get_info<Info>(program_);
        // }

        // template <typename Info>
        // typename boost::disable_if<
        //     typename is_program_info<Info>::type
        //   , void
        // >::type
        // get(Info) const
        // {
        //     static_assert(
        //         is_program_info<Info>::value
        //       , "Template parameter is not a valid program info type"
        //     );
        // }
 
        std::vector<char> content_;
        std::string buildArgs_;
    };
}

#endif
