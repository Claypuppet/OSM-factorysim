/*
 * Copyright (c) 2016 Joost Kraaijeveld. See license.txt for details.
 * For information, bug reports and additions send an e-mail to UnitTest@Askesis.nl.
 *
 * Author: jkr
 */

#include "Object.hpp"

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
BOOST_AUTO_TEST_SUITE( MachineControlTests1 )

//Een voorbeeld test case.
BOOST_AUTO_TEST_CASE( MachineControlTest1 ){

    //Test slaagt als mijnFunctie() geen throw gooit.
    BOOST_CHECK_NO_THROW(Object());
    BOOST_CHECK_NO_THROW(Object("test"));
}

BOOST_AUTO_TEST_CASE( MachineControlTest2 ) {
	Object o1("Piet");
	Object o2("Piet");
    BOOST_REQUIRE_EQUAL( o1, o2 );

    //Stopt deze test case en toont de meegegeven tekst.
//    BOOST_FAIL( "Test is still not ready yet" );
}
//Einde van het groepje test cases aangeven.
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( MachineControlTests1 )

BOOST_AUTO_TEST_CASE( MachineControlTest3 ){
    //Passeert wanneer mijnBoolFunctie() true retourneert.
    BOOST_CHECK( mijnBoolFunctie() );
}

BOOST_AUTO_TEST_CASE( MachineControlTest4 ){
	Object o1("Kees");
	Object o2("Piet");
	BOOST_CHECK_LT( o1, o2 );

}
BOOST_AUTO_TEST_SUITE_END()
