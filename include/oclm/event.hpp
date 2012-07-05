
//  Copyright (c) 2012 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef OCLM_EVENT_HPP
#define OCLM_EVENT_HPP

#include <oclm/config.hpp>
#include <oclm/get_info.hpp>
#include <oclm/command_queue.hpp>

namespace oclm {
    template <int Name, typename T>
    struct event_info
        : info<
            ::cl_event
          , T
          , ::clGetEventInfo
          , Name
        >
    {};
    
    template <typename>
    struct is_event_info
        : boost::mpl::false_
    {};

    template <int Name, typename T>
    struct is_event_info<event_info<Name, T> >
        : boost::mpl::true_
    {};

    struct event
    {
        event()
        {
        }

        event(cl_event e)
            : marker(e)
        {}
        
        event(std::vector<cl_event> e)
            : e_(e)
        {
            if(e.empty()) return;
            if(e.size() == 1)
            {
                marker = e_[0];
            }
            else
            {
                cl_int err = CL_SUCCESS;
                cl_context ctx = get_info<command_queue::context_info_type>(command_queue());
                marker = clCreateUserEvent(ctx, &err);
                OCLM_THROW_IF_EXCEPTION(err, "clCreateUserEvents");

#ifdef CL_VERSION_1_2
                err = clEnqueueMarkerWithWaitList(command_queue(), e_.size(), &e_[0], &marker);
                OCLM_THROW_IF_EXCEPTION(err, "clEnqueueMarkerWithWaitList");
#endif
            }
        }
        
        event(std::vector<event> e)
            : e_(e.begin(), e.end())
        {
            if(e.empty()) return;
            if(e.size() == 1)
            {
                marker = e_[0];
            }
            else
            {
                cl_int err = CL_SUCCESS;
                cl_context ctx = get_info<command_queue::context_info_type>(command_queue());
                marker = clCreateUserEvent(ctx, &err);
                OCLM_THROW_IF_EXCEPTION(err, "clCreateUserEvents");

#ifdef CL_VERSION_1_2
                err = clEnqueueMarkerWithWaitList(command_queue(), e_.size(), &e_[0], &marker);
                OCLM_THROW_IF_EXCEPTION(err, "clEnqueueMarkerWithWaitList");
#endif
            }
        }

        void get()
        {
            if(e_.empty()) return;
            cl_int err = CL_SUCCESS;
            err = clWaitForEvents(1, &marker);
            OCLM_THROW_IF_EXCEPTION(err, "clWaitForEvents");
        }

        operator cl_event const &() const
        {
            return marker;
        }
        
        typedef event_info<CL_EVENT_COMMAND_QUEUE, cl_command_queue> command_queue_info_type;

        cl_command_queue command_queue()
        {
            return get_info<command_queue_info_type>(e_[0]);
        }

        private:
            cl_event marker;
            std::vector<cl_event> e_;
    };
}

#endif
