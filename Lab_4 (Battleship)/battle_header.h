#include <iostream>
#include <map>
#include <vector>

std::string create_table();

class Initializer {
protected:
    char table[10][10];
    std::vector<std::pair<int, int>> used_shots;
    std::pair<int, int> current_coords;
    std::pair<int, int> current_coords_following_hit;
    std::pair<int, int> success_coords;
    int first_hit;
    int four_decked;
    int three_decked;
    int two_decked;
    int one_decked;

    std::vector<int> possible_directions;
    int working_direction;
    int following_hit_flag;
    int change_direction;
    int direct_change;
    int cells_amount;
    int mark;
public:
    Initializer();
    friend class Field;
};

class Field : public Initializer {
public:
    std::string Shot();
    void Missed();
    std::string Hit();
    std::string Killed();
};