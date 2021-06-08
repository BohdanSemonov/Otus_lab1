#define BOOST_TEST_MODULE test_version

#include "lib.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_version)

BOOST_AUTO_TEST_CASE(test_valid_version)
{
    std::ifstream f("ver_tst");
    std::string ver_str;
    
    if (f.is_open())
    {
        getline(f, ver_str);
        BOOST_TEST(std::to_string(version()) == ver_str);    
    }
}

}
