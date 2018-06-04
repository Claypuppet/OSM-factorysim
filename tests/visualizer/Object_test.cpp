/*
 * Copyright (c) 2016 Joost Kraaijeveld. See license.txt for details.
 * For information, bug reports and additions send an e-mail to UnitTest@Askesis.nl.
 *
 * Author: jkr
 */


// http://www.boost.org/doc/libs/1_60_0/libs/test/doc/html/boost_test/adv_scenarios/shared_lib_customizations/entry_point.html
//#define BOOST_TEST_MODULE ObjectTestModule
#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_NO_MAIN
// Header only
//#include <boost/test/included/unit_test.hpp>
// Static library
//#include <boost/test/unit_test.hpp>
// Dynamic library
#include <boost/test/unit_test.hpp>

//Start aangeven van een groepje test cases.
BOOST_AUTO_TEST_SUITE( VisualiserTests1 )

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( VisualiserTests2 )

BOOST_AUTO_TEST_SUITE_END()
