
//  Copyright (c) 2012 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef OCLM_DEVICE_INFO_HPP
#define OCLM_DEVICE_INFO_HPP

#include <oclm/info.hpp>

#include <string>
#include <vector>

#include <boost/mpl/bool.hpp>

namespace oclm
{
    template <int Name, typename T>
    struct device_info
        : info<
            ::cl_device_id
          , T
          , ::clGetDeviceInfo
          , Name
        >
    {};

    template <typename>
    struct is_device_info
        : boost::mpl::false_
    {};

    template <int Name, typename T>
    struct is_device_info<device_info<Name, T> >
        : boost::mpl::true_
    {};

    extern OCLM_EXPORT const device_info<CL_DEVICE_MAX_COMPUTE_UNITS, cl_uint>                   device_compute_units;
    extern OCLM_EXPORT const device_info<CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, cl_uint>            device_max_work_item_dimensions;
    extern OCLM_EXPORT const device_info<CL_DEVICE_MAX_WORK_GROUP_SIZE, ::size_t>                device_max_work_group_size;
    extern OCLM_EXPORT const device_info<CL_DEVICE_MAX_WORK_ITEM_SIZES, std::vector< ::size_t>>  device_max_work_item_size;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR, cl_uint>         device_preferred_vector_width_char;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT, cl_uint>        device_preferred_vector_width_short;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT, cl_uint>          device_preferred_vector_width_int;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG, cl_uint>         device_preferred_vector_width_long;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT, cl_uint>        device_preferred_vector_width_float;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE, cl_uint>       device_preferred_vector_width_double;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF, cl_uint>         device_preferred_vector_width_half;
    extern OCLM_EXPORT const device_info<CL_DEVICE_MAX_CLOCK_FREQUENCY, cl_uint>                 device_max_clock_frequency;
    extern OCLM_EXPORT const device_info<CL_DEVICE_ADDRESS_BITS, cl_uint>                        device_address_bits;
    extern OCLM_EXPORT const device_info<CL_DEVICE_MAX_READ_IMAGE_ARGS, cl_uint>                 device_max_read_image_args;
    extern OCLM_EXPORT const device_info<CL_DEVICE_MAX_WRITE_IMAGE_ARGS, cl_uint>                device_max_write_image_args;
    extern OCLM_EXPORT const device_info<CL_DEVICE_MAX_MEM_ALLOC_SIZE, cl_ulong>                 device_max_mem_alloc_size;
    extern OCLM_EXPORT const device_info<CL_DEVICE_IMAGE2D_MAX_WIDTH, ::size_t>                  device_image2d_max_width;
    extern OCLM_EXPORT const device_info<CL_DEVICE_IMAGE2D_MAX_HEIGHT, ::size_t>                 device_image2d_max_height;
    extern OCLM_EXPORT const device_info<CL_DEVICE_IMAGE3D_MAX_WIDTH, ::size_t>                  device_image3d_max_width;
    extern OCLM_EXPORT const device_info<CL_DEVICE_IMAGE3D_MAX_HEIGHT, ::size_t>                 device_image3d_max_height;
    extern OCLM_EXPORT const device_info<CL_DEVICE_IMAGE3D_MAX_DEPTH, ::size_t>                  device_image3d_max_depth;
    extern OCLM_EXPORT const device_info<CL_DEVICE_IMAGE_SUPPORT, cl_bool>                       device_image_support;
    extern OCLM_EXPORT const device_info<CL_DEVICE_MAX_PARAMETER_SIZE, ::size_t>                 device_max_parameter_size;
    extern OCLM_EXPORT const device_info<CL_DEVICE_MAX_SAMPLERS, cl_uint>                        device_max_samplers;
    extern OCLM_EXPORT const device_info<CL_DEVICE_MEM_BASE_ADDR_ALIGN, cl_uint>                 device_mem_base_addr_align;
    extern OCLM_EXPORT const device_info<CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE, ::size_t>           device_min_data_type_align_size;  // deprectated in opencl 1.2
    extern OCLM_EXPORT const device_info<CL_DEVICE_SINGLE_FP_CONFIG, cl_device_fp_config>        device_single_fp_config;
    extern OCLM_EXPORT const device_info<CL_DEVICE_DOUBLE_FP_CONFIG, cl_device_fp_config>        device_double_fp_config;
    extern OCLM_EXPORT const device_info<CL_DEVICE_GLOBAL_MEM_CACHE_TYPE, cl_device_mem_cache_type> device_global_mem_chache_config;
    extern OCLM_EXPORT const device_info<CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE, cl_uint>           device_global_mem_cacheline_config;
    extern OCLM_EXPORT const device_info<CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, cl_ulong>              device_global_mem_cache_size;
    extern OCLM_EXPORT const device_info<CL_DEVICE_GLOBAL_MEM_SIZE, cl_ulong>                    device_global_mem_size;
    extern OCLM_EXPORT const device_info<CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, cl_ulong>           device_max_constant_buffer_size;
    extern OCLM_EXPORT const device_info<CL_DEVICE_MAX_CONSTANT_ARGS, cl_uint>                   device_max_constant_args;
    extern OCLM_EXPORT const device_info<CL_DEVICE_LOCAL_MEM_TYPE, cl_device_local_mem_type>     device_local_mem_type;
    extern OCLM_EXPORT const device_info<CL_DEVICE_LOCAL_MEM_SIZE, cl_ulong>                     device_local_mem_size;
    extern OCLM_EXPORT const device_info<CL_DEVICE_ERROR_CORRECTION_SUPPORT, cl_bool>            device_error_correction_support;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PROFILING_TIMER_RESOLUTION, ::size_t>         device_profiling_timer_resolution;
    extern OCLM_EXPORT const device_info<CL_DEVICE_ENDIAN_LITTLE, cl_bool>                       device_endian_little;
    extern OCLM_EXPORT const device_info<CL_DEVICE_AVAILABLE, cl_bool>                           device_available;
    extern OCLM_EXPORT const device_info<CL_DEVICE_COMPILER_AVAILABLE, cl_bool>                  device_compiler_available;
    extern OCLM_EXPORT const device_info<CL_DEVICE_EXECUTION_CAPABILITIES, cl_device_exec_capabilities> device_execution_capabilities;
    extern OCLM_EXPORT const device_info<CL_DEVICE_QUEUE_PROPERTIES, cl_command_queue_properties>   device_queue_properties;
    extern OCLM_EXPORT const device_info<CL_DEVICE_NAME, std::string>                             device_name;
    extern OCLM_EXPORT const device_info<CL_DEVICE_VENDOR, std::string>                           device_vendor;
    extern OCLM_EXPORT const device_info<CL_DRIVER_VERSION, std::string>                          device_driver_version;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PROFILE, std::string>                          device_profile;
    extern OCLM_EXPORT const device_info<CL_DEVICE_VERSION, std::string>                          device_version;
    extern OCLM_EXPORT const device_info<CL_DEVICE_EXTENSIONS, std::string>                       device_extensions;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PLATFORM, cl_platform_id>                      device_platform;
    extern OCLM_EXPORT const device_info<CL_DEVICE_HOST_UNIFIED_MEMORY, cl_bool>                  device_host_unified_memory;
    extern OCLM_EXPORT const device_info<CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR, cl_uint>             device_native_vector_width_char;
    extern OCLM_EXPORT const device_info<CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT, cl_uint>            device_native_vector_width_short;
    extern OCLM_EXPORT const device_info<CL_DEVICE_NATIVE_VECTOR_WIDTH_INT, cl_uint>              device_native_vector_width_int;
    extern OCLM_EXPORT const device_info<CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG, cl_uint>             device_native_vector_width_long;
    extern OCLM_EXPORT const device_info<CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT, cl_uint>            device_native_vector_width_float;
    extern OCLM_EXPORT const device_info<CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE, cl_uint>           device_native_vector_width_double;
    extern OCLM_EXPORT const device_info<CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF, cl_uint>             device_native_vector_width_half;
    extern OCLM_EXPORT const device_info<CL_DEVICE_OPENCL_C_VERSION, std::string>                 device_opencl_c_version;
    extern OCLM_EXPORT const device_info<CL_DEVICE_LINKER_AVAILABLE, cl_bool>                     device_linker_available;
    extern OCLM_EXPORT const device_info<CL_DEVICE_BUILT_IN_KERNELS, std::string>                 device_built_in_kernels;
    extern OCLM_EXPORT const device_info<CL_DEVICE_IMAGE_MAX_BUFFER_SIZE, ::size_t>               device_image_max_buffer_size;
    extern OCLM_EXPORT const device_info<CL_DEVICE_IMAGE_MAX_ARRAY_SIZE, ::size_t>                device_image_max_array_size;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PARENT_DEVICE, cl_device_id>                   device_parent_device;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PARTITION_MAX_SUB_DEVICES, cl_uint>            device_partition_max_sub_devices;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PARTITION_PROPERTIES, std::vector<cl_device_partition_property>> device_partition_properties;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PARTITION_AFFINITY_DOMAIN, cl_device_affinity_domain>    device_partition_affinity_domain;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PARTITION_TYPE, std::vector<cl_device_partition_property>>   device_partition_type;
    extern OCLM_EXPORT const device_info<CL_DEVICE_REFERENCE_COUNT, cl_uint>                      device_reference_count;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PRINTF_BUFFER_SIZE, ::size_t>                  device_printf_buffer_size;

    template <cl_device_type Type>
    struct OCLM_EXPORT device_type
        : info<
            ::cl_device_id
          , cl_device_type
          , ::clGetDeviceInfo
          , CL_DEVICE_TYPE
        >
    {
        template <typename T>
        bool operator()(T const & d, std::vector<T> & ds) const
        {
            if(Type == CL_DEVICE_TYPE_ALL)
            {
                return true;
            }
            if(Type == CL_DEVICE_TYPE_DEFAULT && ds.size() == 0)
            {
                return true;
            }
            return d.get(device_type<Type>()) == Type;
        }
    };

    template <cl_device_type Type>
    struct is_device_info<device_type<Type> >
        : boost::mpl::true_
    {};

}

#endif
