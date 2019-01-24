#include "battle_header.h"

Initializer::Initializer() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            table[i][j] = '0';
        }
    }
    success_coords.first = -1;
    success_coords.second = -1;
    four_decked = 1;
    three_decked = 2;
    two_decked = 3;
    one_decked = 4;
    first_hit = 1;
    working_direction = 0;
    following_hit_flag = 0;
    change_direction = 0;
    cells_amount = 0;
    direct_change = 0;
    mark = 0;
}

std::string Field::Shot() {
    if (direct_change == 1) {
        direct_change = 0;
        mark = 1;
        return Hit();
    }
    if (change_direction == 1) {
        int u1 = -1;
        int u2 = -1;
        std::string final_command = "";
        while ((u1 < 0) || (u2 < 0)) {
            std::vector<int> possible_directions_new;

            int g = possible_directions.size();
            for (int y = 0; y < g; y++) {
                if (possible_directions.at(y) != possible_directions[working_direction]) {
                    possible_directions_new.push_back(possible_directions.at(y));
                }
            }
            possible_directions.clear();
            possible_directions = possible_directions_new;
            working_direction = 0;

            switch (possible_directions[working_direction]) {
                case -2:
                    final_command += char('A' + success_coords.first - 1);
                    final_command += ' ';
                    final_command += std::to_string(success_coords.second);
                    final_command += '\n';
                    u1 = success_coords.first - 1;
                    u2 = success_coords.second;
                    current_coords_following_hit.first = success_coords.first - 1;
                    current_coords_following_hit.second = success_coords.second;
                    break;
                case 2:
                    final_command += char('A' + success_coords.first + 1);
                    final_command += ' ';
                    final_command += std::to_string(success_coords.second);
                    final_command += '\n';
                    u1 = success_coords.first + 1;
                    u2 = success_coords.second;
                    current_coords_following_hit.first = success_coords.first + 1;
                    current_coords_following_hit.second = success_coords.second;
                    break;
                case -1:
                    final_command += char('A' + success_coords.first);
                    final_command += ' ';
                    final_command += std::to_string(success_coords.second + 1);
                    final_command += '\n';
                    u1 = success_coords.first;
                    u2 = success_coords.second + 1;
                    current_coords_following_hit.first = success_coords.first;
                    current_coords_following_hit.second = success_coords.second + 1;
                    break;
                case 1:
                    final_command += char('A' + success_coords.first);
                    final_command += ' ';
                    final_command += std::to_string(success_coords.second - 1);
                    final_command += '\n';
                    u1 = success_coords.first;
                    u2 = success_coords.second - 1;
                    current_coords_following_hit.first = success_coords.first;
                    current_coords_following_hit.second = success_coords.second - 1;
                    break;
            }
            if ((u1 >= 0) && (u2 >= 0)) {
                if (table[u2][u1] == '-') {
                    u1 = -1;
                }
            }
        }
        change_direction = 0;
        return final_command;
    } else {
        srand((unsigned int) time(NULL));

        if (first_hit == 1) {
            int x;
            int y;
            while (1) {
                x = rand() % (9 - 0 + 1) + 0;
                y = rand() % (9 - 0 + 1) + 0;
                if (table[y][x] != '-') {
                    current_coords.first = x;
                    current_coords.second = y;
                    break;
                }
            }
            std::string final_command = "";
            final_command += char('A' + x);
            final_command += ' ';
            final_command += std::to_string(y);
            final_command += '\n';
            return final_command;
        } else {
            std::string final_command = "";
            switch (possible_directions[working_direction]) {
                case -2:
                    final_command += char('A' + current_coords_following_hit.first - 1);
                    final_command += ' ';
                    final_command += std::to_string(current_coords_following_hit.second);
                    final_command += '\n';
                    current_coords_following_hit.first = current_coords_following_hit.first - 1;
                    current_coords_following_hit.second = current_coords_following_hit.second;
                    break;
                case 2:
                    final_command += char('A' + current_coords_following_hit.first + 1);
                    final_command += ' ';
                    final_command += std::to_string(current_coords_following_hit.second);
                    final_command += '\n';
                    current_coords_following_hit.first = current_coords_following_hit.first + 1;
                    current_coords_following_hit.second = current_coords_following_hit.second;
                    break;
                case -1:
                    final_command += char('A' + current_coords_following_hit.first);
                    final_command += ' ';
                    final_command += std::to_string(current_coords_following_hit.second + 1);
                    final_command += '\n';
                    current_coords_following_hit.first = current_coords_following_hit.first;
                    current_coords_following_hit.second = current_coords_following_hit.second + 1;
                    break;
                case 1:
                    final_command += char('A' + current_coords_following_hit.first);
                    final_command += ' ';
                    final_command += std::to_string(current_coords_following_hit.second - 1);
                    final_command += '\n';
                    current_coords_following_hit.first = current_coords_following_hit.first;
                    current_coords_following_hit.second = current_coords_following_hit.second - 1;
                    break;
            }
            return final_command;
        }
    }
}

void Field::Missed() {
    if (following_hit_flag == 1) {
        table[current_coords_following_hit.second][current_coords_following_hit.first] = '-';
        if (success_coords.first == -1) {
            current_coords.first = success_coords.first;
            current_coords.first = success_coords.second;
        }
        if (cells_amount == 1) {
            change_direction = 1;
        } else {
            int g = possible_directions.size();
            int y;
            for (y = 0; y < g; y++) {
                if (possible_directions.at(y) == -possible_directions[working_direction]) {
                    break;
                }
            }
            working_direction = y;
            current_coords_following_hit.first = success_coords.first;
            current_coords_following_hit.second = success_coords.second;
            direct_change = 1;
        }
    } else table[current_coords.second][current_coords.first] = '-';
}

std::string Field::Hit() {
    srand((unsigned int) time(NULL) + 3);
    if (mark == 1) {
        mark = 0;
    } else cells_amount++;

    if (following_hit_flag == 1) {
        table[current_coords_following_hit.second][current_coords_following_hit.first] = '-';
    } else table[current_coords.second][current_coords.first] = '-';

    if (success_coords.first == -1) {
        success_coords.first = current_coords.first;
        success_coords.second = current_coords.second;
    }

    if (first_hit == 1) {
        int possible_left = 0;
        int possible_right = 0;
        int possible_up = 0;
        int possible_down = 0;

        if (four_decked > 0) {
            if ((current_coords.first - 3 >= 0) &&
                (table[current_coords.second][current_coords.first - 3] != '-') &&
                (table[current_coords.second][current_coords.first - 2] != '-') &&
                (table[current_coords.second][current_coords.first - 1] != '-')) {
                possible_left = 1;
            }
            if ((current_coords.first - 2 >= 0) && (current_coords.first - 1 >= 0) && (current_coords.first + 1 <= 9) &&
                (table[current_coords.second][current_coords.first - 2] != '-') &&
                (table[current_coords.second][current_coords.first - 1] != '-') &&
                (table[current_coords.second][current_coords.first + 1] != '-')) {
                possible_left = 1;
            }
            if ((current_coords.first - 1 >= 0) && (current_coords.first + 1 <= 9) && (current_coords.first + 2 <= 9) &&
                (table[current_coords.second][current_coords.first - 1] != '-') &&
                (table[current_coords.second][current_coords.first + 1] != '-') &&
                (table[current_coords.second][current_coords.first + 2] != '-')) {
                possible_left = 1;
            }
            if ((current_coords.first + 3 < 10) &&
                (table[current_coords.second][current_coords.first + 3] != '-') &&
                (table[current_coords.second][current_coords.first + 2] != '-') &&
                (table[current_coords.second][current_coords.first + 1] != '-')) {
                possible_right = 1;
            }
            if ((current_coords.first - 2 >= 0) && (current_coords.first - 1 >= 0) && (current_coords.first + 1 <= 9) &&
                (table[current_coords.second][current_coords.first - 2] != '-') &&
                (table[current_coords.second][current_coords.first - 1] != '-') &&
                (table[current_coords.second][current_coords.first + 1] != '-')) {
                possible_right = 1;
            }
            if ((current_coords.first - 1 >= 0) && (current_coords.first + 1 <= 9) && (current_coords.first + 2 <= 9) &&
                (table[current_coords.second][current_coords.first - 1] != '-') &&
                (table[current_coords.second][current_coords.first + 1] != '-') &&
                (table[current_coords.second][current_coords.first + 2] != '-')) {
                possible_right = 1;
            }

            if ((current_coords.second - 3 >= 0) &&
                (table[current_coords.second - 3][current_coords.first] != '-') &&
                (table[current_coords.second - 2][current_coords.first] != '-') &&
                (table[current_coords.second - 1][current_coords.first] != '-')) {
                possible_up = 1;
            }

            if ((current_coords.second - 2 >= 0) && (current_coords.second - 1 >= 0) &&
                (current_coords.second + 1 <= 9) && (table[current_coords.second - 2][current_coords.first] != '-') &&
                (table[current_coords.second - 1][current_coords.first] != '-') &&
                (table[current_coords.second + 1][current_coords.first] != '-')) {
                possible_up = 1;
            }
            if ((current_coords.second - 1 >= 0) && (current_coords.second + 1 <= 9) &&
                (current_coords.second + 2 <= 9) &&
                (table[current_coords.second - 1][current_coords.first] != '-') &&
                (table[current_coords.second + 1][current_coords.first] != '-') &&
                (table[current_coords.second + 2][current_coords.first] != '-')) {
                possible_up = 1;
            }

            if ((current_coords.second + 3 < 10) &&
                (table[current_coords.second + 3][current_coords.first] != '-') &&
                (table[current_coords.second + 2][current_coords.first] != '-') &&
                (table[current_coords.second + 1][current_coords.first] != '-')) {
                possible_down = 1;
            }

            if ((current_coords.second - 2 >= 0) && (current_coords.second - 1 >= 0) &&
                (current_coords.second + 1 <= 9) && (table[current_coords.second - 2][current_coords.first] != '-') &&
                (table[current_coords.second - 1][current_coords.first] != '-') &&
                (table[current_coords.second + 1][current_coords.first] != '-')) {
                possible_down = 1;
            }
            if ((current_coords.second - 1 >= 0) && (current_coords.second + 1 <= 9) &&
                (current_coords.second + 2 <= 9) &&
                (table[current_coords.second - 1][current_coords.first] != '-') &&
                (table[current_coords.second + 1][current_coords.first] != '-') &&
                (table[current_coords.second + 2][current_coords.first] != '-')) {
                possible_down = 1;
            }
        }
        if (three_decked > 0) {
            if ((current_coords.first + 1 - 3 >= 0) &&
                (table[current_coords.second][current_coords.first + 1 - 3] != '-') &&
                (table[current_coords.second][current_coords.first + 1 - 2] != '-')) {
                possible_left = 1;
            }
            if ((current_coords.first + 1 <= 9) && (current_coords.first - 1 >= 0) &&
                (table[current_coords.second][current_coords.first - 1] != '-') &&
                (table[current_coords.second][current_coords.first + 1] != '-')) {
                possible_left = 1;
            }
            if ((current_coords.first + 2 < 10) &&
                (table[current_coords.second][current_coords.first + 2] != '-') &&
                (table[current_coords.second][current_coords.first + 1] != '-')) {
                possible_right = 1;
            }
            if ((current_coords.first + 1 <= 9) && (current_coords.first - 1 >= 0) &&
                (table[current_coords.second][current_coords.first - 1] != '-') &&
                (table[current_coords.second][current_coords.first + 1] != '-')) {
                possible_right = 1;
            }
            if ((current_coords.second + 1 - 3 >= 0) &&
                (table[current_coords.second + 1 - 3][current_coords.first] != '-') &&
                (table[current_coords.second + 1 - 2][current_coords.first] != '-')) {
                possible_up = 1;
            }
            if ((current_coords.second - 1 >= 0) && (current_coords.second + 1 <= 9) &&
                (table[current_coords.second - 1][current_coords.first] != '-') &&
                (table[current_coords.second + 1][current_coords.first] != '-')) {
                possible_up = 1;
            }
            if ((current_coords.second + 2 < 10) &&
                (table[current_coords.second + 2][current_coords.first] != '-') &&
                (table[current_coords.second + 1][current_coords.first] != '-')) {
                possible_down = 1;
            }
            if ((current_coords.second - 1 >= 0) && (current_coords.second + 1 <= 9) &&
                (table[current_coords.second - 1][current_coords.first] != '-') &&
                (table[current_coords.second + 1][current_coords.first] != '-')) {
                possible_down = 1;
            }
        }
        if (two_decked > 0) {
            if ((current_coords.first - 1 >= 0) &&
                (table[current_coords.second][current_coords.first - 1] != '-')) {
                possible_left = 1;
            }
            if ((current_coords.first + 1 < 10) &&
                (table[current_coords.second][current_coords.first + 1] != '-')) {
                possible_right = 1;
            }
            if ((current_coords.second + 1 - 2 >= 0) &&
                (table[current_coords.second + 1 - 2][current_coords.first] != '-')) {
                possible_up = 1;
            }
            if ((current_coords.second + 1 < 10) &&
                (table[current_coords.second + 1][current_coords.first] != '-')) {
                possible_down = 1;
            }
        }

        possible_directions.clear();

        if (possible_left) {
            possible_directions.push_back(-2);
        }
        if (possible_right) {
            possible_directions.push_back(2);
        }
        if (possible_down) {
            possible_directions.push_back(-1);
        }
        if (possible_up) {
            possible_directions.push_back(1);
        }

        working_direction = 0;

        int u1 = 1;
        int u2;
        std::string final_command = "";
        while (u1 > 0) {
            switch (possible_directions[working_direction]) {
                case -2:
                    final_command += char('A' + current_coords.first - 1);
                    final_command += ' ';
                    final_command += std::to_string(current_coords.second);
                    final_command += '\n';
                    u1 = current_coords.first - 1;
                    u2 = current_coords.second;
                    current_coords_following_hit.first = current_coords.first - 1;
                    current_coords_following_hit.second = current_coords.second;
                    break;
                case 2:
                    final_command += char('A' + current_coords.first + 1);
                    final_command += ' ';
                    final_command += std::to_string(current_coords.second);
                    final_command += '\n';
                    u1 = current_coords.first + 1;
                    u2 = current_coords.second;
                    current_coords_following_hit.first = current_coords.first + 1;
                    current_coords_following_hit.second = current_coords.second;
                    break;
                case -1:
                    final_command += char('A' + current_coords.first);
                    final_command += ' ';
                    final_command += std::to_string(current_coords.second + 1);
                    final_command += '\n';
                    u1 = current_coords.first;
                    u2 = current_coords.second + 1;
                    current_coords_following_hit.first = current_coords.first;
                    current_coords_following_hit.second = current_coords.second + 1;
                    break;
                case 1:
                    final_command += char('A' + current_coords.first);
                    final_command += ' ';
                    final_command += std::to_string(current_coords.second - 1);
                    final_command += '\n';
                    u1 = current_coords.first;
                    u2 = current_coords.second - 1;
                    current_coords_following_hit.first = current_coords.first;
                    current_coords_following_hit.second = current_coords.second - 1;
                    break;
            }
            if (table[u2][u1] == '-') {
                std::vector<int> possible_directions_new;

                int g = possible_directions.size();
                for (int y = 0; y < g; y++) {
                    if (possible_directions.at(y) != possible_directions[working_direction]) {
                        possible_directions_new.push_back(possible_directions.at(y));
                    }
                }
                possible_directions.clear();
                possible_directions = possible_directions_new;
                working_direction = 0;
            } else u1 = 0;
        }
        following_hit_flag = 1;
        first_hit = 0;
        return final_command;
    } else {
        std::string final_command = "";
        switch (possible_directions[working_direction]) {
            case -2:
                final_command += char('A' + current_coords_following_hit.first - 1);
                final_command += ' ';
                final_command += std::to_string(current_coords_following_hit.second);
                final_command += '\n';
                current_coords_following_hit.first = current_coords_following_hit.first - 1;
                current_coords_following_hit.second = current_coords_following_hit.second;
                break;
            case 2:
                final_command += char('A' + current_coords_following_hit.first + 1);
                final_command += ' ';
                final_command += std::to_string(current_coords_following_hit.second);
                final_command += '\n';
                current_coords_following_hit.first = current_coords_following_hit.first + 1;
                current_coords_following_hit.second = current_coords_following_hit.second;
                break;
            case -1:
                final_command += char('A' + current_coords_following_hit.first);
                final_command += ' ';
                final_command += std::to_string(current_coords_following_hit.second + 1);
                final_command += '\n';
                current_coords_following_hit.first = current_coords_following_hit.first;
                current_coords_following_hit.second = current_coords_following_hit.second + 1;
                break;
            case 1:
                final_command += char('A' + current_coords_following_hit.first);
                final_command += ' ';
                final_command += std::to_string(current_coords_following_hit.second - 1);
                final_command += '\n';
                current_coords_following_hit.first = current_coords_following_hit.first;
                current_coords_following_hit.second = current_coords_following_hit.second - 1;
                break;
        }
        if ((current_coords_following_hit.first < 0) || (current_coords_following_hit.first > 9) ||
            (current_coords_following_hit.second < 0) || (current_coords_following_hit.second > 9)) {
            final_command = "";

            int g = possible_directions.size();
            int y;
            for (y = 0; y < g; y++) {
                if (possible_directions.at(y) == -possible_directions[working_direction]) {
                    break;
                }
            }
            working_direction = y;
            current_coords_following_hit.first = success_coords.first;
            current_coords_following_hit.second = success_coords.second;

            switch (possible_directions[working_direction]) {
                case -2:
                    final_command += char('A' + current_coords_following_hit.first - 1);
                    final_command += ' ';
                    final_command += std::to_string(current_coords_following_hit.second);
                    final_command += '\n';
                    current_coords_following_hit.first = current_coords_following_hit.first - 1;
                    current_coords_following_hit.second = current_coords_following_hit.second;
                    break;
                case 2:
                    final_command += char('A' + current_coords_following_hit.first + 1);
                    final_command += ' ';
                    final_command += std::to_string(current_coords_following_hit.second);
                    final_command += '\n';
                    current_coords_following_hit.first = current_coords_following_hit.first + 1;
                    current_coords_following_hit.second = current_coords_following_hit.second;
                    break;
                case -1:
                    final_command += char('A' + current_coords_following_hit.first);
                    final_command += ' ';
                    final_command += std::to_string(current_coords_following_hit.second + 1);
                    final_command += '\n';
                    current_coords_following_hit.first = current_coords_following_hit.first;
                    current_coords_following_hit.second = current_coords_following_hit.second + 1;
                    break;
                case 1:
                    final_command += char('A' + current_coords_following_hit.first);
                    final_command += ' ';
                    final_command += std::to_string(current_coords_following_hit.second - 1);
                    final_command += '\n';
                    current_coords_following_hit.first = current_coords_following_hit.first;
                    current_coords_following_hit.second = current_coords_following_hit.second - 1;
                    break;
            }
        } else if (table[current_coords_following_hit.second][current_coords_following_hit.first] == '-') {
            final_command = "";

            int g = possible_directions.size();
            int y;
            for (y = 0; y < g; y++) {
                if (possible_directions[y] == -possible_directions[working_direction]) {
                    break;
                }
            }
            working_direction = y;
            current_coords_following_hit.first = success_coords.first;
            current_coords_following_hit.second = success_coords.second;

            switch (possible_directions[working_direction]) {
                case -2:
                    final_command += char('A' + current_coords_following_hit.first - 1);
                    final_command += ' ';
                    final_command += std::to_string(current_coords_following_hit.second);
                    final_command += '\n';
                    current_coords_following_hit.first = current_coords_following_hit.first - 1;
                    current_coords_following_hit.second = current_coords_following_hit.second;
                    break;
                case 2:
                    final_command += char('A' + current_coords_following_hit.first + 1);
                    final_command += ' ';
                    final_command += std::to_string(current_coords_following_hit.second);
                    final_command += '\n';
                    current_coords_following_hit.first = current_coords_following_hit.first + 1;
                    current_coords_following_hit.second = current_coords_following_hit.second;
                    break;
                case -1:
                    final_command += char('A' + current_coords_following_hit.first);
                    final_command += ' ';
                    final_command += std::to_string(current_coords_following_hit.second + 1);
                    final_command += '\n';
                    current_coords_following_hit.first = current_coords_following_hit.first;
                    current_coords_following_hit.second = current_coords_following_hit.second + 1;
                    break;
                case 1:
                    final_command += char('A' + current_coords_following_hit.first);
                    final_command += ' ';
                    final_command += std::to_string(current_coords_following_hit.second - 1);
                    final_command += '\n';
                    current_coords_following_hit.first = current_coords_following_hit.first;
                    current_coords_following_hit.second = current_coords_following_hit.second - 1;
                    break;
            }
        }

        return final_command;
    }
}

std::string Field::Killed() {
    cells_amount++;
    switch (cells_amount) {
        case 1:
            one_decked--;
            break;
        case 2:
            two_decked--;
            break;
        case 3:
            three_decked--;
            break;
        case 4:
            four_decked--;
            break;
    }
    if (following_hit_flag == 1)
        table[current_coords_following_hit.second][current_coords_following_hit.first] = '-';
    else
        table[current_coords.second][current_coords.first] = '-';
    success_coords.first = -1;
    success_coords.second = -1;

    int x1, x2, y1, y2;
    if (possible_directions.size() != 0) {
        switch (possible_directions[working_direction]) {
            case -2:
                x2 = current_coords_following_hit.first + cells_amount;
                y2 = current_coords_following_hit.second + 1;

                x1 = current_coords_following_hit.first - 1;
                y1 = current_coords_following_hit.second - 1;
                break;
            case 2:
                x2 = current_coords_following_hit.first + 1;
                y2 = current_coords_following_hit.second + 1;

                x1 = current_coords_following_hit.first - cells_amount;
                y1 = current_coords_following_hit.second - 1;
                break;
            case -1:
                x2 = current_coords_following_hit.first + 1;
                y2 = current_coords_following_hit.second + 1;

                x1 = current_coords_following_hit.first - 1;
                y1 = current_coords_following_hit.second - cells_amount;
                break;
            case 1:
                x2 = current_coords_following_hit.first + 1;
                y2 = current_coords_following_hit.second + cells_amount;

                x1 = current_coords_following_hit.first - 1;
                y1 = current_coords_following_hit.second - 1;
                break;
        }


        if (x1 < 0) x1 = 0;
        if (x1 > 9) x1 = 9;
        if (y1 < 0) y1 = 0;
        if (y1 > 9) y1 = 9;
        if (x2 < 0) x2 = 0;
        if (x2 > 9) x2 = 9;
        if (y2 < 0) y2 = 0;
        if (y2 > 9) y2 = 9;

        if (x1 > x2) {
            int tmp = x1;
            x1 = x2;
            x2 = tmp;
        }

        if (y1 > y2) {
            int tmp = y1;
            y1 = y2;
            y2 = tmp;
        }

        for (int i = x1; i <= x2; i++) {
            for (int j = y1; j <= y2; j++) {
                table[j][i] = '-';
            }
        }
    } else {
        x2 = current_coords.first + 1;
        y2 = current_coords.second + cells_amount;

        x1 = current_coords.first - 1;
        y1 = current_coords.second - 1;

        if (x1 < 0) x1 = 0;
        if (x1 > 9) x1 = 9;
        if (y1 < 0) y1 = 0;
        if (y1 > 9) y1 = 9;
        if (x2 < 0) x2 = 0;
        if (x2 > 9) x2 = 9;
        if (y2 < 0) y2 = 0;
        if (y2 > 9) y2 = 9;

        if (x1 > x2) {
            int tmp = x1;
            x1 = x2;
            x2 = tmp;
        }

        if (y1 > y2) {
            int tmp = y1;
            y1 = y2;
            y2 = tmp;
        }

        for (int i = x1; i <= x2; i++) {
            for (int j = y1; j <= y2; j++) {
                table[j][i] = '-';
            }
        }
    }
    first_hit = 1;
    success_coords.first = -1;
    success_coords.second = -1;

    current_coords.first = -1;
    current_coords.second = -1;
    current_coords_following_hit.first = 0;
    current_coords_following_hit.second = 0;

    working_direction = 0;
    possible_directions.clear();
    following_hit_flag = 0;
    cells_amount = 0;

    return Shot();
}

std::string create_table() {
    char table[10][10];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            table[i][j] = '0';
        }
    }

    srand((unsigned int) time(NULL) + 2);

    // introducing the first 4-decked ship

    int x = rand() % (9 - 0 + 1) + 0;
    int y = rand() % (9 - 0 + 1) + 0;
    std::vector<int> direction;

    // -2 == left
    // 2 == right
    // 1 == up
    // -1 == down

    if (x + 1 - 4 >= 0)
        direction.push_back(-2);
    if (x + 4 <= 10)
        direction.push_back(2);
    if (y + 4 <= 10)
        direction.push_back(-1);
    if (y + 1 - 4 >= 0) {
        direction.push_back(1);
    }

    int g = direction.size();
    int c = rand() % (g - 1 - 0 + 1) + 0;

    int x1, y1;
    int x2, y2;
    switch (direction[c]) {
        case -2:
            for (int i = x - 3; i <= x; i++) {
                table[i][y] = '1';
            }
            x1 = x - 4;
            y1 = y - 1;
            x2 = x + 1;
            y2 = y + 1;
            break;
        case 2:
            for (int i = x; i <= x + 3; i++) {
                table[i][y] = '1';
            }
            x1 = x - 1;
            y1 = y - 1;
            x2 = x + 4;
            y2 = y + 1;
            break;
        case 1:
            for (int i = y - 3; i <= y; i++) {
                table[x][i] = '1';
            }
            x1 = x - 1;
            y1 = y - 4;
            x2 = x + 1;
            y2 = y + 1;
            break;
        case -1:
            for (int i = y; i <= y + 3; i++) {
                table[x][i] = '1';
            }
            x1 = x - 1;
            y1 = y - 1;
            x2 = x + 1;
            y2 = y + 4;
            break;
    }

    // introducing the first 3-decked ship

    while (1) {
        x = rand() % (9 - 0 + 1) + 0;
        y = rand() % (9 - 0 + 1) + 0;
        if (!(((x1 <= x) && (x <= x2)) && ((y1 <= y) && (y <= y2)))) {
            break;
        }
    }

    direction.clear();
    if ((x + 1 - 3 >= 0) && !((x1 <= x + 1 - 3) && (x + 1 - 3 <= x2) && (y1 <= y) && (y <= y2)))
        direction.push_back(-2);
    if ((x + 3 <= 10) && !((x1 <= x + 3) && (x + 3 <= x2) && (y1 <= y) && (y <= y2)))
        direction.push_back(2);
    if ((y + 3 <= 10) && !((y1 <= y + 3) && (y + 3 <= y2) && (x1 <= x) && (x <= x2)))
        direction.push_back(-1);
    if ((y + 1 - 3 >= 0) && !((y1 <= y + 1 - 3) && (y + 1 - 3 <= y2) && (x1 <= x) && (x <= x2)))
        direction.push_back(1);

    g = direction.size();
    c = rand() % (g - 1 - 0 + 1) + 0;
    int x3, y3;
    int x4, y4;
    switch (direction[c]) {
        case -2:
            for (int i = x - 2; i <= x; i++) {
                table[i][y] = '1';
            }
            x3 = x - 3;
            y3 = y - 1;
            x4 = x + 1;
            y4 = y + 1;
            break;
        case 2:
            for (int i = x; i <= x + 2; i++) {
                table[i][y] = '1';
            }
            x3 = x - 1;
            y3 = y - 1;
            x4 = x + 3;
            y4 = y + 1;
            break;
        case 1:
            for (int i = y - 2; i <= y; i++) {
                table[x][i] = '1';
            }
            x3 = x - 1;
            y3 = y - 3;
            x4 = x + 1;
            y4 = y + 1;
            break;
        case -1:
            for (int i = y; i <= y + 2; i++) {
                table[x][i] = '1';
            }
            x3 = x - 1;
            y3 = y - 1;
            x4 = x + 1;
            y4 = y + 3;
            break;
    }

    // introducing the second 3-decked ship

    while (1) {
        x = rand() % (9 - 0 + 1) + 0;
        y = rand() % (9 - 0 + 1) + 0;
        if (!(((x1 <= x) && (x <= x2) && (y1 <= y) && (y <= y2)) ||
              ((x3 <= x) && (x <= x4) && (y3 <= y) && (y <= y4)))) {
            break;
        }
    }

    direction.clear();
    if ((x + 1 - 3 >= 0) && !(((x1 <= x + 1 - 3) && (x + 1 - 3 <= x2) && (y1 <= y) && (y <= y2)) ||
                              ((x3 <= x + 1 - 3) && (x + 1 - 3 <= x4) && (y3 <= y) && (y <= y4))))
        direction.push_back(-2);
    if ((x + 3 <= 10) && !(((x1 <= x + 3) && (x + 3 <= x2) && (y1 <= y) && (y <= y2)) ||
                           ((x3 <= x + 3) && (x + 3 <= x4) && (y3 <= y) && (y <= y4))))
        direction.push_back(2);
    if ((y + 3 <= 10) && !(((y1 <= y + 3) && (y + 3 <= y2) && (x1 <= x) && (x <= x2)) ||
                           ((y3 <= y + 3) && (y + 3 <= y4) && (x3 <= x) && (x <= x4))))
        direction.push_back(-1);
    if ((y + 1 - 3 >= 0) && !(((y1 <= y + 1 - 3) && (y + 1 - 3 <= y2) && (x1 <= x) && (x <= x2)) ||
                              ((y3 <= y + 1 - 3) && (y + 1 - 3 <= y4) && (x3 <= x) && (x <= x4))))
        direction.push_back(1);

    g = direction.size();
    c = rand() % (g - 1 - 0 + 1) + 0;
    int x5, y5;
    int x6, y6;
    switch (direction[c]) {
        case -2:
            for (int i = x - 2; i <= x; i++) {
                table[i][y] = '1';
            }
            x5 = x - 3;
            y5 = y - 1;
            x6 = x + 1;
            y6 = y + 1;
            break;
        case 2:
            for (int i = x; i <= x + 2; i++) {
                table[i][y] = '1';
            }
            x5 = x - 1;
            y5 = y - 1;
            x6 = x + 3;
            y6 = y + 1;
            break;
        case 1:
            for (int i = y - 2; i <= y; i++) {
                table[x][i] = '1';
            }
            x5 = x - 1;
            y5 = y - 3;
            x6 = x + 1;
            y6 = y + 1;
            break;
        case -1:
            for (int i = y; i <= y + 2; i++) {
                table[x][i] = '1';
            }
            x5 = x - 1;
            y5 = y - 1;
            x6 = x + 1;
            y6 = y + 3;
            break;
    }

    // introducing the first 2-decked ship

    while (1) {
        x = rand() % (9 - 0 + 1) + 0;
        y = rand() % (9 - 0 + 1) + 0;
        if (!(((x1 <= x) && (x <= x2) && (y1 <= y) && (y <= y2)) ||
              ((x3 <= x) && (x <= x4) && (y3 <= y) && (y <= y4)) ||
              ((x5 <= x) && (x <= x6) && (y5 <= y) && (y <= y6)))) {
            break;
        }
    }

    direction.clear();
    if ((x + 1 - 2 >= 0) && !(((x1 <= x + 1 - 2) && (x + 1 - 2 <= x2) && (y1 <= y) && (y <= y2)) ||
                              ((x3 <= x + 1 - 2) && (x + 1 - 2 <= x4) && (y3 <= y) && (y <= y4)) ||
                              ((x5 <= x + 1 - 2) && (x + 1 - 2 <= x6) && (y5 <= y) && (y <= y6))))
        direction.push_back(-2);
    if ((x + 2 <= 10) && !(((x1 <= x + 2) && (x + 2 <= x2) && (y1 <= y) && (y <= y2)) ||
                           ((x3 <= x + 2) && (x + 2 <= x4) && (y3 <= y) && (y <= y4)) ||
                           ((x5 <= x + 2) && (x + 2 <= x6) && (y5 <= y) && (y <= y6))))
        direction.push_back(2);
    if ((y + 2 <= 10) && !(((y1 <= y + 2) && (y + 2 <= y2) && (x1 <= x) && (x <= x2)) ||
                           ((y3 <= y + 2) && (y + 2 <= y4) && (x3 <= x) && (x <= x4)) ||
                           ((y5 <= y + 2) && (y + 2 <= y6) && (x5 <= x) && (x <= x6))))
        direction.push_back(-1);
    if ((y + 1 - 2 >= 0) && !(((y1 <= y + 1 - 2) && (y + 1 - 2 <= y2) && (x1 <= x) && (x <= x2)) ||
                              ((y3 <= y + 1 - 2) && (y + 1 - 2 <= y4) && (x3 <= x) && (x <= x4)) ||
                              ((y5 <= y + 1 - 2) && (y + 1 - 2 <= y6) && (x5 <= x) && (x <= x6))))
        direction.push_back(1);

    g = direction.size();
    c = rand() % (g - 1 - 0 + 1) + 0;
    int x7, y7;
    int x8, y8;
    switch (direction[c]) {
        case -2:
            for (int i = x - 1; i <= x; i++) {
                table[i][y] = '1';
            }
            x7 = x - 3;
            y7 = y - 1;
            x8 = x + 1;
            y8 = y + 1;
            break;
        case 2:
            for (int i = x; i <= x + 1; i++) {
                table[i][y] = '1';
            }
            x7 = x - 1;
            y7 = y - 1;
            x8 = x + 3;
            y8 = y + 1;
            break;
        case 1:
            for (int i = y - 1; i <= y; i++) {
                table[x][i] = '1';
            }
            x7 = x - 1;
            y7 = y - 3;
            x8 = x + 1;
            y8 = y + 1;
            break;
        case -1:
            for (int i = y; i <= y + 1; i++) {
                table[x][i] = '1';
            }
            x7 = x - 1;
            y7 = y - 1;
            x8 = x + 1;
            y8 = y + 3;
            break;
    }

    // introducing the second 2-decked ship

    while (1) {
        x = rand() % (9 - 0 + 1) + 0;
        y = rand() % (9 - 0 + 1) + 0;
        if (!(((x1 <= x) && (x <= x2) && (y1 <= y) && (y <= y2)) ||
              ((x3 <= x) && (x <= x4) && (y3 <= y) && (y <= y4)) ||
              ((x5 <= x) && (x <= x6) && (y5 <= y) && (y <= y6)) ||
              ((x7 <= x) && (x <= x8) && (y7 <= y) && (y <= y8)))) {
            break;
        }
    }

    direction.clear();
    if ((x + 1 - 2 >= 0) && !(((x1 <= x + 1 - 2) && (x + 1 - 2 <= x2) && (y1 <= y) && (y <= y2)) ||
                              ((x3 <= x + 1 - 2) && (x + 1 - 2 <= x4) && (y3 <= y) && (y <= y4)) ||
                              ((x5 <= x + 1 - 2) && (x + 1 - 2 <= x6) && (y5 <= y) && (y <= y6)) ||
                              ((x7 <= x + 1 - 2) && (x + 1 - 2 <= x8) && (y7 <= y) && (y <= y8))))
        direction.push_back(-2);
    if ((x + 2 <= 10) && !(((x1 <= x + 2) && (x + 2 <= x2) && (y1 <= y) && (y <= y2)) ||
                           ((x3 <= x + 2) && (x + 2 <= x4) && (y3 <= y) && (y <= y4)) ||
                           ((x5 <= x + 2) && (x + 2 <= x6) && (y5 <= y) && (y <= y6)) ||
                           ((x7 <= x + 2) && (x + 2 <= x8) && (y7 <= y) && (y <= y8))))
        direction.push_back(2);
    if ((y + 2 <= 10) && !(((y1 <= y + 2) && (y + 2 <= y2) && (x1 <= x) && (x <= x2)) ||
                           ((y3 <= y + 2) && (y + 2 <= y4) && (x3 <= x) && (x <= x4)) ||
                           ((y5 <= y + 2) && (y + 2 <= y6) && (x5 <= x) && (x <= x6)) ||
                           ((y7 <= y + 2) && (y + 2 <= y8) && (x7 <= x) && (x <= x8))))
        direction.push_back(-1);
    if ((y + 1 - 2 >= 0) && !(((y1 <= y + 1 - 2) && (y + 1 - 2 <= y2) && (x1 <= x) && (x <= x2)) ||
                              ((y3 <= y + 1 - 2) && (y + 1 - 2 <= y4) && (x3 <= x) && (x <= x4)) ||
                              ((y5 <= y + 1 - 2) && (y + 1 - 2 <= y6) && (x5 <= x) && (x <= x6)) ||
                              ((y7 <= y + 1 - 2) && (y + 1 - 2 <= y8) && (x7 <= x) && (x <= x8))))
        direction.push_back(1);

    g = direction.size();
    c = rand() % (g - 1 - 0 + 1) + 0;
    int x9, y9;
    int x10, y10;
    switch (direction[c]) {
        case -2:
            for (int i = x - 1; i <= x; i++) {
                table[i][y] = '1';
            }
            x9 = x - 3;
            y9 = y - 1;
            x10 = x + 1;
            y10 = y + 1;
            break;
        case 2:
            for (int i = x; i <= x + 1; i++) {
                table[i][y] = '1';
            }
            x9 = x - 1;
            y9 = y - 1;
            x10 = x + 3;
            y10 = y + 1;
            break;
        case 1:
            for (int i = y - 1; i <= y; i++) {
                table[x][i] = '1';
            }
            x9 = x - 1;
            y9 = y - 3;
            x10 = x + 1;
            y10 = y + 1;
            break;
        case -1:
            for (int i = y; i <= y + 1; i++) {
                table[x][i] = '1';
            }
            x9 = x - 1;
            y9 = y - 1;
            x10 = x + 1;
            y10 = y + 3;
            break;
    }

    // introducing the third 2-decked ship

    while (1) {
        x = rand() % (9 - 0 + 1) + 0;
        y = rand() % (9 - 0 + 1) + 0;
        if (!(((x1 <= x) && (x <= x2) && (y1 <= y) && (y <= y2)) ||
              ((x3 <= x) && (x <= x4) && (y3 <= y) && (y <= y4)) ||
              ((x5 <= x) && (x <= x6) && (y5 <= y) && (y <= y6)) ||
              ((x7 <= x) && (x <= x8) && (y7 <= y) && (y <= y8)) ||
              ((x9 <= x) && (x <= x10) && (y9 <= y) && (y <= y10)))) {
            break;
        }
    }

    direction.clear();
    if ((x + 1 - 2 >= 0) && !(((x1 <= x + 1 - 2) && (x + 1 - 2 <= x2) && (y1 <= y) && (y <= y2)) ||
                              ((x3 <= x + 1 - 2) && (x + 1 - 2 <= x4) && (y3 <= y) && (y <= y4)) ||
                              ((x5 <= x + 1 - 2) && (x + 1 - 2 <= x6) && (y5 <= y) && (y <= y6)) ||
                              ((x7 <= x + 1 - 2) && (x + 1 - 2 <= x8) && (y7 <= y) && (y <= y8)) ||
                              ((x9 <= x + 1 - 2) && (x + 1 - 2 <= x10) && (y9 <= y) && (y <= y10))))
        direction.push_back(-2);
    if ((x + 2 <= 10) && !(((x1 <= x + 2) && (x + 2 <= x2) && (y1 <= y) && (y <= y2)) ||
                           ((x3 <= x + 2) && (x + 2 <= x4) && (y3 <= y) && (y <= y4)) ||
                           ((x5 <= x + 2) && (x + 2 <= x6) && (y5 <= y) && (y <= y6)) ||
                           ((x7 <= x + 2) && (x + 2 <= x8) && (y7 <= y) && (y <= y8)) ||
                           ((x9 <= x + 2) && (x + 2 <= x10) && (y9 <= y) && (y <= y10))))
        direction.push_back(2);
    if ((y + 2 <= 10) && !(((y1 <= y + 2) && (y + 2 <= y2) && (x1 <= x) && (x <= x2)) ||
                           ((y3 <= y + 2) && (y + 2 <= y4) && (x3 <= x) && (x <= x4)) ||
                           ((y5 <= y + 2) && (y + 2 <= y6) && (x5 <= x) && (x <= x6)) ||
                           ((y7 <= y + 2) && (y + 2 <= y8) && (x7 <= x) && (x <= x8)) ||
                           ((y9 <= y + 2) && (y + 2 <= y10) && (x9 <= x) && (x <= x10))))
        direction.push_back(-1);
    if ((y + 1 - 2 >= 0) && !(((y1 <= y + 1 - 2) && (y + 1 - 2 <= y2) && (x1 <= x) && (x <= x2)) ||
                              ((y3 <= y + 1 - 2) && (y + 1 - 2 <= y4) && (x3 <= x) && (x <= x4)) ||
                              ((y5 <= y + 1 - 2) && (y + 1 - 2 <= y6) && (x5 <= x) && (x <= x6)) ||
                              ((y7 <= y + 1 - 2) && (y + 1 - 2 <= y8) && (x7 <= x) && (x <= x8)) ||
                              ((y9 <= y + 1 - 2) && (y + 1 - 2 <= y10) && (x9 <= x) && (x <= x10))))
        direction.push_back(1);

    g = direction.size();
    c = rand() % (g - 1 - 0 + 1) + 0;
    int x11, y11;
    int x12, y12;
    switch (direction[c]) {
        case -2:
            for (int i = x - 1; i <= x; i++) {
                table[i][y] = '1';
            }
            x11 = x - 3;
            y11 = y - 1;
            x12 = x + 1;
            y12 = y + 1;
            break;
        case 2:
            for (int i = x; i <= x + 1; i++) {
                table[i][y] = '1';
            }
            x11 = x - 1;
            y11 = y - 1;
            x12 = x + 3;
            y12 = y + 1;
            break;
        case 1:
            for (int i = y - 1; i <= y; i++) {
                table[x][i] = '1';
            }
            x11 = x - 1;
            y11 = y - 3;
            x12 = x + 1;
            y12 = y + 1;
            break;
        case -1:
            for (int i = y; i <= y + 1; i++) {
                table[x][i] = '1';
            }
            x11 = x - 1;
            y11 = y - 1;
            x12 = x + 1;
            y12 = y + 3;
            break;
    }

    // introducing the first 1-decked ship

    while (1) {
        x = rand() % (9 - 0 + 1) + 0;
        y = rand() % (9 - 0 + 1) + 0;
        if (!(((x1 <= x) && (x <= x2) && (y1 <= y) && (y <= y2)) ||
              ((x3 <= x) && (x <= x4) && (y3 <= y) && (y <= y4)) ||
              ((x5 <= x) && (x <= x6) && (y5 <= y) && (y <= y6)) ||
              ((x7 <= x) && (x <= x8) && (y7 <= y) && (y <= y8)) ||
              ((x9 <= x) && (x <= x10) && (y9 <= y) && (y <= y10)) ||
              ((x11 <= x) && (x <= x12) && (y11 <= y) && (y <= y12)))) {
            break;
        }
    }

    direction.clear();

    int x13, y13;
    int x14, y14;
    table[x][y] = '1';
    x13 = x - 1;
    y13 = y - 1;
    x14 = x + 1;
    y14 = y + 1;

    // introducing the second 1-decked ship

    while (1) {
        x = rand() % (9 - 0 + 1) + 0;
        y = rand() % (9 - 0 + 1) + 0;
        if (!(((x1 <= x) && (x <= x2) && (y1 <= y) && (y <= y2)) ||
              ((x3 <= x) && (x <= x4) && (y3 <= y) && (y <= y4)) ||
              ((x5 <= x) && (x <= x6) && (y5 <= y) && (y <= y6)) ||
              ((x7 <= x) && (x <= x8) && (y7 <= y) && (y <= y8)) ||
              ((x9 <= x) && (x <= x10) && (y9 <= y) && (y <= y10)) ||
              ((x11 <= x) && (x <= x12) && (y11 <= y) && (y <= y12)) ||
              ((x13 <= x) && (x <= x14) && (y13 <= y) && (y <= y14)))) {
            break;
        }
    }

    direction.clear();

    int x15, y15;
    int x16, y16;
    table[x][y] = '1';
    x15 = x - 1;
    y15 = y - 1;
    x16 = x + 1;
    y16 = y + 1;

    // introducing the third 1-decked ship

    while (1) {
        x = rand() % (9 - 0 + 1) + 0;
        y = rand() % (9 - 0 + 1) + 0;
        if (!(((x1 <= x) && (x <= x2) && (y1 <= y) && (y <= y2)) ||
              ((x3 <= x) && (x <= x4) && (y3 <= y) && (y <= y4)) ||
              ((x5 <= x) && (x <= x6) && (y5 <= y) && (y <= y6)) ||
              ((x7 <= x) && (x <= x8) && (y7 <= y) && (y <= y8)) ||
              ((x9 <= x) && (x <= x10) && (y9 <= y) && (y <= y10)) ||
              ((x11 <= x) && (x <= x12) && (y11 <= y) && (y <= y12)) ||
              ((x13 <= x) && (x <= x14) && (y13 <= y) && (y <= y14)) ||
              ((x15 <= x) && (x <= x16) && (y15 <= y) && (y <= y16)))) {
            break;
        }
    }

    direction.clear();

    int x17, y17;
    int x18, y18;
    table[x][y] = '1';
    x17 = x - 1;
    y17 = y - 1;
    x18 = x + 1;
    y18 = y + 1;

    // introducing the fourth 1-decked ship

    while (1) {
        x = rand() % (9 - 0 + 1) + 0;
        y = rand() % (9 - 0 + 1) + 0;
        if (!(((x1 <= x) && (x <= x2) && (y1 <= y) && (y <= y2)) ||
              ((x3 <= x) && (x <= x4) && (y3 <= y) && (y <= y4)) ||
              ((x5 <= x) && (x <= x6) && (y5 <= y) && (y <= y6)) ||
              ((x7 <= x) && (x <= x8) && (y7 <= y) && (y <= y8)) ||
              ((x9 <= x) && (x <= x10) && (y9 <= y) && (y <= y10)) ||
              ((x11 <= x) && (x <= x12) && (y11 <= y) && (y <= y12)) ||
              ((x13 <= x) && (x <= x14) && (y13 <= y) && (y <= y14)) ||
              ((x15 <= x) && (x <= x16) && (y15 <= y) && (y <= y16)) ||
              ((x17 <= x) && (x <= x18) && (y17 <= y) && (y <= y18)))) {
            break;
        }
    }

    direction.clear();

    table[x][y] = '1';

    std::string final_field;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            final_field += table[i][j];
        }
        final_field += '\n';
    }

    return final_field;
}