#include "tritset.h"

tritset::tritset(unsigned int m) {
    if (m != 0) {
        if ((m - 1) / (sizeof(unsigned int) * 4) + 1 > array_size) {
            if (array_size) {
                unsigned int *new_array = new unsigned int[(m - 1) / (sizeof(unsigned int) * 4) + 1];
                for (int i = 0; i < array_size; i++) {
                    new_array[i] = array[i];
                }
                array = new_array;
                array_size = m / (sizeof(unsigned int) * 4);
            } else {
                unsigned int *new_array = new unsigned int[(m - 1) / (sizeof(unsigned int) * 4) + 1];
                for (int i = 0; i < (m - 1) / (sizeof(unsigned int) * 4) + 1; i++) {
                    new_array[i] = 0;
                }
                array = new_array;
                array_size = (m - 1) / (sizeof(unsigned int) * 4) + 1;
            }
        } else if (array == nullptr) {
            unsigned int *new_array = new unsigned int[1];
            new_array[0] = 0;
            array = new_array;
        }
    }
}

tritset::~tritset() {
    if (array_size)
        delete[] array;
}

void tritset::shrink() {
    unsigned int *new_array = new unsigned int[last_index + 1];
    for (int i = 0; i < last_index + 1; i++) {
        new_array[i] = 0;
    }
    if (array == nullptr) {
        new_array[0] = 0;
        array = new_array;
        array_size = 1;
        return;
    }
    for (int i = 0; i < last_index + 1; i++) {
        new_array[i] = array[i];
    }
    array = new_array;
    array_size = last_index + 1;
}

trit tritset::operator[](unsigned int m) const {
    unsigned int array_index = m / (sizeof(unsigned int) * 4);
    unsigned int trit_index = m % (sizeof(unsigned int) * 4);
    if (array_index >= array_size)
        return trit::t_unknown;

    unsigned int the_one = array[array_index];
    unsigned int rep_amount = sizeof(unsigned int) * 4 - 1 - trit_index;
    for (unsigned int i = 0; i < rep_amount; i++) {
        the_one >>= 2;
    }
    the_one &= 3;
    switch (the_one) {
        case 0:
            return trit::t_unknown;
        case 1:
            return trit::t_true;
        case 2:
            return trit::t_false;
        default:
            delete[] array;
            exit(1);
    }
}

tritset &tritset::operator=(const tritset &working_tritset) {
    if (this == &working_tritset) {
        return (*this);
    }
    unsigned int *new_array = new unsigned int[working_tritset.array_size];
    for (int i = 0; i < working_tritset.array_size; i++) {
        new_array[i] = working_tritset.array[i];
    }
    if (this->array_size != 0)
        delete [] this->array;

    this->array = new_array;
    this->last_index = working_tritset.last_index;
    this->array_size = working_tritset.array_size;

    return (*this);
}

void tritset::trim(unsigned int index) {
    for (unsigned int i = index; i < array_size * sizeof(unsigned int) * 4; i++) {
        (*this)[i] = trit::t_unknown;
    }

    unsigned int *new_array = new unsigned int[index / (sizeof(unsigned int) * 4) + 1];
    for (int i = 0; i < index / (sizeof(unsigned int) * 4) + 1; i++) {
        new_array[i] = array[i];
    }
    array = new_array;
    array_size = index / (sizeof(unsigned int) * 4) + 1;
}


tritset_proxy tritset::operator[](unsigned int m) {
    unsigned int array_index = m / (sizeof(unsigned int) * 4);
    unsigned int trit_index = m % (sizeof(unsigned int) * 4);
    tritset_proxy value(array_index, trit_index, this);

    return value;
}

tritset tritset::operator&(const tritset &working_tritset) const {
    tritset result, base;

    if (this->array_size >= working_tritset.array_size) {
        result = (*this);
        base = working_tritset;
    } else {
        result = working_tritset;
        base = (*this);
    }
    for (int i = 0; i < base.array_size * sizeof(unsigned int) * 8; i += 2) {
        if (base[i / 2] == trit::t_false) {
            result[i / 2] = trit::t_false;
        } else if (base[i / 2] == trit::t_unknown) {
            if (result[i / 2] == trit::t_true) {
                result[i / 2] = trit::t_unknown;
            }
        }
    }
    for (int i = base.array_size * sizeof(unsigned int) * 8; i < result.array_size * sizeof(unsigned int) * 8; i += 2) {
        if (result[i / 2] == trit::t_true)
            result[i / 2] = trit::t_unknown;
    }

    return result;
}

tritset &tritset::operator&=(const tritset &working_tritset) {
    tritset temp = ((*this) & working_tritset);
    *this = temp;
    return *this;
}

tritset tritset::operator|(const tritset &working_tritset) const {
    tritset result, base;

    if (this->array_size >= working_tritset.array_size) {
        result = (*this);
        base = working_tritset;
    } else {
        result = working_tritset;
        base = (*this);
    }
    for (int i = 0; i < base.array_size * sizeof(unsigned int) * 8; i += 2) {
        if (base[i / 2] == trit::t_true) {
            result[i / 2] = trit::t_true;
        } else if (base[i / 2] == trit::t_unknown) {
            if (result[i / 2] == trit::t_false) {
                result[i / 2] = trit::t_unknown;
            }
        }
    }
    for (int i = base.array_size * sizeof(unsigned int) * 8; i < result.array_size * sizeof(unsigned int) * 8; i += 2) {
        if (result[i / 2] == trit::t_false)
            result[i / 2] = trit::t_unknown;
    }

    return result;
}

tritset &tritset::operator|=(const tritset &working_tritset) {
    tritset temp = ((*this) | working_tritset);
    *this = temp;
    return *this;
}

tritset tritset::operator!() const {
    tritset base;

    base.array_size = this->array_size;
    base.last_index = this->last_index;
    unsigned int *new_array = new unsigned int[this->array_size];
    for (int i = 0; i < this->array_size; i++) {
        new_array[i] = this->array[i];
    }
    base.array = new_array;
    for (int i = 0; i < base.array_size * sizeof(unsigned int) * 8; i += 2) {
        if (base[i / 2] == trit::t_true) {
            base[i / 2] = trit::t_false;
        } else if (base[i / 2] == trit::t_false) {
            base[i / 2] = trit::t_true;
        }
    }

    return base;
}

unsigned int tritset::cardinality(trit value) const {
    unsigned int m = 0;
    if (value != trit::t_unknown) {
        for (int i = 0; i < array_size * sizeof(unsigned int) * 4; i++) {
            if ((*this)[i] == value) {
                m++;
            }
        }
    } else {
        for (int i = 0; i <= last_trit; i++) {
            if ((*this)[i] == value) {
                m++;
            }
        }
    }

    return m;
}

std::unordered_map<trit, int> tritset::cardinality() const {
    std::unordered_map<trit, int> trits_map;

    unsigned int false_amount = 0, unknown_amount = 0, true_amount = 0;

    for (int i = 0; i <= last_trit; i++) {
        if ((*this)[i] == trit::t_unknown) {
            unknown_amount++;
        } else if ((*this)[i] == trit::t_true) {
            true_amount++;
        } else false_amount++;
    }

    for (int i = last_trit + 1; i < array_size * sizeof(unsigned int) * 4; i++) {
        if ((*this)[i] == trit::t_true) {
            true_amount++;
        } else if ((*this)[i] == trit::t_false) {
            false_amount++;
        }
    }

    trits_map[trit::t_false] = false_amount;
    trits_map[trit::t_unknown] = unknown_amount;
    trits_map[trit::t_true] = true_amount;

    return trits_map;
}

unsigned int tritset::length() const {
    unsigned int m = 0;
    for (unsigned int i = 0; i < array_size * sizeof(unsigned int) * 4; i++) {
        if (((*this)[i] == trit::t_true) || ((*this)[i] == trit::t_false)) {
            m = i;
        }
    }

    return m;
}

trit operator&(const trit &a, const trit &b) {
    if ((a == trit::t_false) || (b == trit::t_false))
        return trit::t_false;
    if ((a == trit::t_true) && (b == trit::t_true))
        return trit::t_true;
    return trit::t_unknown;
}

trit operator|(const trit &a, const trit &b) {
    if ((a == trit::t_false) && (b == trit::t_false))
        return trit::t_false;
    if ((a == trit::t_true) || (b == trit::t_true))
        return trit::t_true;
    return trit::t_unknown;
}

trit operator!(const trit &a) {
    if (a == trit::t_true)
        return trit::t_false;
    if (a == trit::t_false)
        return trit::t_true;
    return trit::t_unknown;
}

std::ostream &operator<<(std::ostream &new_os, const trit &value) {
    switch (value) {
        case trit::t_false:
            new_os << "False";
            break;
        case trit::t_unknown:
            new_os << "Unknown";
            break;
        case trit::t_true:
            new_os << "True";
            break;
        default:
            new_os << "";
            break;
    }

    return new_os;
}

std::ostream &operator<<(std::ostream &new_os, tritset &working_tritset) {
    for (unsigned int i = 0; i <= working_tritset.length(); i++)
        if (working_tritset[i] == trit::t_false) {
            new_os << trit::t_false << ' ';
        } else if (working_tritset[i] == trit::t_unknown) {
            new_os << trit::t_unknown << ' ';
        } else new_os << trit::t_true << ' ';

    return new_os;
}

tritset::tritset(const std::initializer_list<trit> &list) {
    tritset(list.size());
    {
        int count = 0;
        int m = 0;
        for (auto &element : list) {
            operator[](m) = element;
//            operator=(element);
            m++;
        }
    };
}

void tritset_proxy::correct_array() {
    if (array_index >= pointer->array_size) {
        if (pointer->array_size) {
            unsigned int *new_array = new unsigned int[array_index + 1];
            for (int i = 0; i < pointer->array_size; i++) {
                new_array[i] = pointer->array[i];
            }
            for (int i = pointer->array_size; i < array_index + 1; i++) {
                new_array[i] = 0;
            }
            pointer->array = new_array;
            pointer->array_size = array_index + 1;
        } else {
            unsigned int *new_array = new unsigned int[array_index + 1];
            for (int i = 0; i < array_index + 1; i++) {
                new_array[i] = 0;
            }

            pointer->array = new_array;
            pointer->array_size = array_index + 1;
        }
    }
}

tritset_proxy &tritset_proxy::operator=(trit value) {
    unsigned int empty_one = 0;

    switch (value) {
        case trit::t_true:
            empty_one |= (1 << (sizeof(unsigned int) * 8 - 1 - trit_index * 2));
            empty_one |= (1 << (sizeof(unsigned int) * 8 - 2 - trit_index * 2));

            correct_array();
            pointer->array[array_index] &= ~empty_one;

            empty_one = 0;
            empty_one |= (1 << (sizeof(unsigned int) * 8 - 2 - trit_index * 2));
            pointer->array[array_index] |= empty_one;
            pointer->last_index = array_index;
            pointer->last_trit = trit_index;
            break;
        case trit::t_false:
            empty_one = 0;

            empty_one |= (1 << (sizeof(unsigned int) * 8 - 1 - trit_index * 2));
            empty_one |= (1 << (sizeof(unsigned int) * 8 - 2 - trit_index * 2));

            correct_array();
            pointer->array[array_index] &= ~empty_one;

            empty_one = 0;
            empty_one |= (1 << (sizeof(unsigned int) * 8 - 1 - trit_index * 2));
            pointer->array[array_index] |= empty_one;
            pointer->last_index = array_index;
            pointer->last_trit = trit_index;
            break;
        case trit::t_unknown:
            empty_one = 0;

            empty_one |= (1 << (sizeof(unsigned int) * 8 - 1 - trit_index * 2));
            empty_one |= (1 << (sizeof(unsigned int) * 8 - 2 - trit_index * 2));

            if (array_index < pointer->array_size) {
                correct_array();
                pointer->array[array_index] &= ~empty_one;
                pointer->last_index = array_index;
                pointer->last_trit = trit_index;
            }
            break;
        default:
            delete[] pointer->array;
            exit(1);
    }

    return *this;
}

bool tritset_proxy::operator==(trit value) const {
    if (array_index < pointer->array_size) {
        unsigned int the_one = pointer->array[array_index];
        unsigned int rep_amount = sizeof(unsigned int) * 4 - 1 - trit_index;
        for (unsigned int i = 0; i < rep_amount; i++) {
            the_one >>= 2;
        }
        the_one &= 3;
        switch (the_one) {
            case 2:
                return (trit::t_false == value);
            case 1:
                return (trit::t_true == value);
            case 0:
                return (trit::t_unknown == value);
            default:
                delete[] pointer->array;
                exit(1);
        }
    } else
        return false;
}