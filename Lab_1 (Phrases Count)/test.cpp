#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "functions.h"

TEST_CASE("case_1") {
    int amount = 2, repetitions = 2;
    int argc = 4;

    char **argv = new char *[argc];
    for (int i = 0; i < argc; i++) {
        argv[i] = new char[2];
    }

    strcpy(argv[1], "-n");
    strcpy(argv[2], "6");
    strcpy(argv[3], "-");

    input_check(argc, argv, amount, repetitions, std::cout);

    REQUIRE(amount == 6);
    REQUIRE(repetitions == 2);
}

TEST_CASE("case_2") {
    int amount = 2, repetitions = 2, argc = 2;

    char **argv = new char *[argc];
    for (int i = 0; i < argc; i++) {
        argv[i] = new char[2];
    }

    strcpy(argv[1], "-");

    input_check(argc, argv, amount, repetitions, std::cout);

    REQUIRE(amount == 2);
    REQUIRE(repetitions == 2);
}

TEST_CASE("case_3") {
    int amount = 2;

    std::stringstream test_cin;
    test_cin << "one two three four";

    std::vector<std::pair<std::string, int>> phrases = make_phrases(amount, test_cin);

    std::string new_1 = phrases[0].first;
    std::string new_2 = phrases[1].first;
    std::string new_3 = phrases[2].first;

    REQUIRE(new_1 == "one two");
    REQUIRE(new_2 == "two three");
    REQUIRE(new_3 == "three four");
}

TEST_CASE("case_4") {
    int amount = 6;

    std::stringstream test_cin;
    test_cin << "We wish you a merry Christmas "
                "And a happy new year "
                "We wish you a merry Christmas";

    std::vector<std::pair<std::string, int>> phrases = make_phrases(amount, test_cin);

    std::string new_1 = phrases[0].first;
    int am_1 = phrases[0].second;

    REQUIRE(new_1 == "We wish you a merry Christmas");
    REQUIRE(am_1 == 2);
}

TEST_CASE("case_5") {
    int amount = -1, repetitions = -2, argc = 6;

    char **argv = new char *[argc];
    for (int i = 0; i < argc; i++) {
        argv[i] = new char[2];
    }

    strcpy(argv[1], "-n");
    strcpy(argv[2], "-1");
    strcpy(argv[3], "-m");
    strcpy(argv[4], "-2");
    strcpy(argv[5], "-");

    std::stringstream test_cout;
    int m = input_check(argc, argv, amount, repetitions, test_cout);
    REQUIRE(test_cout.str() == "Incorrect input data\n");
    REQUIRE(m == 1);
}

TEST_CASE("case_6") {
    int amount = 3, repetitions = 2, argc = 6;

    char **argv = new char *[argc];
    for (int i = 0; i < argc; i++) {
        argv[i] = new char[2];
    }

    strcpy(argv[1], "-n");
    strcpy(argv[2], "3");
    strcpy(argv[3], "-m");
    strcpy(argv[4], "2");
    strcpy(argv[5], "-");

    std::stringstream test_cin;
    test_cin << "the quick brown fox the quick brown";

    std::vector<std::pair<std::string, int>> phrases = make_phrases(amount, test_cin);

    std::stringstream test_cout;
    print_res(phrases, repetitions, test_cout);

    REQUIRE(test_cout.str() == "the quick brown(2)\n");
}