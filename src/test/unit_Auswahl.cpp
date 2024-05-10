/**
 * @file unit_Auswahl.cpp
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
#include "../Auswahl.h"
#include "../Data/Data.h"
#include <memory> 

BOOST_AUTO_TEST_SUITE( auswahl )

BOOST_AUTO_TEST_CASE( suche_Einsezbar )
{ 
    Data d = Data();

    Auswahl a = Auswahl(d);

    d.hinzufügenEinheit()
}

BOOST_AUTO_TEST_SUITE_END()
