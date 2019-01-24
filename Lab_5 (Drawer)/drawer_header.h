#pragma once

#define pi 3.14

#include <iostream>
#include <cmath>
#include <sstream>
#include <vector>
#include <map>
#include <tuple>
#include <memory>

#include "bitmap/bitmap_image.hpp"

class Named;
class Colored;
class Segments;
class Shape;

std::pair<int, int> find_canvas(std::istream &stream);

std::shared_ptr<Shape> observing_rectangle(int &i, std::string shape_representative);
std::shared_ptr<Shape> observing_circle(int &i, std::string shape_representative);
std::shared_ptr<Shape> observing_triangle(int &i, std::string shape_representative);

void observing_shapes(std::istream &stream);

struct Color { ;
    int r, g, b;
    std::string defined_color;
};

class Named {
public:
    static std::vector<std::pair<std::string, int>> arr;
    static std::vector<std::pair<std::string, double>> arr_2;
    static int arr_2_counter;

    void make_string(std::string name, double sqr) {
        unsigned long k = Named::arr.size();
        int i = 0;
        for (i; i < k; i++) {
            if (Named::arr.at(i).first == name) {
                break;
            }
        }
        if (i == k) {
            Named::arr.emplace_back(make_pair(name, 1));
        }

        std::string shape_name = name;
        shape_name = name + '.' + std::to_string(Named::arr.at(i).second);
        Named::arr.at(i).second++;

        std::pair<std::string, double> arr_1;
        arr_1.first = shape_name;
        arr_1.second = sqr;
        Named::arr_2.emplace_back(arr_1);
    }

    Named(std::string name) {
        if (name != "") {
            Named::make_string(name, 0);
        }
    }

    operator std::pair<std::string, double>() const {
        unsigned long arr_s = Named::arr_2.size();
        std::pair<std::string, double> arr_1;
        arr_1.first = Named::arr_2.at(Named::arr_2_counter).first;
        arr_1.second = 0;
        Named::arr_2_counter++;
        return arr_1;
    };

    operator std::string() const {
        if (Named::arr_2.size() != 0) {
            std::string m = Named::arr_2[arr_2_counter].first;
            arr_2_counter++;
            if (arr_2_counter == Named::arr_2.size()) {
                Named::arr_2_counter = 0;
                Named::arr_2.resize(0);
                Named::arr.resize(0);
            }
            return m + '\n';
        }
        return "";
    };

    operator double() const {
        if (Named::arr_2.size() != 0) {
            double m = Named::arr_2[arr_2_counter].second;
            arr_2_counter++;
            if (arr_2_counter == Named::arr_2.size()) {
                Named::arr_2_counter = 0;
                Named::arr_2.resize(0);
                Named::arr.resize(0);
            }
            return m;
        }
        return 0;
    };
};

class Colored {
    int red_color;
    int green_color;
    int blue_color;

    std::string color;
public:
    Colored(int r1, int r2, int r3) {
        red_color = r1;
        green_color = r2;
        blue_color = r3;
        color = "-";
    }
    Colored(std::string name_color) {
        color = name_color;
        red_color = -1;
        green_color = -1;
        blue_color = -1;
    }
    Colored() {}
    Color getColor() {
        Color temp = {-1, -1, -1, "-"};
        if (red_color == -1) {
            temp.defined_color = color;
        }
        else {
            temp.r = red_color;
            temp.g = green_color;
            temp.b = blue_color;
        }
        return temp;
    };
    void setColor(std::string new_color) {
        red_color = -1;
        green_color = -1;
        blue_color = -1;

        color = new_color;
    };
    void setColor(int r, int g, int b) {
        red_color = r;
        green_color = g;
        blue_color = b;

        color = "-";
    };
};

class Segments {
public:
    virtual std::vector<std::tuple<int, int, int, int>> getSegments() const = 0;
};

class Shape : public Named, public Colored, public Segments {
public:
    virtual double square() const = 0;
    Shape(std::string name, int r1, int r2, int r3) : Named(name), Colored(r1, r2, r3) {}
    Shape(std::string name, std::string name_color) : Named(name), Colored(name_color) {}
    Shape(std::string name) : Named(name), Colored() {}
};

class Drawer {
    static bitmap_image img;
    static int width;
    static int height;
public:
    static void create_image(std::pair<int, int> m) {
        width = m.first;
        height = m.second;
        bitmap_image tmp(m.first, m.second);
        tmp.set_all_channels(255, 255, 255);
        image_drawer draw(tmp);
        draw.pen_width(1);

        draw.pen_color(0, 0, 255);
        draw.line_segment(0, tmp.height() / 2, tmp.width(), tmp.height() / 2);
        draw.line_segment(tmp.width() / 2, 0, tmp.width() / 2, tmp.height());

        img = tmp;
    }
    static void drawShape(Shape &s) {
        Color temp = s.getColor();

        image_drawer draw(img);
        draw.pen_width(2);

        if (temp.r == -1) {
            if (temp.defined_color == "red") {
                draw.pen_color(150, 0, 0);
            } else if (temp.defined_color == "orange") {
                draw.pen_color(238, 118, 0);
            } else if (temp.defined_color == "yellow") {
                draw.pen_color(255, 185, 15);
            } else if (temp.defined_color == "green") {
                draw.pen_color(0, 150, 0);
            } else if (temp.defined_color == "blue") {
                draw.pen_color(0, 0, 150);
            } else if (temp.defined_color == "violet") {
                draw.pen_color(139, 0, 139);
            } else if (temp.defined_color == "brown") {
                draw.pen_color(139, 35, 35);
            } else if (temp.defined_color == "pink") {
                draw.pen_color(255, 0, 120);
            }
        }
        else draw.pen_color(temp.r, temp.g, temp.b);

        std::vector<std::tuple<int, int, int, int>> shape_segments = s.getSegments();
        int segments_size = shape_segments.size();
        for (int i = 0; i < segments_size; i++) {
            int m = std::get<2>(shape_segments.at(i));
            draw.line_segment(std::get<0>(shape_segments.at(i)) + width / 2, height / 2 - std::get<1>(shape_segments.at(i)), std::get<2>(shape_segments.at(i)) + width / 2 , height / 2 - std::get<3>(shape_segments.at(i)));
        }
        img.save_image("example.bmp");
    }
};

class Rectangle : public Shape {
    int width;
    int height;

    int position_x;
    int position_y;
public:
    double square() const {
        return width * height;
    }

    std::vector<std::tuple<int, int, int, int>> getSegments() const {
        std::vector<std::tuple<int, int, int, int>> coords;
        coords.push_back(std::make_tuple(position_x - width / 2, position_y + height / 2, position_x + width / 2, position_y + height / 2));
        coords.push_back(std::make_tuple(position_x - width / 2, position_y + height / 2, position_x - width / 2, position_y - height / 2));
        coords.push_back(std::make_tuple(position_x - width / 2, position_y - height / 2, position_x + width / 2, position_y - height / 2));
        coords.push_back(std::make_tuple(position_x + width / 2, position_y + height / 2, position_x + width / 2, position_y - height / 2));

        return coords;
    };

    Rectangle(int w, int h) : Shape("") {
        Named::make_string("Rectangle", w * h);
    };

    Rectangle(int width_tmp, int height_tmp, int position_x_tmp, int position_y_tmp, int red_color_tmp,
              int green_color_tmp, int blue_color_tmp) : width(width_tmp), height(height_tmp),
                                                         position_x(position_x_tmp),
                                                         position_y(position_y_tmp), Shape("", red_color_tmp, green_color_tmp, blue_color_tmp)  {
    };

    Rectangle(int width_tmp, int height_tmp, int position_x_tmp,
              int position_y_tmp, std::string color_tmp) : width(width_tmp), height(height_tmp),
                                                           position_x(position_x_tmp),
                                                           position_y(position_y_tmp), Shape("", color_tmp) {
    };
};

class Circle : public Shape {
    int radius;

    int position_x;
    int position_y;
public:
    Circle(int radius_tmp) : Shape("") {
        Named::make_string("Circle", radius_tmp * radius_tmp * pi);
    }

    double square() const {
        return pi * radius * radius;
    }

    std::vector<std::tuple<int, int, int, int>> getSegments() const {
        int position_x1 = position_x;
        int position_y1 = position_y;
        int radius1 = radius;
        std::vector<std::pair<int, int>> left_part;
        std::vector<std::pair<int, int>> right_part;
        std::vector<std::tuple<int, int, int, int>> coords;

        for (double y = position_y1 + radius1; y >= position_y1 - radius1; y -= 0.5) {
            double x1 = sqrt(radius1 * radius1 - (y - position_y1) * (y - position_y1)) + position_x1 + 0.5;
            double x2 = -sqrt(radius1 * radius1 - (y - position_y1) * (y - position_y1)) + position_x1 + 0.5;
            left_part.push_back(std::make_pair(x1, y));
            right_part.push_back(std::make_pair(x2, y));
            if (left_part.size() == 2) {
                coords.push_back(std::make_tuple(left_part.at(0).first, left_part.at(0).second, left_part.at(1).first, left_part.at(1).second));
                coords.push_back(std::make_tuple(right_part.at(0).first, right_part.at(0).second, right_part.at(1).first, right_part.at(1).second));
                left_part.at(0) = left_part.at(1);
                right_part.at(0) = right_part.at(1);
                left_part.resize(1);
                right_part.resize(1);
            }
        }

        return coords;
    };

    Circle(int radius_tmp, int position_x_tmp, int position_y_tmp, int red_color_tmp,
           int green_color_tmp, int blue_color_tmp) : radius(radius_tmp), position_x(position_x_tmp),
                                                      position_y(position_y_tmp), Shape("", red_color_tmp, green_color_tmp, blue_color_tmp) {}

    Circle(int radius_tmp, int position_x_tmp, int position_y_tmp,
           std::string color_tmp) : radius(radius_tmp), position_x(position_x_tmp), position_y(position_y_tmp), Shape("", color_tmp) {}
};

class Triangle : public Shape {
    int position_x1, position_y1;
    int position_x2, position_y2;
    int position_x3, position_y3;
public:
    Triangle(int x1, int y1, int x2, int y2, int x3, int y3) : Shape("") {
        Named::make_string("Triangle", abs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1)) / 2.0);
    }
    double square() const {
        return abs((position_x2 - position_x1) * (position_y3 - position_y1) - (position_x3 - position_x1) * (position_y2 - position_y1)) / 2.0;
    }

    std::vector<std::tuple<int, int, int, int>> getSegments() const {
        std::vector<std::tuple<int, int, int, int>> coords;
        coords.push_back(std::make_tuple(position_x1, position_y1, position_x2, position_y2));
        coords.push_back(std::make_tuple(position_x2, position_y2, position_x3, position_y3));
        coords.push_back(std::make_tuple(position_x3, position_y3, position_x1, position_y1));

        return coords;
    }

    Triangle(int position_x1_tmp, int position_y1_tmp, int position_x2_tmp, int position_y2_tmp,
             int position_x3_tmp,
             int position_y3_tmp, int red_color_tmp, int green_color_tmp,
             int blue_color_tmp) : position_x1(position_x1_tmp), position_y1(position_y1_tmp),
                                   position_x2(position_x2_tmp), position_y2(position_y2_tmp),
                                   position_x3(position_x3_tmp), position_y3(position_y3_tmp),
                                   Shape("", red_color_tmp, green_color_tmp, blue_color_tmp) {}

    Triangle(int position_x1_tmp, int position_y1_tmp, int position_x2_tmp, int position_y2_tmp,
             int position_x3_tmp,
             int position_y3_tmp, std::string color_tmp) : position_x1(position_x1_tmp),
                                                          position_y1(position_y1_tmp),
                                                          position_x2(position_x2_tmp),
                                                          position_y2(position_y2_tmp),
                                                          position_x3(position_x3_tmp),
                                                          position_y3(position_y3_tmp),
                                                          Shape("", color_tmp) {}
};

template<typename T>
std::string printNames(T value) {
    return value;
}

template<typename T, typename... Args>
std::string printNames(T first, Args... args) {
    std::string k = printNames(first);
    return k + printNames(args...);
}

template<typename T>
double totalArea(T value) {
    return value;
}

template<typename T, typename... Args>
double totalArea(T first, Args... args) {
    double k = totalArea(first);
    return k + totalArea(args...);
}