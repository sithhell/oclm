
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <oclm/oclm.hpp>

#include <iterator>
#include <iostream>
#include <stdexcept>

TEST_CASE( "platform_manager - access platforms", "Access platforms and check for uniqueness")
{
	typedef std::vector< oclm::platform >::const_iterator pIter;

	REQUIRE_NOTHROW( oclm::get_platforms() );

	pIter p1( ++(oclm::get_platforms().begin()) );
	pIter p2( oclm::get_platforms().begin() );

	while ( i1 != oclm::get_platforms().end() )
	{
		// std::cout << i1->get( oclm::platform_name ) << " - " << i2->get( oclm::platform_name ) << std::endl;
		REQUIRE( static_cast< bool >( !( *p1 == *p2 ) ) );
		++p1;
		++p2;
	}
}
