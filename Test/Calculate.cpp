#include <catch_amalgamated.hpp>
#include <BigInt.h>

TEST_CASE("计算功能") {
    BigInt b1 = 1;
    BigInt b2 = 2;
    BigInt b3 = 3;
    BigInt b21 = 21;
    SECTION("加法") {
        CHECK((b1 + b2 == 3));
        CHECK((b1 + b2 == b3));
        CHECK((b2 + b3 == 5));
        CHECK((b1 + b21 == 22));

    }
}