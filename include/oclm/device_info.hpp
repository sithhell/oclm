
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
    template <int Name>
    struct device_info
        : info<
            ::cl_device_id
          , std::string
          , ::clGetDeviceInfo
          , Name
        >
    {};

    template <typename>
    struct is_device_info
        : boost::mpl::false_
    {};

    template <int Name>
    struct is_device_info<device_info<Name> >
        : boost::mpl::true_
    {};

    extern OCLM_EXPORT const device_info<CL_DEVICE_MAX_COMPUTE_UNITS>               device_compute_units;
    extern OCLM_EXPORT const device_info<CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS>        device_max_work_item_dimensions;
    extern OCLM_EXPORT const device_info<CL_DEVICE_MAX_WORK_GROUP_SIZE>             device_max_work_group_size;
    extern OCLM_EXPORT const device_info<CL_DEVICE_MAX_WORK_ITEM_SIZES>             device_max_work_item_size;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR>     device_preferred_vector_width_char;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT>    device_preferred_vector_width_short;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT>      device_preferred_vector_width_int;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG>     device_preferred_vector_width_long;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT>    device_preferred_vector_width_float;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE>   device_preferred_vector_width_double;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF>     device_preferred_vector_width_half;
    extern OCLM_EXPORT const device_info<CL_DEVICE_MAX_CLOCK_FREQUENCY>             device_max_clock_frequency;
    extern OCLM_EXPORT const device_info<CL_DEVICE_ADDRESS_BITS>                    device_address_bits;
    extern OCLM_EXPORT const device_info<CL_DEVICE_MAX_READ_IMAGE_ARGS>             device_max_read_image_args;
    extern OCLM_EXPORT const device_info<CL_DEVICE_MAX_WRITE_IMAGE_ARGS>            device_max_write_image_args;
    extern OCLM_EXPORT const device_info<CL_DEVICE_MAX_MEM_ALLOC_SIZE>              device_max_mem_alloc_size;
    extern OCLM_EXPORT const device_info<CL_DEVICE_IMAGE2D_MAX_WIDTH>               device_image2d_max_width;
    extern OCLM_EXPORT const device_info<CL_DEVICE_IMAGE2D_MAX_HEIGHT>              device_image2d_max_height;
    extern OCLM_EXPORT const device_info<CL_DEVICE_IMAGE3D_MAX_WIDTH>               device_image3d_max_width;
    extern OCLM_EXPORT const device_info<CL_DEVICE_IMAGE3D_MAX_HEIGHT>              device_image3d_max_height;
    extern OCLM_EXPORT const device_info<CL_DEVICE_IMAGE3D_MAX_DEPTH>               device_image3d_max_depth;
    extern OCLM_EXPORT const device_info<CL_DEVICE_IMAGE_SUPPORT>                   device_image_support;
    extern OCLM_EXPORT const device_info<CL_DEVICE_MAX_PARAMETER_SIZE>              device_max_parameter_size;
    extern OCLM_EXPORT const device_info<CL_DEVICE_MAX_SAMPLERS>                    device_max_samplers;
    extern OCLM_EXPORT const device_info<CL_DEVICE_MEM_BASE_ADDR_ALIGN>             device_mem_base_addr_align;
    extern OCLM_EXPORT const device_info<CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE>        device_min_data_type_align_size;
    extern OCLM_EXPORT const device_info<CL_DEVICE_SINGLE_FP_CONFIG>                device_single_fp_config;
    extern OCLM_EXPORT const device_info<CL_DEVICE_GLOBAL_MEM_CACHE_TYPE>           device_global_mem_chache_config;
    extern OCLM_EXPORT const device_info<CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE>       device_global_mem_cacheline_config;
    extern OCLM_EXPORT const device_info<CL_DEVICE_GLOBAL_MEM_CACHE_SIZE>           device_global_mem_cache_size;
    extern OCLM_EXPORT const device_info<CL_DEVICE_GLOBAL_MEM_SIZE>                 device_global_mem_size;
    extern OCLM_EXPORT const device_info<CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE>        device_max_constant_buffer_size;
    extern OCLM_EXPORT const device_info<CL_DEVICE_MAX_CONSTANT_ARGS>               device_max_constant_args;
    extern OCLM_EXPORT const device_info<CL_DEVICE_LOCAL_MEM_TYPE>                  device_local_mem_type;
    extern OCLM_EXPORT const device_info<CL_DEVICE_LOCAL_MEM_SIZE>                  device_local_mem_size;
    extern OCLM_EXPORT const device_info<CL_DEVICE_ERROR_CORRECTION_SUPPORT>        device_error_correction_support;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PROFILING_TIMER_RESOLUTION>      device_profiling_timer_resolution;
    extern OCLM_EXPORT const device_info<CL_DEVICE_ENDIAN_LITTLE>                   device_endian_little;
    extern OCLM_EXPORT const device_info<CL_DEVICE_AVAILABLE>                       device_available;
    extern OCLM_EXPORT const device_info<CL_DEVICE_COMPILER_AVAILABLE>              device_compiler_available;
    extern OCLM_EXPORT const device_info<CL_DEVICE_EXECUTION_CAPABILITIES>          device_execution_capabilities;
    extern OCLM_EXPORT const device_info<CL_DEVICE_QUEUE_PROPERTIES>                device_queue_properties;
    extern OCLM_EXPORT const device_info<CL_DEVICE_NAME>                            device_name;
    extern OCLM_EXPORT const device_info<CL_DEVICE_VENDOR>                          device_vendor;
    extern OCLM_EXPORT const device_info<CL_DRIVER_VERSION>                         device_driver_version;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PROFILE>                         device_profile;
    extern OCLM_EXPORT const device_info<CL_DEVICE_VERSION>                         device_version;
    extern OCLM_EXPORT const device_info<CL_DEVICE_EXTENSIONS>                      device_extensions;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PLATFORM>                        device_platform;
    extern OCLM_EXPORT const device_info<CL_DEVICE_DOUBLE_FP_CONFIG>                device_double_fp_config;
    extern OCLM_EXPORT const device_info<CL_DEVICE_HOST_UNIFIED_MEMORY>             device_host_unified_memory;
    extern OCLM_EXPORT const device_info<CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR>        device_native_vector_width_char;
    extern OCLM_EXPORT const device_info<CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT>       device_native_vector_width_short;
    extern OCLM_EXPORT const device_info<CL_DEVICE_NATIVE_VECTOR_WIDTH_INT>         device_native_vector_width_int;
    extern OCLM_EXPORT const device_info<CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG>        device_native_vector_width_long;
    extern OCLM_EXPORT const device_info<CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT>       device_native_vector_width_float;
    extern OCLM_EXPORT const device_info<CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE>      device_native_vector_width_double;
    extern OCLM_EXPORT const device_info<CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF>        device_native_vector_width_half;
    extern OCLM_EXPORT const device_info<CL_DEVICE_OPENCL_C_VERSION>                device_opencl_c_version;
    extern OCLM_EXPORT const device_info<CL_DEVICE_LINKER_AVAILABLE>                device_linker_available;
    extern OCLM_EXPORT const device_info<CL_DEVICE_BUILT_IN_KERNELS>                device_built_in_kernels;
    extern OCLM_EXPORT const device_info<CL_DEVICE_IMAGE_MAX_BUFFER_SIZE>           device_image_max_buffer_size;
    extern OCLM_EXPORT const device_info<CL_DEVICE_IMAGE_MAX_ARRAY_SIZE>            device_image_max_array_size;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PARENT_DEVICE>                   device_parent_device;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PARTITION_MAX_SUB_DEVICES>       device_partition_max_sub_devices;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PARTITION_PROPERTIES>            device_partition_properties;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PARTITION_AFFINITY_DOMAIN>       device_partition_affinity_domain;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PARTITION_TYPE>                  device_partition_type;
    extern OCLM_EXPORT const device_info<CL_DEVICE_REFERENCE_COUNT>                 device_reference_count;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PREFERRED_INTEROP_USER_SYNC>     device_prefered_interop_user_sync;
    extern OCLM_EXPORT const device_info<CL_DEVICE_PRINTF_BUFFER_SIZE>              device_printf_buffer_size;

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
