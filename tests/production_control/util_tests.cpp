
#include <boost/test/unit_test.hpp>

#include <utils/RandomHelper.h>

BOOST_AUTO_TEST_SUITE(UtilsTests);

BOOST_AUTO_TEST_CASE(TestRandomHelper){

  utils::SignedUniformDistribution sDistribution(-5000, 500);
  utils::UnsignedUniformDistribution uDistribution(0, 1000);
  utils::NormalDistribution nDistribution(500, 10);
  BOOST_CHECK_NO_THROW(utils::RandomHelper::getRandom(sDistribution));
  BOOST_CHECK_NO_THROW(utils::RandomHelper::getRandom(uDistribution));
  BOOST_CHECK_NO_THROW(utils::RandomHelper::getRandom(nDistribution));

  utils::RandomHelper::getInstance().setSeed(400);
  BOOST_CHECK_EQUAL(utils::RandomHelper::getRandom(uDistribution), 669);
  BOOST_CHECK_EQUAL(utils::RandomHelper::getRandom(uDistribution), 792);
  BOOST_CHECK_EQUAL(utils::RandomHelper::getRandom(uDistribution), 226);
  BOOST_CHECK_EQUAL(utils::RandomHelper::getRandom(uDistribution), 188);
  BOOST_CHECK_EQUAL(utils::RandomHelper::getRandom(uDistribution), 860);
}


BOOST_AUTO_TEST_SUITE_END();