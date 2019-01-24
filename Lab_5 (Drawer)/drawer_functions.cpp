#include "drawer_header.h"

int Named::arr_2_counter = 0;
std::vector<std::pair<std::string, int>> Named::arr;
std::vector<std::pair<std::string, double>> Named::arr_2;
bitmap_image Drawer::img;
int Drawer::height;
int Drawer::width;

void drawShape(std::shared_ptr<Shape> shape) {
    Drawer::drawShape(*shape);
};

std::shared_ptr<Shape> parseShape(const std::string &shape_representative) {
    int i = 0;
    std::string template_shape;
    while (shape_representative[i] != '(') {
        template_shape += shape_representative[i];
        i++;
    }
    i++;
    try {
        if (template_shape == "Rectangle") {
            return observing_rectangle(i, shape_representative);
        } else if (template_shape == "Circle") {
            return observing_circle(i, shape_representative);
        } else if (template_shape == "Triangle") {
            return observing_triangle(i, shape_representative);
        }
        else {
            throw std::logic_error("Invalid shape input");
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what();
        exit(1);
    }
};

void observing_shapes(std::istream &stream) {
    std::string shape_representative;
    getline(stream, shape_representative);
    while (stream) {
        std::shared_ptr<Shape> new_shape = parseShape(shape_representative);
        drawShape(new_shape);
        getline(stream, shape_representative);
    }
}

std::pair<int, int> find_canvas(std::istream &stream) {
    std::string canvas_base;
    getline(stream, canvas_base);

    unsigned long string_size = canvas_base.size();
    std::string template_value;
    std::pair<int, int> m;

    m.first = 0;
    m.second = 0;

    try {
        for (int i = 0; i < string_size; i++) {
            if (canvas_base[i] == 'x') {
                m.first = stoi(template_value);
                if (m.first <= 0) {
                    throw std::logic_error("Invalid canvas size");
                }
                template_value = "";
            } else if (i == string_size - 1) {
                template_value += canvas_base[i];
                m.second = stoi(template_value);
                if (m.second <= 0) {
                    throw std::logic_error("Invalid canvas size");
                }
                template_value = "";
            } else {
                template_value += canvas_base[i];
            }
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what();
        exit(1);
    }
    return m;
}

std::shared_ptr<Shape> observing_rectangle(int &i, std::string shape_representative) {
    int rectangle_width;
    int rectangle_height;

    std::string rectangle_color;
    int rectangle_position_x;
    int rectangle_position_y;

    int rectangle_red_color = -1;
    int rectangle_green_color = -1;
    int rectangle_blue_color = -1;

    try {
        std::string template_number;
        while (shape_representative[i] != ',') {
            template_number += shape_representative[i];
            i++;
        }
        i++;

        rectangle_width = stoi(template_number);
        if (rectangle_width <= 0) {
            throw std::logic_error("Invalid rectangle input");
        }

        template_number = "";
        while (shape_representative[i] != ')') {
            template_number += shape_representative[i];
            i++;
        }

        rectangle_height = stoi(template_number);
        if (rectangle_height <= 0) {
            throw std::logic_error("Invalid rectangle input");
        }

        while (shape_representative[i - 1] != '[') {
            i++;
        }

        template_number = "";
        while (shape_representative[i] != ',') {
            template_number += shape_representative[i];
            i++;
        }
        i++;

        rectangle_position_x = stoi(template_number);

        template_number = "";
        while (shape_representative[i] != ']') {
            template_number += shape_representative[i];
            i++;
        }
        i++;

        rectangle_position_y = stoi(template_number);
        rectangle_color = "-";

        while (shape_representative[i - 1] != '{') {
            i++;
        }

        if ((shape_representative[i] >= 'a') && (shape_representative[i] <= 'z')) {
            std::string template_color;
            while (shape_representative[i] != '}') {
                template_color += shape_representative[i];
                i++;
            }
            i++;

            rectangle_color = template_color;
        } else {
            std::string template_number_color;
            while (shape_representative[i] != ',') {
                template_number_color += shape_representative[i];
                i++;
            }
            i++;

            rectangle_red_color = stoi(template_number_color);
            if (rectangle_red_color < 0) {
                throw std::logic_error("Invalid rectangle red color input");
            }

            template_number_color = "";
            while (shape_representative[i] != ',') {
                template_number_color += shape_representative[i];
                i++;
            }
            i++;

            rectangle_green_color = stoi(template_number_color);
            if (rectangle_green_color < 0) {
                throw std::logic_error("Invalid rectangle green color input");
            }

            template_number_color = "";
            while (shape_representative[i] != '}') {
                template_number_color += shape_representative[i];
                i++;
            }

            rectangle_blue_color = stoi(template_number_color);
            if (rectangle_blue_color < 0) {
                throw std::logic_error("Invalid rectangle blue color input");
            }
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what();
        exit(1);
    }

    if (rectangle_color == "-") {
        Rectangle *ptr = new Rectangle(rectangle_width, rectangle_height, rectangle_position_x, rectangle_position_y,
                                         rectangle_red_color, rectangle_green_color, rectangle_blue_color);;
        std::shared_ptr<Shape> p(ptr);
        return p;

    } else {
        Rectangle *ptr = new Rectangle(rectangle_width, rectangle_height, rectangle_position_x, rectangle_position_y,
                                       rectangle_color);
        std::shared_ptr<Shape> p(ptr);
        return p;
    }
}

std::shared_ptr<Shape> observing_circle(int &i, std::string shape_representative) {
    int circle_radius;

    int circle_position_x;
    int circle_position_y;

    std::string circle_color;
    int circle_red_color = -1;
    int circle_green_color = -1;
    int circle_blue_color = -1;

    try {
        std::string template_number;
        while (shape_representative[i] != ')') {
            template_number += shape_representative[i];
            i++;
        }
        i++;

        circle_radius = stoi(template_number);
        if (circle_radius < 0) {
            throw std::logic_error("Invalid circle radius input");
        }

        while (shape_representative[i - 1] != '[') {
            i++;
        }

        template_number = "";
        while (shape_representative[i] != ',') {
            template_number += shape_representative[i];
            i++;
        }
        i++;

        circle_position_x = stoi(template_number);

        template_number = "";
        while (shape_representative[i] != ']') {
            template_number += shape_representative[i];
            i++;
        }
        i++;

        circle_position_y = stoi(template_number);

        while (shape_representative[i - 1] != '{') {
            i++;
        }

        circle_color = "-";

        if ((shape_representative[i] >= 'a') && (shape_representative[i] <= 'z')) {
            std::string template_color;
            while (shape_representative[i] != '}') {
                template_color += shape_representative[i];
                i++;
            }
            i++;

            circle_color = template_color;
        } else {
            std::string template_number_color;
            while (shape_representative[i] != ',') {
                template_number_color += shape_representative[i];
                i++;
            }
            i++;

            circle_red_color = stoi(template_number_color);
            if (circle_red_color < 0) {
                throw std::logic_error("Invalid circle red color input");
            }

            template_number_color = "";
            while (shape_representative[i] != ',') {
                template_number_color += shape_representative[i];
                i++;
            }
            i++;

            circle_green_color = stoi(template_number_color);
            if (circle_green_color < 0) {
                throw std::logic_error("Invalid circle green color input");
            }

            template_number_color = "";
            while (shape_representative[i] != '}') {
                template_number_color += shape_representative[i];
                i++;
            }

            circle_blue_color = stoi(template_number_color);
            if (circle_blue_color < 0) {
                throw std::logic_error("Invalid circle blue color input");
            }
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what();
        exit(1);
    }

    if (circle_color == "-") {
        Circle *ptr = new Circle(circle_radius, circle_position_x, circle_position_y, circle_red_color, circle_green_color,
                                 circle_blue_color);
        std::shared_ptr<Shape> p(ptr);
        return p;
    } else {
        Circle *ptr = new Circle(circle_radius, circle_position_x, circle_position_y, circle_color);
        std::shared_ptr<Shape> p(ptr);
        return p;
    }
}

std::shared_ptr<Shape> observing_triangle(int &i, std::string shape_representative) {
    int triangle_x2, triangle_y2;
    int triangle_x3, triangle_y3;
    int triangle_position_x;
    int triangle_position_y;

    std::string triangle_color;
    int triangle_red_color = -1;
    int triangle_green_color = -1;
    int triangle_blue_color = -1;

    try {
        std::string template_number;
        while (shape_representative[i] != ',') {
            template_number += shape_representative[i];
            i++;
        }
        i++;

        triangle_x2 = stoi(template_number);

        template_number = "";
        while (shape_representative[i] != ',') {
            template_number += shape_representative[i];
            i++;
        }
        i++;

        triangle_y2 = stoi(template_number);

        template_number = "";
        while (shape_representative[i] != ',') {
            template_number += shape_representative[i];
            i++;
        }
        i++;

        triangle_x3 = stoi(template_number);

        template_number = "";
        while (shape_representative[i] != ')') {
            template_number += shape_representative[i];
            i++;
        }
        i++;

        triangle_y3 = stoi(template_number);

        while (shape_representative[i - 1] != '[') {
            i++;
        }

        template_number = "";
        while (shape_representative[i] != ',') {
            template_number += shape_representative[i];
            i++;
        }
        i++;

        triangle_position_x = stoi(template_number);

        template_number = "";
        while (shape_representative[i] != ']') {
            template_number += shape_representative[i];
            i++;
        }
        i++;

        triangle_position_y = stoi(template_number);

        while (shape_representative[i - 1] != '{') {
            i++;
        }

        triangle_color = "-";

        if ((shape_representative[i] >= 'a') && (shape_representative[i] <= 'z')) {
            std::string template_color;
            while (shape_representative[i] != '}') {
                template_color += shape_representative[i];
                i++;
            }
            i++;

            triangle_color = template_color;
        } else {
            std::string template_number_color;
            while (shape_representative[i] != ',') {
                template_number_color += shape_representative[i];
                i++;
            }
            i++;

            triangle_red_color = stoi(template_number_color);
            if (triangle_red_color < 0) {
                throw std::logic_error("Invalid triangle red color input");
            }

            template_number_color = "";
            while (shape_representative[i] != ',') {
                template_number_color += shape_representative[i];
                i++;
            }
            i++;

            triangle_green_color = stoi(template_number_color);
            if (triangle_green_color < 0) {
                throw std::logic_error("Invalid triangle green color input");
            }

            template_number_color = "";
            while (shape_representative[i] != '}') {
                template_number_color += shape_representative[i];
                i++;
            }

            triangle_blue_color = stoi(template_number_color);
            if (triangle_blue_color < 0) {
                throw std::logic_error("Invalid triangle blue color input");
            }
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what();
        exit(1);
    }

    if (triangle_color == "-") {
        Triangle *ptr = new Triangle(triangle_position_x, triangle_position_y, triangle_x2, triangle_y2, triangle_x3, triangle_y3, triangle_red_color, triangle_green_color,
                                   triangle_blue_color);
        std::shared_ptr<Shape> p(ptr);
        return p;
    } else {
        Triangle *ptr = new Triangle(triangle_position_x, triangle_position_y, triangle_x2, triangle_y2, triangle_x3, triangle_y3, triangle_color);
        std::shared_ptr<Shape> p(ptr);
        return p;
    }
}