#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "battle_header.h"

TEST_CASE("case_1") {
    std::string field = create_table();
    int m = 0;
    for (int i = 0; i < field.size(); i++) {
        if (field[i] == '1') {
            m = 1;
            break;
        }
    }

    REQUIRE(m == 1);
}