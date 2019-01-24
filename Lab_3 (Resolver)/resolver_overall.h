#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>

template<typename T>
class version {
    T cmp;
public:
    version<T> &operator=(T m) {
        cmp = m;
        return (*this);
    };

    bool operator<(version<T> to_cmp) {
        return (this->give() < to_cmp.give());
    };

    bool operator<=(version<T> to_cmp) {
        return (this->give() <= to_cmp.give());
    };

    bool operator>=(version<T> to_cmp) {
        return (this->give() >= to_cmp.give());
    };

    bool operator>(version<T> to_cmp) {
        return (this->give() > to_cmp.give());
    };

    bool operator==(version<T> to_cmp) {
        return (this->give() == to_cmp.give());
    };

    bool operator!=(version<T> to_cmp) {
        return (this->give() != to_cmp.give());
    };

    bool operator==(T l) {
        return (this->give() == l);
    };

    version<T> operator>>(std::istringstream l) {
        this->cmp = l.str();
        return (*this);
    };

    T give() {
        return cmp;
    };
};

struct library {
    std::string name;
    version<std::string> vers;
    std::vector<std::pair<std::string, std::pair<version<std::string>, version<std::string>>>> dependencies;
    std::vector<std::pair<std::string, std::pair<version<std::string>, version<std::string>>>> conflicts;
    int compatibility;
    int kind;
};

struct target {
    std::string name;
    std::pair<version<std::string>, version<std::string>> borders;
};

class stack {
    int amount;
    std::vector<int> arr;
public:
    void push(int x);
    void pop();
    stack();
    void clear();
    std::vector<int> give();
};

void collecting_stack_dependencies_deeper(stack &libs_indexes_set, int &m, int u, std::vector<struct library> &every_libs);
void collecting_stack_dependencies(stack &libs_indexes_set, int &m, std::vector<struct library> &every_libs, std::string needed_name, version<std::string> needed_border_1, version<std::string> needed_border_2);
void collecting_stack_conflicts(stack &libs_indexes_set, int &m, std::vector<struct library> &every_libs, std::string needed_name, version<std::string> needed_version, std::string orig_name, version<std::string> orig_version);
void rechecking(stack &indexes_set, stack &libs_indexes_set, int &m, std::vector<struct library> &every_libs, std::string needed_name, version<std::string> needed_border_1, version<std::string> needed_border_2);
void rechecking_deeper(stack &indexes_set, stack &libs_indexes_set, int &m, int u, std::vector<struct library> &every_libs);
void checking_for_validity(std::vector<struct target> &every_targets, std::vector<struct library> &every_libs, std::ostream &out);
bool find_elem(stack &libs_indexes_set, int x);
bool comp_less(int u, std::vector<struct library> &every_libs, version<std::string> needed_border_2);
bool comp_more(int u, std::vector<struct library> &every_libs, version<std::string> needed_border_1);
void find(std::vector<struct library> &every_libs, std::vector<std::pair<std::string, int>> &arr, int z, int f);
void filling_every_libs_up(std::istream &stream, std::vector<struct library> &every_libs);
void filling_every_targets_up(std::istream &stream, std::vector<struct target> &every_targets);
void finding_compatibilities(std::vector<struct target> &every_targets, int h, stack &libs_indexes_set, stack &indexes_set, std::vector<struct library> &every_libs);
void finding_conflicts(std::vector<struct target> &every_targets, int h, std::vector<struct library> &every_libs, stack &libs_indexes_set);
void finding_unsuitable_dependencies_version(std::vector<struct library> &every_libs, stack &libs_indexes_set);
void finding_unsuitable_conflicts_version(std::vector<struct library> &every_libs, stack &libs_indexes_set);
void checking_for_existence(int h, std::vector<struct target> &every_targets, std::vector<struct library> &every_libs, stack &libs_indexes_set);
void exploring_kinds(std::vector<struct target> &every_targets, std::vector<struct library> &every_libs);
void showing_results(std::vector<struct library> &every_libs, std::ostream &out);
void controlling_dependencies(std::vector<struct target> &every_targets, std::vector<struct library> &every_libs);
bool if_already_used(std::string needed_name, std::vector<std::pair<std::string, int>> arr3);
bool cmp_less(version<std::string> needed_border_1, version<std::string> needed_version);
bool cmp_more(version<std::string> needed_border_2, version<std::string> needed_version);