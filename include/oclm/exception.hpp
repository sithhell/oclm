
//  Copyright (c) 2012 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef OCLM_EXCEPTION_HPP
#define OCLM_EXCEPTION_HPP

#include <oclm/config.hpp>

#include <string>
#include <sstream>

#define OCLM_THROW_IF_EXCEPTION(ERR, FUNCTION)                                  \
    if(ERR != CL_SUCCESS)                                                       \
    {                                                                           \
        switch ( ERR )                                                          \
        {                                                                       \
            case -1:                                                            \
                throw ::oclm::exception(FUNCTION ": CL_DEVICE_NOT_FOUND");      \
                break;                                                          \
            case -2:                                                            \
                throw ::oclm::exception(FUNCTION ": CL_DEVICE_NOT_AVAILABLE");  \
                break;                                                          \
            case -3:                                                            \
                throw ::oclm::exception(FUNCTION ": CL_COMPILER_NOT_AVAILABLE");\
                break;                                                          \
            case -4:                                                            \
                throw ::oclm::exception(FUNCTION ": CL_MEM_OBJECT_ALLOCATION_FAILURE");\
                break;                                                          \
            case -5:                                                            \
                throw ::oclm::exception(FUNCTION ": CL_OUT_OF_RESOURCES");      \
                break;                                                          \
            case -6:                                                            \
                throw ::oclm::exception(FUNCTION ": CL_OUT_OF_HOST_MEMORY");    \
                break;                                                          \
            case -7:                                                            \
                throw ::oclm::exception(FUNCTION ": CL_PROFILING_INFO_NOT_AVAILABLE");\
                break;                                                          \
            case -8:                                                            \
                throw ::oclm::exception(FUNCTION ": CL_MEM_COPY_OVERLAP");      \
                break;                                                          \
            case -9:                                                            \
                throw ::oclm::exception(FUNCTION ": CL_IMAGE_FORMAT_MISMATCH"); \
                break;                                                          \
            case -10:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_IMAGE_FORMAT_NOT_SUPPORTED");\
                break;                                                          \
            case -11:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_BUILD_PROGRAM_FAILURE"); \
                break;                                                          \
            case -12:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_MAP_FAILURE");           \
                break;                                                          \
            case -13:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_MISALIGNED_SUB_BUFFER_OFFSET");\
                break;                                                          \
            case -14:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST");\
                break;                                                          \
            case -30:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_VALUE");         \
                break;                                                          \
            case -31:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_DEVICE_TYPE");   \
                break;                                                          \
            case -32:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_PLATFORM");      \
                break;                                                          \
            case -33:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_DEVICE");        \
                break;                                                          \
            case -34:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_CONTEXT");       \
                break;                                                          \
            case -35:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_QUEUE_PROPERTIES");\
                break;                                                          \
            case -36:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_COMMAND_QUEUE"); \
                break;                                                          \
            case -37:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_HOST_PTR");      \
                break;                                                          \
            case -38:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_MEM_OBJECT");    \
                break;                                                          \
            case -39:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_IMAGE_FORMAT_DESCRIPTOR");\
                break;                                                          \
            case -40:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_IMAGE_SIZE");    \
                break;                                                          \
            case -41:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_SAMPLER");       \
                    break;                                                      \
            case -42:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_BINARY");        \
                break;                                                          \
            case -43:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_BUILD_OPTIONS"); \
                break;                                                          \
            case -44:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_PROGRAM");       \
                break;                                                          \
            case -45:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_PROGRAM_EXECUTABLE");\
                break;                                                          \
            case -46:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_KERNEL_NAME");   \
                break;                                                          \
            case -47:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_KERNEL_DEFINITION");\
                break;                                                          \
            case -48:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_KERNEL");        \
                break;                                                          \
            case -49:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_ARG_INDEX");     \
                break;                                                          \
            case -50:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_ARG_VALUE");     \
                break;                                                          \
            case -51:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_ARG_SIZE");      \
                break;                                                          \
            case -52:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_KERNEL_ARGS");   \
                break;                                                          \
            case -53:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_WORK_DIMENSION");\
                break;                                                          \
            case -54:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_WORK_GROUP_SIZE");\
                break;                                                          \
            case -55:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_WORK_ITEM_SIZE");\
                break;                                                          \
            case -56:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_GLOBAL_OFFSET"); \
                break;                                                          \
            case -57:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_EVENT_WAIT_LIST");\
                break;                                                          \
            case -58:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_EVENT");         \
                break;                                                          \
            case -59:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_OPERATION");     \
                break;                                                          \
            case -60:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_GL_OBJECT");     \
                break;                                                          \
            case -61:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_BUFFER_SIZE");   \
                break;                                                          \
            case -62:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_MIP_LEVEL");     \
                break;                                                          \
            case -63:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_GLOBAL_WORK_SIZE");\
                break;                                                          \
            case -64:                                                           \
                throw ::oclm::exception(FUNCTION ": CL_INVALID_PROPERTY");      \
                break;                                                          \
            default:                                                            \
                {                                                               \
                    std::stringstream s;                                        \
                    s << FUNCTION << ": UNKNOWN ERROR ( " << ERR << " )";       \
                    throw ::oclm::exception(s.str().c_str());                   \
                }                                                               \
        }                                                                       \
    }                                                                           \
    ERR*=CL_SUCCESS                                                             \
/**/

namespace oclm {
    struct exception : std::exception
    {
        exception() : what_("UNKNOWN") {}

        exception(const char * what) : what_(what) {}
    
        virtual ~exception() throw() {}

        virtual const char * what() const throw()
        {
            return what_;
        }

        private:
            const char * what_;
    };
}

#endif
