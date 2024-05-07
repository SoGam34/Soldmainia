/*
 * test_Timer.cpp
 *
 *  Created on: 07.05.2024
 *      Author: random
 */

#define BOOST_TEST_MODULE Mein erster Boost Test
#include <boost/test/included/unit_test.hpp>
#include "../Timer.h"

BOOST_AUTO_TEST_SUITE( timer )

BOOST_AUTO_TEST_CASE( einzelTimer )
{
  Timer t = Timer();

  t.neuerTimer(3);

  t.aktTimer();
  BOOST_TEST(t.checkTimerAbgelaufen() == false);

  t.aktTimer();
  BOOST_TEST(t.checkTimerAbgelaufen() == false);

  t.aktTimer();
  BOOST_TEST(t.checkTimerAbgelaufen() == true);

  t.aktTimer();
  BOOST_TEST(t.checkTimerAbgelaufen() == true);
}

BOOST_AUTO_TEST_CASE( test_case2 )
{
  BOOST_TEST_REQUIRE( 1 == 2 );
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE( test_suite2 )

BOOST_AUTO_TEST_CASE( test_case3 )
{
  BOOST_TEST( true );
}

BOOST_AUTO_TEST_CASE( test_case4 )
{
  BOOST_TEST( true );
}

BOOST_AUTO_TEST_SUITE_END()



