#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "tritset.h"

TEST_CASE("case_1") {
    tritset a;
    a[0] = trit::t_true;

    REQUIRE(a[0] == trit::t_true);
}

TEST_CASE("case_2") {
    tritset a;
    a[0] = trit::t_true;
    a[0] = trit::t_false;
    a[0] = trit::t_unknown;

    REQUIRE(a[0] == trit::t_unknown);
}

TEST_CASE("case_3") {
    tritset a(1000);
    size_t length = a.capacity();

    REQUIRE(length >= 16 * 2 / 8 / sizeof(unsigned int));
}

TEST_CASE("case_4") {
    tritset a;
    unsigned int length = a.capacity();
    a[1000] = trit::t_unknown;

    REQUIRE(length == a.capacity());
}

TEST_CASE("case_5") {
    tritset a;
    unsigned int length = a.capacity();
    if (a[20000] == trit::t_true) {}

    REQUIRE(length == a.capacity());
}

TEST_CASE("case_6") {
    tritset a;
    unsigned int length = a.capacity();
    a[1000] = trit::t_true;

    REQUIRE(length < a.capacity());
}

TEST_CASE("case_7") {
    tritset a;
    a[1000] = trit::t_true;
    unsigned int length = a.capacity();
    a[1000000] = trit::t_unknown;
    a[100] = trit::t_false;

    REQUIRE(length == a.capacity());
}

TEST_CASE("case_8") {
    tritset a;
    a[1000] = trit::t_true;
    unsigned int length = a.capacity();
    a[1000000] = trit::t_unknown;
    a[100] = trit::t_false;
    a.shrink();

    REQUIRE(length > a.capacity());
}

TEST_CASE("case_9") {
    tritset a(1000);
    a[0] = trit::t_true;
    tritset b(2000);
    b[0] = trit::t_false;
    tritset c = a & b;

    REQUIRE(c.capacity() == b.capacity());
}

TEST_CASE("case_10") {
    tritset a;
    a[0] = trit::t_true;
    a[1] = trit::t_true;
    a[5] = trit::t_true;
    a[7] = trit::t_true;
    a[8] = trit::t_true;

    unsigned int amount = a.cardinality(trit::t_true);

    REQUIRE(amount == 5);
}

TEST_CASE("case_11") {
    tritset a;
    a[0] = trit::t_true;
    a[1] = trit::t_true;
    a[5] = trit::t_true;
    a[7] = trit::t_true;
    a[8] = trit::t_true;
    a[4] = trit::t_true;

    unsigned int amount = a.cardinality(trit::t_unknown);

    REQUIRE(amount == 2);
}

TEST_CASE("case_12") {
    tritset a;
    a[0] = trit::t_true;
    a[1] = trit::t_true;
    a[5] = trit::t_true;
    a[7] = trit::t_true;
    a[8] = trit::t_true;
    a[4] = trit::t_true;

    std::unordered_map<trit, int> map_test = a.cardinality();

    REQUIRE(map_test[trit::t_false] == 0);
    REQUIRE(map_test[trit::t_unknown] == 2);
    REQUIRE(map_test[trit::t_true] == 6);
}

TEST_CASE("case_13") {
    tritset a;
    a[0] = trit::t_true;
    a[1] = trit::t_true;
    a[5] = trit::t_true;
    a[7] = trit::t_true;
    a[8] = trit::t_true;
    a[3] = trit::t_true;
    a[2] = trit::t_true;
    a[16] = trit::t_true;

    a.trim(1);

    REQUIRE(a.capacity() == 1);
}

TEST_CASE("case_14") {
    tritset a;
    a[0] = trit::t_true;
    a[1] = trit::t_true;
    a[5] = trit::t_true;
    a[7] = trit::t_true;
    a[8] = trit::t_true;
    a[3] = trit::t_true;
    a[2] = trit::t_true;
    a[16] = trit::t_true;

    a.trim(3);

    REQUIRE(a[5] == trit::t_unknown);
}

TEST_CASE("case_15") {
    tritset a;
    a[0] = trit::t_true;
    a[1] = trit::t_true;
    a[5] = trit::t_true;
    a[7] = trit::t_true;
    a[8] = trit::t_true;
    a[3] = trit::t_true;
    a[2] = trit::t_true;
    a[16] = trit::t_true;

    unsigned int m = a.length();

    REQUIRE(m == 16);
}

TEST_CASE("case_16") {
    tritset a, b, c;
    a[0] = trit::t_true;
    b[0] = trit::t_false;

    c = a & b;

    REQUIRE(c[0] == trit::t_false);
}

TEST_CASE("case_17") {
    tritset a, b, c;
    a[0] = trit::t_true;
    a[0] = trit::t_unknown;
    b[0] = trit::t_false;

    c = a | b;

    REQUIRE(c[0] == trit::t_unknown);
}

TEST_CASE("case_18") {
    tritset a, b;
    a[0] = trit::t_true;
    b[0] = trit::t_false;

    a &= b;

    REQUIRE(a[0] == trit::t_false);
}

TEST_CASE("case_19") {
    tritset a, b;
    a[0] = trit::t_true;
    a[0] = trit::t_unknown;
    b[0] = trit::t_false;

    a |= b;

    REQUIRE(a[0] == trit::t_unknown);
}

TEST_CASE("case_20") {
    tritset a{trit::t_true, trit::t_unknown, trit::t_false};

    REQUIRE(a[0] == trit::t_true);
    REQUIRE(a[2] == trit::t_false);
}

TEST_CASE("case_21") {
    tritset a{trit::t_true, trit::t_unknown, trit::t_false};

    REQUIRE(a[0] == trit::t_true);
    REQUIRE(a[2] == trit::t_false);
}

TEST_CASE("case_22") {
    std::stringstream test_cout;
    test_cout << trit::t_true;

    REQUIRE(test_cout.str() == "True");
}

TEST_CASE("case_23") {
    tritset a {trit::t_true, trit::t_unknown, trit::t_false};
    std::stringstream test_cout;
    test_cout << a;

    REQUIRE(test_cout.str() == "True Unknown False ");
}












