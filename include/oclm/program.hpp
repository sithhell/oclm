
//  Copyright (c) 2012 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef OCLM_PROGRAM_HPP
#define OCLM_PROGRAM_HPP

#include <oclm/config.hpp>
#include <oclm/get_info.hpp>
#include <oclm/command_queue.hpp>

#include <string>
#include <vector>
#include <algorithm>

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
        program( program const & p )
            : program_( p.program_ )
            , content_( p.content_ )
            , buildArgs_( p.buildArgs_ )
        {
            cl_int err = ::clRetainProgram(program_);
            OCLM_THROW_IF_EXCEPTION(err, "clRetainProgram");
        }

        template <typename RangeArgs>
        program( cl_program & p, RangeArgs const & args )
            : program_( p )
            , buildArgs_(boost::begin(args), boost::end(args))
        {
            cl_int err = ::clRetainProgram(program_);
            OCLM_THROW_IF_EXCEPTION(err, "clRetainProgram");

            std::string content( get(program_source) );
            content_ = std::vector<char>(boost::begin(content), boost::end(content));
        }

        operator cl_program const &() const
        {
            return program_;
        }

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

        ~program()
        {
            cl_int err = ::clReleaseProgram(program_);
            OCLM_THROW_IF_EXCEPTION(err, "clReleaseProgram");
        }

        //program(std::vector<std::string> const &);
        // Creates a program from a files ...
        //program(boost::filesystem::path const &);
        //program(std::vector<boost::filesystem::path> const &);

        // TODO: add constructors for binaries

        template <typename Info>
        typename boost::enable_if<
            typename is_program_info<Info>::type
          , typename Info::result_type
        >::type
        get(Info) const
        {
            return get_info<Info>(program_);
        }

        template <typename Info>
        typename boost::disable_if<
            typename is_program_info<Info>::type
          , void
        >::type
        get(Info) const
        {
            static_assert(
                is_program_info<Info>::value
              , "Template parameter is not a valid program info type"
            );
        }

        void build( command_queue & queue )
        {
            cl_uint n = 0;
            cl_int err = CL_SUCCESS;
            std::size_t length[] = {content_.size()};
            const char* strings[] = {&content_[0]};

            std::vector<cl_device_id> device_ids;
            cl_platform_id tmpPlatform = queue.d_.get(device_platform);

            err = ::clGetDeviceIDs(tmpPlatform, CL_DEVICE_TYPE_ALL, 0, NULL, &n);
            OCLM_THROW_IF_EXCEPTION(err, "clGetDeviceIDs");

            err = ::clGetDeviceIDs(tmpPlatform, CL_DEVICE_TYPE_ALL, n, &device_ids[0], NULL);
            OCLM_THROW_IF_EXCEPTION(err, "clGetDeviceIDs");

            //check if program was built before
            if ( get(program_reference_count) > 0 && std::find( device_ids.begin(), device_ids.end(), queue.d_) != device_ids.end() )
            {
                err = ::clRetainProgram(program_);
                OCLM_THROW_IF_EXCEPTION(err, "clRetainProgram");

                return;
            }

            err = CL_SUCCESS;
            cl_program p = clCreateProgramWithSource(queue.ctx_, 1, strings, length, &err);
            OCLM_THROW_IF_EXCEPTION(err, "clCreateProgramWithSource");

            err = ::clBuildProgram(p, static_cast<cl_uint>( device_ids.size() ), &device_ids[0], buildArgs_.c_str(), NULL, NULL);

            // check for build errors
            if ( err != CL_SUCCESS )
            {
                // check all devices for build errors
                for ( ::size_t i = 0; i < device_ids.size(); ++i )
                {
                    cl_int tmpErr = CL_SUCCESS;
                    std::size_t buildLogSize;

                    tmpErr = ::clGetProgramBuildInfo(p, device_ids[0], CL_PROGRAM_BUILD_LOG, 0, NULL, &buildLogSize);
                    OCLM_THROW_IF_EXCEPTION(tmpErr, "clGetProgramBuildInfo");

                    char* buildLog = new char[buildLogSize];

                    tmpErr = ::clGetProgramBuildInfo(p, device_ids[0], CL_PROGRAM_BUILD_LOG, buildLogSize, buildLog, NULL);
                    OCLM_THROW_IF_EXCEPTION(tmpErr, "clGetProgramBuildInfo");

                    std::cerr << "Build log:\n" << buildLog << std::endl;

                    delete buildLog;

                    OCLM_THROW_IF_EXCEPTION(err, "clBuildProgram");
                }
            }

            program_ = p;
        }
 
        cl_program program_;
        std::vector<char> content_;
        std::string buildArgs_;
    };
}

#endif
