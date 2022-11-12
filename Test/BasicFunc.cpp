#include <catch_amalgamated.hpp>
#include <BigInt.h>

TEST_CASE("基本功能测试") {

    SECTION("BigInt 转 字符串") {
        SECTION("0") {
            BigInt t = 0;
            REQUIRE(t.to_string() == "0");
        }

        SECTION("123") {
            BigInt t = 1234567890;
            REQUIRE(t.to_string() == "1234567890");
        }


        SECTION("1234") {
            BigInt t = 1234;
            REQUIRE(t.to_string() == "1234");
        }
    }

}