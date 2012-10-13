
//  Copyright (c) 2012 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef OCLM_KERNEL_HPP
#define OCLM_KERNEL_HPP

#include <string>

#include <oclm/range.hpp>
#include <oclm/function.hpp>
#include <oclm/get_info.hpp>

namespace oclm {

    template <int Name, typename T>
    struct kernel_info
        : info<
            ::cl_command_queue
          , T
          , ::clGetCommandQueueInfo
          , Name
        >
    {};
    
    template <typename>
    struct is_kernel_info
        : boost::mpl::false_
    {};

    template <int Name, typename T>
    struct is_kernel_info<kernel_info<Name, T> >
        : boost::mpl::true_
    {};

    // extern OCLM_EXPORT const kernel_info<CL_QUEUE_CONTEXT, cl_context>                      queue_context;

    struct kernel
    {
        /// \brief create a kernel object
        ///
        /// Create a kernel named \kernel_name from a program \p 
        kernel(program const & p, std::string const & kernel_name)
            : p_(p)
            , kernel_name_(kernel_name)
        {}

        /// \brief create a kernel object
        ///
        /// Create a kernel named \kernel_name from a string \p src with build
        /// arguments \p args
        kernel(std::string const & src, std::string const & args,
            std::string const & kernel_name)
            : p_(oclm::program(src,args))
            , kernel_name_(kernel_name)
        {}

        template <typename Tag>
        oclm::function operator[](kernel_range<Tag> f)
        {
            kernel_range<tag::collection_> coll;
            coll.set(f);
            return oclm::function(p_, kernel_name_, coll);
        }

        template <typename Info>
        typename boost::enable_if<
            typename is_kernel_info<Info>::type
          , typename Info::result_type
        >::type
        get(Info) const
        {
            return get_info<Info>(k_);
        }

        template <typename Info>
        typename boost::disable_if<
            typename is_kernel_info<Info>::type
          , void
        >::type
        get(Info) const
        {
            static_assert(
                is_kernel_info<Info>::value
              , "Template parameter is not a valid command_queue info type"
            );
        }

        program p_;
        cl_kernel k_;
        std::string kernel_name_;
    };

}

#endif
