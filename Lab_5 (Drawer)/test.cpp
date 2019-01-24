#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "drawer_header.h"

template<>
std::string printNames<std::pair<std::string, double>>(std::pair<std::string, double> value) {
    return value.first + '\n';
}

TEST_CASE("case_1") {
    std::stringstream test_cin;
    test_cin << "1000x500";

    std::pair<int, int> m;
    m.first = 0;
    m.second = 0;

    m = find_canvas(test_cin);

    REQUIRE(m.first == 1000);
    REQUIRE(m.second == 500);
}

TEST_CASE("case_2") {
    std::stringstream test_cin_1;
    std::stringstream test_cin_2;

    test_cin_1 << printNames(Named("Unknown"), Named("Unknown"));

    test_cin_2 << totalArea(Circle(1), Rectangle(4,5), Triangle(0,0,0,5,2,0));

    REQUIRE(test_cin_1.str() == "Unknown.1\n"
                                "Unknown.2\n");
    REQUIRE(test_cin_2.str() == "28.14");
}

TEST_CASE("case_3") {
    std::stringstream test_cin_1;
    std::stringstream test_cin_2;

    test_cin_1 << printNames(Circle(2), Circle(3));
    test_cin_2 << printNames(Circle(2), Circle(2), Circle(3));

    REQUIRE(test_cin_2.str() == "Circle.1\n"
                                "Circle.2\n"
                                "Circle.3\n");
}

TEST_CASE("case_4") {
    std::stringstream test_cin_1;
    test_cin_1 << totalArea(Circle(1), Circle(1));

    REQUIRE(test_cin_1.str() == "6.28");
}

TEST_CASE("case_5") {
    std::stringstream test_cin;
    std::stringstream test_cin_1;

    test_cin << "400x400\n"
                "Circle(150) [0, 0] {red}\n"
                "Circle(190) [0, 0] {green}\n"
                "Circle(90) [0, 0] {yellow}\n"
                "Rectangle(100,100)[0,0]{red}\n"
                "Triangle(-100,0,0,-100)[0,0]{pink}\n"
                "Triangle(100,0,0,100)[0,0]{pink}";

    std::pair<int, int> canvas_w_h = find_canvas(test_cin);

    Drawer::create_image(canvas_w_h);

    observing_shapes(test_cin);

    test_cin_1 << totalArea(Circle(490));

    REQUIRE(test_cin_1.str() == "753914");
}