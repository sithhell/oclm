
//  Copyright (c) 2012 Julian Hornich
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <oclm/oclm.hpp>

TEST_CASE( "device operators", "Test available device operators")
{
	std::vector< oclm::device > devices;

	REQUIRE_NOTHROW( devices = oclm::get_platform().devices; )
	REQUIRE( devices.size() != 0 );

	oclm::device d1;

	REQUIRE_NOTHROW( d1 = devices[0] );
	REQUIRE( static_cast< bool >( d1 == devices[0] ) );
}

TEST_CASE( "device_info", "Test for correct device_info behavior" )
{
	std::vector< oclm::device > devices;

	REQUIRE_NOTHROW( devices = oclm::get_platform().devices; )
	REQUIRE( devices.size() != 0 );

	REQUIRE( devices[0].get( oclm::device_name ).empty() == false );
	REQUIRE( devices[0].get( oclm::device_vendor ).empty() == false );
	REQUIRE( devices[0].get( oclm::device_profile ).empty() == false );
	REQUIRE( devices[0].get( oclm::device_version ).empty() == false );
	REQUIRE( devices[0].get( oclm::device_extensions ).empty() == false );
}

TEST_CASE( "device_type", "Test for correct device_type behavior" )
{
	oclm::device d;

	REQUIRE_NOTHROW( d = oclm::get_device() );

	// REQUIRE( device_type( d ) == oclm::gpu );
}
