
//  Copyright (c) 2012 Julian Hornich
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <oclm/oclm.hpp>

TEST_CASE( "platform_manager", "Access platforms")
{
	REQUIRE( oclm::get_platforms().size() != 0 );
	REQUIRE( static_cast< bool >( oclm::get_platform() != static_cast< cl_platform_id >( 0 ) ) );
}

TEST_CASE( "platform", "Test available operators for platforms" )
{
	oclm::platform p1, p2;
	REQUIRE_NOTHROW( p1 = oclm::get_platforms().front() );
	REQUIRE_NOTHROW( p2 = p1 );
	REQUIRE( static_cast< bool >( p1 == p2 ) );
}

TEST_CASE( "platform_info", "Test correct platform_info behavior" )
{
	REQUIRE( oclm::get_platform().get( oclm::platform_name ).empty() == false );
	REQUIRE( oclm::get_platform().get( oclm::platform_vendor ).empty() == false );
	REQUIRE( oclm::get_platform().get( oclm::platform_profile ).empty() == false );
	REQUIRE( oclm::get_platform().get( oclm::platform_version ).empty() == false );
	REQUIRE( oclm::get_platform().get( oclm::platform_extensions ).empty() == false );
}
