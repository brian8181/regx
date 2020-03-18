#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "utility.h"
#include <string>

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}

TEST_CASE("Replace All")
{
    std::string s = "Hello BEFORE this [BEFORE] <BEFORE> BEFORE";
    replace_all(s, "BEFORE", "AFTER");
    REQUIRE( s == "Hello AFTER this [AFTER] <AFTER> AFTER" );
}

// g++ utility.cpp unit_test.cpp -o unit_test