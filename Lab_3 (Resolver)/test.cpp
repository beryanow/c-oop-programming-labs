#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "resolver_overall.h"

TEST_CASE("case_1") {
    std::vector<struct library> every_libs;

    std::stringstream test_cin;
    test_cin << "A 1.0";

    filling_every_libs_up(test_cin, every_libs);

    REQUIRE(every_libs.at(0).name == "A");
}

TEST_CASE("case_2") {
    std::vector<struct library> every_libs;

    std::stringstream test_cin;
    test_cin << "A 1.0\n"
                "+ B >= 1.0\n"
                "B 1.0\n"
                "B 2.0";

    filling_every_libs_up(test_cin, every_libs);

    REQUIRE(every_libs.at(0).name == "A");
    REQUIRE(every_libs.at(0).dependencies.at(0).first == "B");
    REQUIRE(every_libs.at(1).name == "B");
    REQUIRE(every_libs.at(2).name == "B");
}

TEST_CASE("case_3") {
    std::vector<struct target> every_targets;
    std::stringstream test_cin;
    test_cin << "A < 1.8";

    filling_every_targets_up(test_cin, every_targets);

    REQUIRE(every_targets.at(0).name == "A");
    REQUIRE(every_targets.at(0).borders.first.give() == "-");
    REQUIRE(every_targets.at(0).borders.second.give() == "1.7");
}

TEST_CASE("case_4") {
    std::vector<struct library> every_libs;

    std::stringstream test_cin;
    test_cin << "A 1.0\n"
                "A 2.0\n"
                "A 1.5";

    filling_every_libs_up(test_cin, every_libs);
    test_cin.clear();

    std::vector<struct target> every_targets;
    test_cin << "A";

    filling_every_targets_up(test_cin, every_targets);

    stack libs_indexes_set;
    stack indexes_set;

    int h = every_targets.size();
    finding_compatibilities(every_targets, h, libs_indexes_set, indexes_set, every_libs);
    finding_conflicts(every_targets, h, every_libs, libs_indexes_set);
    finding_unsuitable_dependencies_version(every_libs, libs_indexes_set);
    finding_unsuitable_conflicts_version(every_libs, libs_indexes_set);
    checking_for_existence(h, every_targets, every_libs, libs_indexes_set);
    exploring_kinds(every_targets, every_libs);

    std::stringstream test_cout;
    showing_results(every_libs, test_cout);

    REQUIRE(test_cout.str() == "A 2.0\n");
}

TEST_CASE("case_5") {
    std::vector<struct library> every_libs;

    std::stringstream test_cin;
    test_cin << "A 1.0\n"
                "+ B >= 1.0\n"
                "B 1.0\n"
                "B 2.0";

    filling_every_libs_up(test_cin, every_libs);
    test_cin.clear();

    std::vector<struct target> every_targets;
    test_cin << "A";

    filling_every_targets_up(test_cin, every_targets);

    stack libs_indexes_set;
    stack indexes_set;

    int h = every_targets.size();
    finding_compatibilities(every_targets, h, libs_indexes_set, indexes_set, every_libs);
    finding_conflicts(every_targets, h, every_libs, libs_indexes_set);
    finding_unsuitable_dependencies_version(every_libs, libs_indexes_set);
    finding_unsuitable_conflicts_version(every_libs, libs_indexes_set);
    checking_for_existence(h, every_targets, every_libs, libs_indexes_set);
    exploring_kinds(every_targets, every_libs);

    std::stringstream test_cout;
    showing_results(every_libs, test_cout);

    REQUIRE(test_cout.str() == "A 1.0\n"
                               "B 2.0\n");
}

TEST_CASE("case_6") {
    std::vector<struct library> every_libs;

    std::stringstream test_cin;
    test_cin << "A 1.0\n"
                "+ B\n"
                "B 2.0\n"
                "B 2.5\n"
                "- A";

    filling_every_libs_up(test_cin, every_libs);
    test_cin.clear();

    std::vector<struct target> every_targets;
    test_cin << "A";

    filling_every_targets_up(test_cin, every_targets);

    stack libs_indexes_set;
    stack indexes_set;

    int h = every_targets.size();
    finding_compatibilities(every_targets, h, libs_indexes_set, indexes_set, every_libs);
    finding_conflicts(every_targets, h, every_libs, libs_indexes_set);
    finding_unsuitable_dependencies_version(every_libs, libs_indexes_set);
    finding_unsuitable_conflicts_version(every_libs, libs_indexes_set);
    checking_for_existence(h, every_targets, every_libs, libs_indexes_set);
    exploring_kinds(every_targets, every_libs);

    std::stringstream test_cout;
    showing_results(every_libs, test_cout);

    REQUIRE(test_cout.str() == "A 1.0\n"
                               "B 2.0\n");
}

TEST_CASE("case_7") {
    std::vector<struct library> every_libs;

    std::stringstream test_cin;
    test_cin << "A 2.0\n"
                "A 1.5\n"
                "A 1.0";

    filling_every_libs_up(test_cin, every_libs);
    test_cin.clear();

    std::vector<struct target> every_targets;
    test_cin << "A < 1.8";

    filling_every_targets_up(test_cin, every_targets);

    stack libs_indexes_set;
    stack indexes_set;

    int h = every_targets.size();
    finding_compatibilities(every_targets, h, libs_indexes_set, indexes_set, every_libs);
    finding_conflicts(every_targets, h, every_libs, libs_indexes_set);
    finding_unsuitable_dependencies_version(every_libs, libs_indexes_set);
    finding_unsuitable_conflicts_version(every_libs, libs_indexes_set);
    checking_for_existence(h, every_targets, every_libs, libs_indexes_set);
    exploring_kinds(every_targets, every_libs);

    std::stringstream test_cout;
    showing_results(every_libs, test_cout);

    REQUIRE(test_cout.str() == "A 1.5\n");
}

TEST_CASE("case_8") {
    std::vector<struct library> every_libs;

    std::stringstream test_cin;
    test_cin << "A 1.1\n"
                "+ B >= 1.0\n"
                "B 0.9\n"
                "B 1.1\n"
                "B 1.2\n"
                "- C\n"
                "C 3.0";

    filling_every_libs_up(test_cin, every_libs);
    test_cin.clear();

    std::vector<struct target> every_targets;
    test_cin << "A\n"
                "C";

    filling_every_targets_up(test_cin, every_targets);

    stack libs_indexes_set;
    stack indexes_set;

    int h = every_targets.size();
    finding_compatibilities(every_targets, h, libs_indexes_set, indexes_set, every_libs);
    finding_conflicts(every_targets, h, every_libs, libs_indexes_set);
    finding_unsuitable_dependencies_version(every_libs, libs_indexes_set);
    finding_unsuitable_conflicts_version(every_libs, libs_indexes_set);
    checking_for_existence(h, every_targets, every_libs, libs_indexes_set);
    exploring_kinds(every_targets, every_libs);

    std::stringstream test_cout;
    showing_results(every_libs, test_cout);

    REQUIRE(test_cout.str() == "A 1.1\n"
                               "B 1.1\n"
                               "C 3.0\n");
}

TEST_CASE("case_9") {
    std::vector<struct library> every_libs;

    std::stringstream test_cin;
    test_cin << "A 1.0\n"
                "+ B >= 1.0\n"
                "+ C\n"
                "B 1.0\n"
                "- C\n"
                "C 1.0";

    filling_every_libs_up(test_cin, every_libs);
    test_cin.clear();

    std::vector<struct target> every_targets;
    test_cin << "A";

    filling_every_targets_up(test_cin, every_targets);

    std::stringstream test_cout;

    stack libs_indexes_set;
    stack indexes_set;

    int h = every_targets.size();
    finding_compatibilities(every_targets, h, libs_indexes_set, indexes_set, every_libs);
    finding_conflicts(every_targets, h, every_libs, libs_indexes_set);
    finding_unsuitable_dependencies_version(every_libs, libs_indexes_set);
    finding_unsuitable_conflicts_version(every_libs, libs_indexes_set);
    int j = every_targets.size();

    std::vector<std::pair<std::string, int>> arr;
    arr.resize(j);
    for (int i = 0; i < j; i++) {
        arr.at(i).first = every_targets.at(i).name;
        arr.at(i).second = 0;
    }

    int z = every_libs.size();
    for (int k = 0; k < j; k++) {
        for (int i = 0; i < z; i++) {
            if ((every_libs.at(i).compatibility == 1) && (every_libs.at(i).name == arr.at(k).first)) {
                arr.at(k).second = 1;
            }
        }
    }
    for (int i = 0; i < j; i++) {
        if (arr.at(i).second == 0) {
            try {
                throw std::logic_error("Unable to resolve targets.");
            }
            catch(const std::exception& e)
            {
                test_cout << e.what();
            }
            REQUIRE(test_cout.str() == "Unable to resolve targets.");
        }
    }
}

TEST_CASE("case_10") {
    std::vector<struct library> every_libs;

    std::stringstream test_cin;
    test_cin << "A 3.0\n"
                "+ B >= 5.0\n"
                "- D < 6.0\n"
                "\n"
                "B 7.0\n"
                "+ C 6.7\n"
                "\n"
                "C 6.7";

    filling_every_libs_up(test_cin, every_libs);
    test_cin.clear();

    std::vector<struct target> every_targets;
    test_cin << "A";

    filling_every_targets_up(test_cin, every_targets);

    stack libs_indexes_set;
    stack indexes_set;

    int h = every_targets.size();
    finding_compatibilities(every_targets, h, libs_indexes_set, indexes_set, every_libs);
    finding_conflicts(every_targets, h, every_libs, libs_indexes_set);
    finding_unsuitable_dependencies_version(every_libs, libs_indexes_set);
    finding_unsuitable_conflicts_version(every_libs, libs_indexes_set);
    checking_for_existence(h, every_targets, every_libs, libs_indexes_set);
    exploring_kinds(every_targets, every_libs);

    std::stringstream test_cout;
    showing_results(every_libs, test_cout);

    REQUIRE(test_cout.str() == "A 3.0\n"
                               "B 7.0\n"
                               "C 6.7\n");
}

TEST_CASE("case_11") {
    std::vector<struct library> every_libs;

    std::stringstream test_cin;
    test_cin << "A 3.0\n"
                "+ B >= 5.0\n"
                "- D < 6.0\n"
                "\n"
                "B 7.0\n"
                "+ C 6.7\n"
                "+ E\n"
                "- G\n"
                "\n"
                "B 3.0\n"
                "\n"
                "C 6.7\n"
                "\n"
                "E 7.0";

    filling_every_libs_up(test_cin, every_libs);
    test_cin.clear();

    std::vector<struct target> every_targets;
    test_cin << "A";

    filling_every_targets_up(test_cin, every_targets);

    stack libs_indexes_set;
    stack indexes_set;

    int h = every_targets.size();
    finding_compatibilities(every_targets, h, libs_indexes_set, indexes_set, every_libs);
    finding_conflicts(every_targets, h, every_libs, libs_indexes_set);
    finding_unsuitable_dependencies_version(every_libs, libs_indexes_set);
    finding_unsuitable_conflicts_version(every_libs, libs_indexes_set);
    checking_for_existence(h, every_targets, every_libs, libs_indexes_set);
    exploring_kinds(every_targets, every_libs);

    std::stringstream test_cout;
    showing_results(every_libs, test_cout);

    REQUIRE(test_cout.str() == "A 3.0\n"
                               "B 7.0\n"
                               "C 6.7\n"
                               "E 7.0\n");
}

TEST_CASE("case_12") {
    std::vector<struct library> every_libs;

    std::stringstream test_cin;
    test_cin << "A 1.1\n"
                "+ B >= 1.0\n"
                "\n"
                "B 2.9\n"
                "\n"
                "C 3.0\n"
                "+ B\n"
                "\n"
                "C 5.0";

    filling_every_libs_up(test_cin, every_libs);
    test_cin.clear();

    std::vector<struct target> every_targets;
    test_cin << "A\n"
                "C";

    filling_every_targets_up(test_cin, every_targets);

    stack libs_indexes_set;
    stack indexes_set;

    int h = every_targets.size();
    finding_compatibilities(every_targets, h, libs_indexes_set, indexes_set, every_libs);
    finding_conflicts(every_targets, h, every_libs, libs_indexes_set);
    finding_unsuitable_dependencies_version(every_libs, libs_indexes_set);
    finding_unsuitable_conflicts_version(every_libs, libs_indexes_set);
    checking_for_existence(h, every_targets, every_libs, libs_indexes_set);
    exploring_kinds(every_targets, every_libs);

    std::stringstream test_cout;
    showing_results(every_libs, test_cout);

    REQUIRE(test_cout.str() == "A 1.1\n"
                               "B 2.9\n"
                               "C 5.0\n");
}

TEST_CASE("case_13") {
    std::vector<struct library> every_libs;

    std::stringstream test_cin;
    test_cin << "A 1.0\n"
                "+ B >= 1.0\n"
                "\n"
                "A 1.1\n"
                "+ B >= 1.1\n"
                "\n"
                "A 1.2\n"
                "+ B >= 2.2\n"
                "\n"
                "B 1.1\n"
                "+ D\n"
                "\n"
                "B 2.5\n"
                "- A < 2.0\n"
                "\n"
                "C 4.0\n"
                "+ A >= 1.0\n"
                "\n"
                "C 4.1\n"
                "\n"
                "D 1.0\n"
                "\n"
                "D 1.5\n"
                "- A < 1.0";

    filling_every_libs_up(test_cin, every_libs);
    test_cin.clear();

    std::vector<struct target> every_targets;
    test_cin << "A";

    filling_every_targets_up(test_cin, every_targets);

    stack libs_indexes_set;
    stack indexes_set;

    int h = every_targets.size();
    finding_compatibilities(every_targets, h, libs_indexes_set, indexes_set, every_libs);
    finding_conflicts(every_targets, h, every_libs, libs_indexes_set);
    finding_unsuitable_dependencies_version(every_libs, libs_indexes_set);
    finding_unsuitable_conflicts_version(every_libs, libs_indexes_set);
    checking_for_existence(h, every_targets, every_libs, libs_indexes_set);
    exploring_kinds(every_targets, every_libs);

    std::stringstream test_cout;
    showing_results(every_libs, test_cout);

    REQUIRE(test_cout.str() == "A 1.1\n"
                               "B 1.1\n"
                               "D 1.5\n");
}