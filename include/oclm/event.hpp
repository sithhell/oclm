
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
            : e_(1, e)
        {}

        event(std::vector<cl_event> e)
            : e_(e)
        {
        }

        event(std::vector<event> e)
            : e_(e.begin(), e.end())
        {
        }

        void get() const
        {
            if(e_.empty()) return;
            cl_int err = CL_SUCCESS;
            err = clWaitForEvents(static_cast<cl_uint>(e_.size()), &e_[0]);
            OCLM_THROW_IF_EXCEPTION(err, "clWaitForEvents");
        }

        operator cl_event() const
        {
            cl_int err = CL_SUCCESS;
            if(e_.size() == 1)
            {
                return e_[0];
            }
            if(!e_.empty())
            {
                cl_context ctx = get_info<command_queue::context_info_type>(command_queue());
                cl_event e = clCreateUserEvent(ctx, &err);
                OCLM_THROW_IF_EXCEPTION(err, "clCreateUserEvents");
    #ifdef CL_VERSION_1_2
                err = clEnqueueMarkerWithWaitList(command_queue(),
                    static_cast<cl_uint>(e_.size()), &e_[0], &marker);
                OCLM_THROW_IF_EXCEPTION(err, "clEnqueueMarkerWithWaitList");
    #else
                get();
                err = clSetUserEventStatus(e, CL_COMPLETE);
    #endif
                return e;
            }
            else
                return cl_event();
        }

        typedef event_info<CL_EVENT_COMMAND_QUEUE, cl_command_queue> command_queue_info_type;

        cl_command_queue command_queue() const
        {
            return get_info<command_queue_info_type>(e_[0]);
        }

        private:
            std::vector<cl_event> e_;
    };
}

#endif
