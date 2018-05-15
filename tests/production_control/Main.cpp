/*
 * Copyright (c) 2015-2016 Joost Kraaijeveld. See license.txt for details.
 * For information, bug reports and additions send an e-mail to ProjectTemplate@Askesis.nl.
 *
 * Author: jkr
 */


#include <iostream>

#include "silly_objects/Lib1.hpp"
#include "silly_objects/Object.hpp"

#define BOOST_TEST_MODULE ObjectTestModule
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>
#include <utils/Logger.h>

int main(int argc, char **argv) {
  utils::Logger::setEnabled(false);
  return boost::unit_test::unit_test_main(&init_unit_test, argc, argv);
}
