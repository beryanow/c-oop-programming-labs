#include "resolver_overall.h"

void stack::push(int x) {
    amount++;
    arr.resize(amount - 1);
    arr.push_back(x);
}

void stack::pop() {
    if (amount != 0)
        amount--;
    arr.resize(amount);
}

stack::stack() {
    amount = 0;
}

void stack::clear() {
    amount = 0;
    arr.resize(0);
}

std::vector<int> stack::give() {
    return arr;
}

bool find_elem(stack &libs_indexes_set, int x) {
    std::vector<int> arr;
    arr = libs_indexes_set.give();
    auto it = find(arr.begin(), arr.end(), x);

    if (it != arr.end()) return true;
    return false;
}

bool comp_less(int u, std::vector<struct library> &every_libs, version<std::string> needed_border_2) {
    if (needed_border_2 == "-")
        return true;
    return (every_libs.at(u).vers <= needed_border_2);
}

bool comp_more(int u, std::vector<struct library> &every_libs, version<std::string> needed_border_1) {
    if (needed_border_1 == "-")
        return true;
    return (every_libs.at(u).vers >= needed_border_1);
}

void find(std::vector<struct library> &every_libs, std::vector<std::pair<std::string, int>> &arr, int z, int f) {
    for (int i = 0; i < f; i++) {
        for (int k = 0; k < z; k++) {
            if ((arr.at(i).first == every_libs.at(k).name) && (every_libs.at(k).compatibility == 1)) {
                arr.at(i).second = 1;
            }
        }
    }
}