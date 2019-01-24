#include "drawer_header.h"

template<>
std::string printNames<std::pair<std::string, double>>(std::pair<std::string, double> value) {
    return value.first + '\n';
}

int main() {
    //std::ifstream conditions_in("conditions.txt");
    std::pair<int, int> canvas_w_h = find_canvas(std::cin);

    Drawer::create_image(canvas_w_h);

    observing_shapes(std::cin);
    //conditions_in.close();

    std::cout << printNames(Circle(2), Named("Unknown"), Named("Unknown"), Named("Test"), Named("Test"), Named("Check"));
    std::cout << totalArea(Circle(1), Rectangle(4, 5), Triangle(0, 0, 0, 5, 2, 0));
    return 0;
}

