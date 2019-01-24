#pragma once

#include <iostream>
#include <unordered_map>
#include <sstream>

enum class trit {
    t_false, t_unknown, t_true
};

class tritset_proxy;

class tritset {
    friend class tritset_proxy;

    unsigned int *array;
    unsigned int array_size = 0, last_index = 0, last_trit = 0;

public:
    tritset() {}
    ~tritset();
    tritset(unsigned int m);
    tritset(const std::initializer_list<trit> &list);
    unsigned int capacity() {
        return array_size;
    }
    trit operator[](unsigned int m) const;
    tritset operator&(const tritset &working_tritset) const;
    tritset operator|(const tritset &working_tritset) const;
    tritset operator!() const;
    tritset &operator&=(const tritset &working_tritset);
    tritset &operator|=(const tritset &working_tritset);
    tritset &operator=(const tritset &working_tritset);
    tritset_proxy operator[](unsigned int m);
    std::unordered_map<trit, int> cardinality() const;
    unsigned int cardinality(trit value) const;
    void trim(unsigned int index);
    unsigned int length() const;
    void shrink();
};

class tritset_proxy {
    friend class tritset;

    unsigned int array_index, trit_index;
    tritset *pointer;
    void correct_array();
    tritset_proxy(unsigned int array_index_value, unsigned int trit_index_value, tritset *pointer_value)
            : array_index(array_index_value), trit_index(trit_index_value), pointer(pointer_value) {}

public:
    tritset_proxy &operator=(trit value);
    bool operator==(trit value) const;
    void operator==(tritset_proxy value) const {}
};

std::ostream &operator<<(std::ostream &new_os, tritset &working_tritset);
std::ostream &operator<<(std::ostream &new_os, const trit &value);
trit operator!(const trit &a);
trit operator|(const trit &a, const trit &b);
trit operator&(const trit &a, const trit &b);