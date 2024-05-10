/**
 * @file unit_Timer.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#define BOOST_TEST_MODULE timer
#include <boost/test/included/unit_test.hpp>
#include "../Timer.h"

BOOST_AUTO_TEST_SUITE( timer )

BOOST_AUTO_TEST_CASE( einzelTimer )
{
	Timer t = Timer();

	BOOST_TEST(t.getTimerstand() == 0);
	BOOST_TEST(t.checkTimerAbgelaufen() == true);

	t.neuerTimer(3);
	BOOST_TEST(t.getTimerstand() == 3);

	t.aktTimer();
	BOOST_TEST(t.getTimerstand() == 2);
	BOOST_TEST(t.checkTimerAbgelaufen() == false);

	t.aktTimer();
	BOOST_TEST(t.getTimerstand() == 1);
	BOOST_TEST(t.checkTimerAbgelaufen() == false);

	t.aktTimer();
	BOOST_TEST(t.getTimerstand() == 0);
	BOOST_TEST(t.checkTimerAbgelaufen() == true);

	t.aktTimer();
	BOOST_TEST(t.getTimerstand() == -1);
	BOOST_TEST(t.checkTimerAbgelaufen() == false);
}

BOOST_AUTO_TEST_CASE( einzelTimer )
{
	Timer t = Timer();

	BOOST_TEST(t.getTimerstandMitID(1).has_value() == false);
	BOOST_TEST(t.checkTimerAbgelaufenMitID(1) == false);

	t.neuerTimerMitID(1, 3);
	BOOST_TEST(t.getTimerstandMitID(1) == 3);

	t.aktTimer();
	BOOST_TEST(t.getTimerstandMitID(1) == 2);
	BOOST_TEST(t.checkTimerAbgelaufenMitID(1) == false);

	t.aktTimer();
	BOOST_TEST(t.getTimerstandMitID(1) == 1);
	BOOST_TEST(t.checkTimerAbgelaufenMitID(1) == false);

	t.aktTimer();
	BOOST_TEST(t.getTimerstandMitID(1) == 0);
	BOOST_TEST(t.checkTimerAbgelaufenMitID(1) == true);

	t.aktTimer();
	BOOST_TEST(t.getTimerstandMitID(1) == -1);
	BOOST_TEST(t.checkTimerAbgelaufenMitID(1) == false);
}

BOOST_AUTO_TEST_SUITE_END()
