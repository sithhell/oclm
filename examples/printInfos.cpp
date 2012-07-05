
//  Copyright (c) 2012 Julian Hornich
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>

#include <oclm/oclm.hpp>

int main()
{
	typedef std::vector< oclm::platform >::const_iterator	pIter;
	typedef std::vector< oclm::device >::const_iterator		dIter;

	std::vector< oclm::platform > p( oclm::get_platforms() );;

	size_t nPlatform(0);

	for ( pIter i = p.begin(); i != p.end(); ++i )
	{
		std::cout << "Platform " << nPlatform++ << ":\n";
		std::cout << "\tNAME:\t\t" << i->get( oclm::platform_name ) << "\n";
		std::cout << "\tVENDOR:\t\t" << i->get( oclm::platform_vendor ) << "\n";
		std::cout << "\tVERSION:\t" << i->get( oclm::platform_version ) << "\n";
		std::cout << "\tPROFILE:\t" << i->get( oclm::platform_profile ) << "\n";
		std::cout << "\tEXTENSIONS:\t" << i->get( oclm::platform_extensions ) << "\n";

		size_t nDevices(0);

		const std::vector< oclm::device >& d( i->devices );

		for ( dIter j = d.begin(); j != d.end(); ++j )
		{
			std::cout << "Device " << nDevices++ << ":\n";
			std::cout << "\tNAME:\t\t" << j->get( oclm::device_name ) << "\n";
			std::cout << "\tVENDOR:\t\t" << j->get( oclm::device_vendor ) << "\n";
			std::cout << "\tVERSION:\t" << j->get( oclm::device_version ) << "\n";
			std::cout << "\tPROFILE:\t" << j->get( oclm::device_profile ) << "\n";
			std::cout << "\tEXTENSIONS:\t" << j->get( oclm::device_extensions ) << "\n";
		}

		std::cout << std::endl;
	}
}
