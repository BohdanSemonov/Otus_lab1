#define BOOST_TEST_MODULE test_version

#include "lib.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_version)

BOOST_AUTO_TEST_CASE(test_valid_version)
{
    BOOST_TEST_REQUIRE(boost::unit_test::framework::master_test_suite().argc == 3);
    BOOST_TEST_REQUIRE(boost::unit_test::framework::master_test_suite().argv[1] == "--version");

    BOOST_TEST(std::to_string(version()) == boost::unit_test::framework::master_test_suite().argv[2]);
}

}
