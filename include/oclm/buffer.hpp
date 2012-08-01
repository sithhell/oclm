
//  Copyright (c) 2012 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef OCLM_BUFFER_HPP
#define OCLM_BUFFER_HPP

#include <oclm/config.hpp>

#include <oclm/event.hpp>
#include <oclm/command_queue.hpp>

namespace oclm
{
    namespace policy
    {
        struct noop;
        struct input;
        struct output;
        struct io;
    }

    template <typename Src, typename Policy = policy::io, typename Enable = void>
    struct make_buffer
    {
        typedef void type;
        static type call(Src);
    };

    template <typename T, typename Policy>
    struct buffer;

    template <typename T, typename P1, typename P2>
    struct make_buffer<buffer<T, P1>, P2>
    {
        typedef buffer<T, P1> type;

        static type call(buffer<T, P1> &t)
        {
            return t;
        }
    };

    template <typename T, typename Policy>
    struct buffer
    {
        typedef T value_type;
        typedef Policy policy_type;

        buffer()
            : data(0)
            , size(0)
        {}

        buffer(buffer const & o)
            : data(o.data)
            , size(o.size)
            , mem(o.mem)
        {}

        template <typename U>
        explicit buffer(U & u)
        {
            typedef
                typename make_buffer<U, Policy>::type
                src_buffer_type;

            // static_assert(is_convertible<typename src_buffer_type::value_type, value_type>::value, "")

            src_buffer_type const src(make_buffer<U, Policy>::call(u));
            (*this) = src;
        }

        template <typename U>
        buffer& operator=(U & u)
        {
            typedef
                typename make_buffer<U, Policy>::type
                src_buffer_type;

            // static_assert(is_convertible<typename src_buffer_type::value_type, value_type>::value, "")

            src_buffer_type const src(make_buffer<U, Policy>::call(u));
            (*this) = src;

            return *this;
        }

        buffer & operator=(buffer const & o)
        {
            data = o.data;
            size = o.size;
            mem = o.mem;

            return *this;
        }

        void create(command_queue const & queue)
        {
            Policy::create(queue, *this);
        }

        void set_kernel_arg(cl_kernel k, std::size_t idx)
        {
            Policy::set_kernel_arg(k, static_cast<cl_uint>(idx), *this);
        }

        void write(command_queue const & queue)
        {
            std::vector<cl_event> tmp1;
            std::vector<cl_event> tmp2;
            write(queue, tmp1, tmp2);
        }

        void write(command_queue const & queue, cl_event const & e, std::vector<cl_event> & events)
        {
            std::vector<cl_event> tmp(1, e);
            write(queue, tmp, events);
        }

        void write(command_queue const & queue, std::vector<cl_event> & events)
        {
            std::vector<cl_event> tmp;
            write(queue, tmp, events);
        }

        void write(command_queue const & queue, std::vector<cl_event> & wait, std::vector<cl_event> &events)
        {
            Policy::write(queue, *this, wait, events);
        }

        void read(command_queue const & queue)
        {
            std::vector<cl_event> tmp;
            read(queue, tmp);
        }

        void read(command_queue const & queue, event const & e, std::vector<cl_event> & events)
        {
            std::vector<cl_event> tmp(1, e);
            read(queue, tmp, events);
        }

        void read(command_queue const & queue, std::vector<cl_event> & events)
        {
            std::vector<cl_event> tmp;
            read(queue, tmp, events);
        }

        void read(command_queue const & queue, std::vector<cl_event> & wait, std::vector<cl_event> &events)
        {
            Policy::read(queue, *this, wait, events);
        }

        T * data;
        std::size_t size;
        cl_mem mem;
    };

    namespace policy
    {
        struct noop
        {
            template <typename Buffer>
            static void create(command_queue const & queue, Buffer & b)
            {}

            template <typename Buffer>
            static void set_kernel_arg(cl_kernel k, std::size_t idx, Buffer & b)
            {
                cl_int err = CL_SUCCESS;
                err = clSetKernelArg(k, idx, sizeof(cl_mem), &b.mem);
                OCLM_THROW_IF_EXCEPTION(err, "clSetKernelArg");
            }

            template <typename Buffer>
            static void write(command_queue const &, Buffer &, std::vector<cl_event> &, std::vector<cl_event> &)
            {}

            template <typename Buffer>
            static void read(command_queue const &, Buffer &, std::vector<cl_event> &, std::vector<cl_event> &)
            {}

            template <typename Buffer1, typename Buffer2>
            static void copy(command_queue const &, Buffer1 &, Buffer2 &, std::vector<cl_event> &, std::vector<cl_event> &)
            {}
        };

        struct io
        {
            template <typename Buffer>
            static void create(command_queue const & queue, Buffer & b)
            {
                cl_int err = CL_SUCCESS;
                b.mem = clCreateBuffer(queue.ctx_, CL_MEM_READ_WRITE, b.size * sizeof(typename Buffer::value_type), NULL, &err);
                OCLM_THROW_IF_EXCEPTION(err, "clCreateBuffer");
            }
            template <typename Buffer>
            static void set_kernel_arg(cl_kernel k, std::size_t idx, Buffer & b)
            {
                cl_int err = CL_SUCCESS;
                err = clSetKernelArg(k, static_cast<cl_uint>(idx)
                  , static_cast<cl_uint>(sizeof(cl_mem)), &b.mem);
                OCLM_THROW_IF_EXCEPTION(err, "clSetKernelArg");
            }
            template <typename Buffer>
            static void write(command_queue const & queue, Buffer & b, std::vector<cl_event> & wait_list, std::vector<cl_event> &events)
            {
                cl_int err = CL_SUCCESS;
                cl_event event;
                err = clEnqueueWriteBuffer(queue, b.mem, false, 0
                  , b.size * sizeof(typename Buffer::value_type)
                  , b.data, static_cast<cl_uint>(wait_list.size())
                  , &wait_list[0], &event);
                OCLM_THROW_IF_EXCEPTION(err, "clEnqueueWriteBuffer");
                events.push_back(event);
            }

            template <typename Buffer>
            static void read(command_queue const & queue, Buffer & b, std::vector<cl_event> & wait_list, std::vector<cl_event> &events)
            {
                cl_int err = CL_SUCCESS;
                cl_event event;
                err = clEnqueueReadBuffer(queue, b.mem, false, 0
                  , b.size* sizeof(typename Buffer::value_type)
                  , b.data, static_cast<cl_uint>(wait_list.size())
                  , &wait_list[0], &event);
                OCLM_THROW_IF_EXCEPTION(err, "clEnqueueReadBuffer");
                events.push_back(event);
            }

            template <typename Buffer1, typename Buffer2>
            static void copy(command_queue const & q, Buffer1 & src, Buffer2 & dst, std::vector<cl_event> &, std::vector<cl_event> &)
            {}
        };

        struct input
        {
            template <typename Buffer>
            static void create(command_queue const & queue, Buffer & b)
            {
                cl_int err = CL_SUCCESS;
                b.mem = clCreateBuffer(queue.ctx_, CL_MEM_READ_ONLY, b.size* sizeof(typename Buffer::value_type), NULL, &err);
                OCLM_THROW_IF_EXCEPTION(err, "clCreateBuffer");
            }
            template <typename Buffer>
            static void set_kernel_arg(cl_kernel k, std::size_t idx, Buffer & b)
            {
                cl_int err = CL_SUCCESS;
                err = clSetKernelArg(k, static_cast<cl_uint>(idx)
                  , static_cast<cl_uint>(sizeof(cl_mem)), &b.mem);
                OCLM_THROW_IF_EXCEPTION(err, "clSetKernelArg");
            }

            template <typename Buffer>
            static void write(command_queue const & queue, Buffer & b, std::vector<cl_event> & wait_list, std::vector<cl_event> &events)
            {
                cl_int err = CL_SUCCESS;
                cl_event event;
                err = clEnqueueWriteBuffer(queue, b.mem, false, 0
                  , b.size* sizeof(typename Buffer::value_type)
                  , b.data, static_cast<cl_uint>(wait_list.size())
                  , &wait_list[0], &event);
                OCLM_THROW_IF_EXCEPTION(err, "clEnqueueWriteBuffer");
                events.push_back(event);
            }


            template <typename Buffer>
            static void read(command_queue const &, Buffer &, std::vector<cl_event> &, std::vector<cl_event> &)
            {}

            template <typename Buffer1, typename Buffer2>
            static void copy(command_queue const &, Buffer1 &, Buffer2 &, std::vector<cl_event> &, std::vector<cl_event> &)
            {}
        };

        struct output
        {
            template <typename Buffer>
            static void create(command_queue const & queue, Buffer & b)
            {
                cl_int err = CL_SUCCESS;
                b.mem = clCreateBuffer(queue.ctx_, CL_MEM_WRITE_ONLY, b.size* sizeof(typename Buffer::value_type), NULL, &err);
                OCLM_THROW_IF_EXCEPTION(err, "clCreateBuffer");
            }
            template <typename Buffer>
            static void set_kernel_arg(cl_kernel k, std::size_t idx, Buffer & b)
            {
                cl_int err = CL_SUCCESS;
                err = clSetKernelArg(k, static_cast<cl_uint>(idx)
                  , static_cast<cl_uint>(sizeof(cl_mem)), &b.mem);
                OCLM_THROW_IF_EXCEPTION(err, "clSetKernelArg");
            }

            template <typename Buffer>
            static void write(command_queue const &, Buffer &, std::vector<cl_event> &, std::vector<cl_event> &)
            {}

            template <typename Buffer>
            static void read(command_queue const & queue, Buffer & b, std::vector<cl_event> & wait_list, std::vector<cl_event> &events)
            {
                cl_int err = CL_SUCCESS;
                cl_event event;
                err = clEnqueueReadBuffer(queue, b.mem, false, 0
                  , b.size* sizeof(typename Buffer::value_type)
                  , b.data, static_cast<cl_uint>(wait_list.size())
                  , &wait_list[0], &event);
                OCLM_THROW_IF_EXCEPTION(err, "clEnqueueReadBuffer");
                events.push_back(event);
            }

            template <typename Buffer1, typename Buffer2>
            static void copy(command_queue const &, Buffer1 &, Buffer2 &, std::vector<cl_event> &, std::vector<cl_event> &)
            {}
        };
    }

    template <typename T, typename Policy>
    struct make_buffer<std::vector<T>, Policy>
    {
        typedef buffer<T, Policy> type;

        static type call(std::vector<T> &t)
        {
            type res;
            res.data = &t[0];
            res.size = t.size();
            return res;
        }
    };
}

#endif
