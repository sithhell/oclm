
//  Copyright (c) 2012 Julian Hornich
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <oclm/command_queue.hpp>
#include <oclm/context.hpp>

#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>

namespace oclm
{
    command_queue::command_queue( const oclm::queue_selector qSelector )
    {
        platform    chosen_platform;
        device      chosen_device;

        if ( qSelector == default_ )
        {
            chosen_platform = oclm::get_platform();
            chosen_device   = chosen_platform.devices.at(0);
        }
        else if ( qSelector == interactive_ )
        {
            std::vector< platform > available_platforms = oclm::get_platforms();
            std::string input;

            // let the user choose the platform
            while ( true )
            {
                // if there is only one platform available, we will automatically select it
                if (available_platforms.size() == 1)
                {
                    chosen_platform = available_platforms.at(0);

                    std::cout << "\nAvailable platform:\n\t" << chosen_platform.get(oclm::platform_name) << std::endl;

                    break;
                }

                std::cout << "\nAvailable platforms: ";

                for( size_t i(0); i < available_platforms.size(); ++i )
                    std::cout << "\n\t" << i << ") " << available_platforms.at(i).get( oclm::platform_name );

                // perhaps we want an option for more information about platforms here too

                std::cout << "\n\t" << "q) Quit\n";
                std::cout << "\nPlease choose your desired platform: ";

                std::cin >> input;

                input.resize(1);

                if ( input == "q" || input == "Q" )
                {
                    std::cout << "Exiting..." << std::endl;
                    exit(1);
                }
                else if ( input[0] >= '0' && input[0] <= '9' ) // TODO better ascii number detection (more than one digit)
                {
                    size_t i( static_cast< size_t >( atoi(&(input[0])) ) );

                    if ( i >= available_platforms.size() )
                        continue;

                    chosen_platform = available_platforms.at(i);
                    break;
                }
            }

            // let the user choose the device
            while ( true )
            {
                // if there is only one device available for the platform, we will automatically select it
                if (chosen_platform.devices.size() == 1)
                {
                    chosen_device = chosen_platform.devices.at(0);

                    std::cout << "\nAvailable device:\n\t" << chosen_device.get(oclm::device_name) << std::endl;

                    break;
                }

                std::cout << "\nAvailable devices: ";

                for( size_t i(0); i < chosen_platform.devices.size(); ++i )
                    std::cout << "\n\t" << i << ") " << chosen_platform.devices.at(i).get( oclm::device_name );

                // perhaps we want an option for more information about platforms here too

                std::cout << "\n\t" << "q) Quit\n";
                std::cout << "\nPlease choose your desired device: ";

                std::cin >> input;

                input.resize(1);

                if ( input == "q" || input == "Q" )
                {
                    std::cout << "Exiting..." << std::endl;
                    exit(1);
                }
                else if ( input[0] >= '0' && input[0] <= '9' ) // TODO better ascii number detection (more than one digit)
                {
                    std::cout << input << std::endl;

                    size_t i( static_cast< size_t >( atoi(&(input[0])) ) );

                    if ( i >= chosen_platform.devices.size() )
                        continue;

                    // std::cout << "Chosen Platform: " << available_platforms.at(i).get( oclm::platform_name ) << "\n";
                    chosen_device = chosen_platform.devices.at(i);
                    break;
                }
            }
        }

        ctx_ = create_context(chosen_device);
        d_ = chosen_device;

        cq_ = create(ctx_, d_);
    }
}
