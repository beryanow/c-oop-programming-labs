#include "resolver_overall.h"

void collecting_stack_dependencies_deeper(stack &libs_indexes_set, int &m, int u, std::vector<struct library> &every_libs) {
    int l = every_libs.at(u).dependencies.size();
    for (int p = 0; p < l; p++) {
        std::string needed_name = every_libs.at(u).dependencies.at(p).first;
        version<std::string> needed_border_1 = every_libs.at(u).dependencies.at(p).second.first;
        version<std::string> needed_border_2 = every_libs.at(u).dependencies.at(p).second.second;
        collecting_stack_dependencies(libs_indexes_set, m, every_libs, needed_name, needed_border_1, needed_border_2);
    }
}

void collecting_stack_dependencies(stack &libs_indexes_set, int &m, std::vector<struct library> &every_libs, std::string needed_name, version<std::string> needed_border_1, version<std::string> needed_border_2) {
    int g = every_libs.size();
    for (int u = 0; u < g; u++) {
        if ((every_libs.at(u).name == needed_name) && (comp_less(u, every_libs, needed_border_2)) &&
            (comp_more(u, every_libs, needed_border_1))) {
            if (find_elem(libs_indexes_set, u)) {
                break;
            }
            libs_indexes_set.push(u);
            collecting_stack_dependencies_deeper(libs_indexes_set, m, u, every_libs);
        }
    }

}

void rechecking_deeper(stack &indexes_set, stack &libs_indexes_set, int &m, int u, std::vector<struct library> &every_libs) {
    int l = every_libs.at(u).dependencies.size();
    for (int p = 0; p < l; p++) {
        std::string needed_name = every_libs.at(u).dependencies.at(p).first;
        version<std::string> needed_border_1 = every_libs.at(u).dependencies.at(p).second.first;
        version<std::string> needed_border_2 = every_libs.at(u).dependencies.at(p).second.second;
        rechecking(indexes_set, libs_indexes_set, m, every_libs, needed_name, needed_border_1, needed_border_2);
    }
}

void rechecking(stack &indexes_set, stack &libs_indexes_set, int &m, std::vector<struct library> &every_libs, std::string needed_name, version<std::string> needed_border_1, version<std::string> needed_border_2) {
    int g = every_libs.size();
    for (int u = 0; u < g; u++) {
        if (find_elem(libs_indexes_set, u)) {
            continue;
        }
        if ((every_libs.at(u).name == needed_name) && (comp_less(u, every_libs, needed_border_2)) &&
            (comp_more(u, every_libs, needed_border_1))) {
            if (find_elem(indexes_set, u)) {
                break;
            }
            indexes_set.push(u);
            rechecking_deeper(indexes_set, libs_indexes_set, m, u, every_libs);
        }
    }

}

bool cmp_less(version<std::string> needed_border_1, version<std::string> needed_version) {
    if (needed_border_1 == "-")
        return true;
    return (needed_border_1 <= needed_version);
}

bool cmp_more(version<std::string> needed_border_2, version<std::string> needed_version) {
    if (needed_border_2 == "-")
        return true;
    return (needed_version <= needed_border_2);
}


void collecting_stack_conflicts(stack &libs_indexes_set, int &m, std::vector<struct library> &every_libs, std::string needed_name, version<std::string> needed_version, std::string orig_name, version<std::string> orig_version) {
    int g = every_libs.size();
    for (int u = 0; u < g; u++) {
        int k = every_libs.at(u).conflicts.size();
        for (int i = 0; i < k; i++) {
            if ((every_libs.at(u).conflicts.at(i).first == needed_name)) {
                version<std::string> needed_border_1 = every_libs.at(u).conflicts.at(i).second.first;
                version<std::string> needed_border_2 = every_libs.at(u).conflicts.at(i).second.second;
                if ((cmp_less(needed_border_1, needed_version)) && (cmp_more(needed_border_2, needed_version))) {
                    every_libs.at(u).compatibility = 0;
                    libs_indexes_set.push(u);
                }

                int n = every_libs.at(u).dependencies.size();
                for (int y = 0; y < n; y++) {
                    std::string name_pursued = every_libs.at(u).dependencies.at(y).first;
                    version<std::string> version_pursued_b_1 = every_libs.at(u).dependencies.at(y).second.first;
                    version<std::string> version_pursued_b_2 = every_libs.at(u).dependencies.at(y).second.second;

                    for (int l = 0; l < g; l++) {
                        if ((every_libs.at(l).name == name_pursued) &&
                            (comp_less(l, every_libs, version_pursued_b_2)) &&
                            (comp_more(l, every_libs, version_pursued_b_1))) {
                            if (every_libs.at(l).vers >= version_pursued_b_1) {
                                every_libs.at(l).compatibility = 0;
                            }
                        }
                    }
                }
                break;
            }
        }
    }
}

void filling_every_libs_up(std::istream &stream, std::vector<struct library> &every_libs) {
    int g = 0;
    int f = 0;

    std::string libs_name;
    std::string libs_version;

    stream >> libs_name >> libs_version;
    every_libs.resize(g + 1);
    every_libs.at(g).name = libs_name;
    every_libs.at(g).vers = libs_version;

    while (stream) {
        std::string probability;
        stream >> probability;
        std::string str;

        if (probability == "+") {
            getline(stream, str);
            std::istringstream cin_tmp(str);

            std::string name_dep;
            cin_tmp >> name_dep;

            int k = count(str.begin(), str.end(), ' ');
            int h = every_libs.at(g).dependencies.size();
            int h1 = -1;
            for (int i = 0; i < h; i++) {
                if (every_libs.at(g).dependencies.at(i).first == name_dep) {
                    h1 = i;
                    break;
                }
            }
            if (h1 == -1) {
                every_libs.at(g).dependencies.resize(h + 1);
                every_libs.at(g).dependencies.at(h).first = name_dep;
                every_libs.at(g).dependencies.at(h).second.first = "-";
                every_libs.at(g).dependencies.at(h).second.second = "-";
                h1 = h;
            }

            if (k > 1) {
                cin_tmp >> probability;
                if (probability == ">=") {
                    cin_tmp >> probability;
                    every_libs.at(g).dependencies.at(h1).second.first = probability;
                } else if (probability == "<=") {
                    cin_tmp >> probability;
                    every_libs.at(g).dependencies.at(h1).second.second = probability;
                } else if (probability == ">") {
                    cin_tmp >> probability;
                    probability = probability + '.' + '1';
                    every_libs.at(g).dependencies.at(h1).second.first = probability;
                } else if (probability == "<") {
                    cin_tmp >> probability;
                    size_t probability_size = probability.size();
                    for (int z = probability_size - 1; z >= 0; z -= 2) {
                        if (probability[z] - (size_t) '0' != 0) {
                            probability[z] = (char) (probability[z] - 1);
                            break;
                        } else {
                            probability[z] = (char) (probability[z] + 9);
                        }
                    }
                    every_libs.at(g).conflicts.at(h1).second.second = probability;
                }
                f = 1;
            } else f = 0;
        }

        if (probability == "-") {
            getline(stream, str);
            std::istringstream cin_tmp(str);

            std::string name_conf;
            cin_tmp >> name_conf;

            int k = count(str.begin(), str.end(), ' ');
            int h = every_libs.at(g).conflicts.size();
            int h1 = -1;
            for (int i = 0; i < h; i++) {
                if (every_libs.at(g).conflicts.at(i).first == name_conf) {
                    h1 = i;
                    break;
                }
            }
            if (h1 == -1) {
                every_libs.at(g).conflicts.resize(h + 1);
                every_libs.at(g).conflicts.at(h).first = name_conf;
                every_libs.at(g).conflicts.at(h).second.first = "-";
                every_libs.at(g).conflicts.at(h).second.second = "-";
                h1 = h;
            }

            if (k > 1) {
                cin_tmp >> probability;
                if (probability == ">=") {
                    cin_tmp >> probability;
                    every_libs.at(g).conflicts.at(h1).second.first = probability;
                } else if (probability == "<=") {
                    cin_tmp >> probability;
                    every_libs.at(g).conflicts.at(h1).second.second = probability;
                } else if (probability == ">") {
                    cin_tmp >> probability;
                    probability = probability + '.' + '1';
                    every_libs.at(g).conflicts.at(h1).second.first = probability;
                } else if (probability == "<") {
                    cin_tmp >> probability;
                    size_t probability_size = probability.size();
                    for (int z = probability_size - 1; z >= 0; z -= 2) {
                        if (probability[z] - (size_t) '0' != 0) {
                            probability[z] = (char) (probability[z] - 1);
                            break;
                        } else {
                            probability[z] = (char) (probability[z] + 9);
                        }
                    }
                    every_libs.at(g).conflicts.at(h1).second.second = probability;
                }

                f = 1;
            } else f = 0;

        }

        if ((f == 0) && (probability != "-") && (probability != "+")) {
            if (!stream)
                break;
            g++;
            every_libs.resize(g + 1);
            every_libs.at(g).name = probability;

            std::string t;
            stream >> t;
            every_libs.at(g).vers = t;
            f = 0;
        }

        if (f != 0)
            f--;
    }
    stream.clear();
}

void filling_every_targets_up(std::istream &stream, std::vector<struct target> &every_targets) {
    std::string probability;
    stream >> probability;

    while (stream) {
        int h = every_targets.size();
        int h1 = -1;
        for (int i = 0; i < h; i++) {
            if (every_targets.at(i).name == probability) {
                h1 = i;
                break;
            }
        }

        if (h1 == -1) {
            every_targets.resize(h + 1);
            every_targets.at(h).name = probability;
            every_targets.at(h).borders.first = "-";
            every_targets.at(h).borders.second = "-";
            h1 = h;
        }

        std::string str;
        getline(stream, str);

        int k = count(str.begin(), str.end(), ' ');
        std::istringstream cin_tmp(str);
        std::string name_bord;

        if (k > 1) {
            cin_tmp >> name_bord;

            if (name_bord == ">=") {
                cin_tmp >> name_bord;
                every_targets.at(h1).borders.first = name_bord;
            } else if (name_bord == "<=") {
                cin_tmp >> name_bord;
                every_targets.at(h1).borders.second = name_bord;
            } else if (name_bord == ">") {
                cin_tmp >> name_bord;
                name_bord = name_bord + '.' + '1';
                every_targets.at(h1).borders.first = name_bord;
            } else if (name_bord == "<") {
                cin_tmp >> name_bord;
                size_t name_bord_size = name_bord.size();
                for (int z = name_bord_size - 1; z >= 0; z -= 2) {
                    if (name_bord[z] - (size_t) '0' != 0) {
                        name_bord[z] = (char) (name_bord[z] - 1);
                        break;
                    } else {
                        name_bord[z] = (char) (name_bord[z] + 9);
                    }
                }
                every_targets.at(h1).borders.second = name_bord;
            }
        }
        stream >> probability;
    }
};

void finding_compatibilities(std::vector<struct target> &every_targets, int h, stack &libs_indexes_set, stack &indexes_set, std::vector<struct library> &every_libs) {
    for (int y = 0; y < h; y++) {
        std::string needed_name = every_targets.at(y).name;
        version<std::string> needed_border_1 = every_targets.at(y).borders.first;
        version<std::string> needed_border_2 = every_targets.at(y).borders.second;
        int m = 0;
        collecting_stack_dependencies(libs_indexes_set, m, every_libs, needed_name, needed_border_1, needed_border_2);

        std::vector<int> l = libs_indexes_set.give();
        int v = l.size();
        for (int v1 = 0; v1 < v; v1++) {
            every_libs.at(l.at(v1)).compatibility = 1;
        }
        libs_indexes_set.clear();

        version<std::string> needed_version;

        std::string orig_name = needed_name;
        int z = every_libs.size();
        for (int r = 0; r < z; r++) {
            if ((every_libs.at(r).name == needed_name) && (every_libs.at(r).compatibility == 1)) {
                needed_version = every_libs.at(r).vers;
                version<std::string> orig_version = needed_version;
                collecting_stack_conflicts(libs_indexes_set, m, every_libs, needed_name, needed_version, orig_name,
                                           orig_version);
                break;
            }
        }
        indexes_set.clear();

        needed_name = every_targets.at(y).name;
        needed_border_1 = every_targets.at(y).borders.first;
        needed_border_2 = every_targets.at(y).borders.second;
        m = 0;
        rechecking(indexes_set, libs_indexes_set, m, every_libs, needed_name, needed_border_1, needed_border_2);

        l = indexes_set.give();
        v = l.size();
        for (int v1 = 0; v1 < v; v1++) {
            every_libs.at(l.at(v1)).compatibility = 1;
        }
        libs_indexes_set.clear();
        indexes_set.clear();
    }
    libs_indexes_set.clear();
}

void finding_conflicts(std::vector<struct target> &every_targets, int h, std::vector<struct library> &every_libs, stack &libs_indexes_set) {
    for (int y = 0; y < h; y++) {
        std::string needed_name = every_targets.at(y).name;
        version<std::string> needed_border_1 = every_targets.at(y).borders.first;
        version<std::string> needed_border_2 = every_targets.at(y).borders.second;

        int z = every_libs.size();
        for (int i = 0; i < z; i++) {
            if (every_libs.at(i).compatibility == 1) {
                if (((every_libs.at(i).name == needed_name) && !((comp_less(i, every_libs, needed_border_2)) && (comp_more(i, every_libs, needed_border_1))))) {
                    libs_indexes_set.push(i);
                }
            }
        }
    }
    std::vector<int> l = libs_indexes_set.give();
    int v = l.size();
    for (int v1 = 0; v1 < v; v1++) {
        every_libs.at(l.at(v1)).compatibility = 0;
    }
    libs_indexes_set.clear();
}

bool if_already_used(std::string needed_name, std::vector<std::pair<std::string, int>> arr3) {
    int k = arr3.size();
    for (int i = 0; i < k; i++) {
        if (arr3.at(i).first == needed_name) {
            if (arr3.at(i).second == 1)
                return true;
        }
    }
    return false;
}

void finding_unsuitable_dependencies_version(std::vector<struct library> &every_libs, stack &libs_indexes_set) {
    int x = 0;
    int t = 0;
    std::vector<std::pair<std::string, std::pair<version<std::string>, version<std::string>>>> arr2;
    std::vector<std::pair<std::string, int>> arr3;
    int z = every_libs.size();
    for (int i = 0; i < z; i++) {
        if (every_libs.at(i).compatibility == 1) {
            int h = every_libs.at(i).dependencies.size();
            for (int y = 0; y < h; y++) {
                arr2.resize(x + 1);
                arr2.at(x).first = every_libs.at(i).dependencies.at(y).first;
                arr2.at(x).second.first = every_libs.at(i).dependencies.at(y).second.first;
                arr2.at(x).second.second = every_libs.at(i).dependencies.at(y).second.second;
                int k = arr3.size();
                int v;
                for (v = 0; v < k; v++) {
                    if (arr3.at(v).first == arr2.at(x).first) {
                        break;
                    }
                }
                if (v == k) {
                    arr3.resize(t + 1);
                    arr3.at(t).first = arr2.at(x).first;
                    arr3.at(t).second = 0;
                    t++;
                }
                x++;
            }
        }
    }

    for (int y = 0; y < x; y++) {
        std::string needed_name = arr2.at(y).first;
        version<std::string> needed_border_1 = arr2.at(y).second.first;
        version<std::string> needed_border_2 = arr2.at(y).second.second;

        int z = every_libs.size();
        int m = 0;
        for (int i = 0; i < z; i++) {
            if (every_libs.at(i).compatibility == 1) {
                if (((every_libs.at(i).name == needed_name) && !((comp_less(i, every_libs, needed_border_2)) && (comp_more(i, every_libs, needed_border_1))))) {
                    if (!(if_already_used(needed_name, arr3)))
                        libs_indexes_set.push(i);
                    else
                        libs_indexes_set.push(y);
                    m = 1;
                    int k = arr3.size();
                    for (int h = 0; h < k; h++) {
                        if (arr3.at(h).first == needed_name) {
                            arr3.at(h).second = 1;
                        }
                    }
                }
            }
        }
        if (m == 0) {
            int k = arr3.size();
            for (int h = 0; h < k; h++) {
                if (arr3.at(h).first == needed_name) {
                    arr3.at(h).second = 1;
                }
            }
        }
    }

    std::vector<int> l = libs_indexes_set.give();
    int v = l.size();
    for (int v1 = 0; v1 < v; v1++) {
        every_libs.at(l.at(v1)).compatibility = 0;
    }
    libs_indexes_set.clear();
}

void finding_unsuitable_conflicts_version(std::vector<struct library> &every_libs, stack &libs_indexes_set) {
    int w = 0;
    std::vector<std::pair<std::string, std::pair<version<std::string>, version<std::string>>>> arr3;
    int z = every_libs.size();
    for (int i = 0; i < z; i++) {
        if (every_libs.at(i).compatibility == 1) {
            int h = every_libs.at(i).conflicts.size();
            for (int y = 0; y < h; y++) {
                arr3.resize(w + 1);
                arr3.at(w).first = every_libs.at(i).conflicts.at(y).first;
                arr3.at(w).second.first = every_libs.at(i).conflicts.at(y).second.first;
                arr3.at(w).second.second = every_libs.at(i).conflicts.at(y).second.second;
                w++;
            }
        }
    }

    for (int y = 0; y < w; y++) {
        std::string needed_name = arr3.at(y).first;
        version<std::string> needed_border_1 = arr3.at(y).second.first;
        version<std::string> needed_border_2 = arr3.at(y).second.second;

        int z = every_libs.size();
        for (int i = 0; i < z; i++) {
            if (every_libs.at(i).compatibility == 1) {
                if ((every_libs.at(i).name == needed_name) && (comp_less(i, every_libs, needed_border_2)) &&
                    (comp_more(i, every_libs, needed_border_1))) {
                    libs_indexes_set.push(i);
                }
            }
        }
    }

    std::vector<int> l = libs_indexes_set.give();
    int v = l.size();
    for (int v1 = 0; v1 < v; v1++) {
        every_libs.at(l.at(v1)).compatibility = 0;
    }
    libs_indexes_set.clear();
}

void checking_for_validity(std::vector<struct target> &every_targets, std::vector<struct library> &every_libs, std::ostream &out) {
    int j = every_targets.size();
    std::vector<std::pair<std::string, int>> arr;
    arr.resize(j);
    for (int i = 0; i < j; i++) {
        arr.at(i).first = every_targets.at(i).name;
        arr.at(i).second = 0;
    }

    int z = every_libs.size();
    for (int k = 0; k < j; k++) {
        for (int i = 0; i < z; i++) {
            if ((every_libs.at(i).compatibility == 1) && (every_libs.at(i).name == arr.at(k).first)) {
                arr.at(k).second = 1;
            }
        }
    }
    for (int i = 0; i < j; i++) {
        if (arr.at(i).second == 0) {
            try {
                throw std::logic_error("Unable to resolve targets.");
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what();
                exit(1);
            }
        }
    }
}

void checking_for_existence(int h, std::vector<struct target> &every_targets, std::vector<struct library> &every_libs, stack &libs_indexes_set) {
    for (int y = 0; y < h; y++) {
        std::string needed_name = every_targets.at(y).name;
        int z = every_libs.size();
        for (int i = 0; i < z; i++) {
            if ((every_libs.at(i).name == needed_name) && (every_libs.at(i).compatibility == 1)) {
                int f = every_libs.at(i).dependencies.size();
                std::vector<std::pair<std::string, int>> arr;
                arr.resize(f);
                for (int v = 0; v < f; v++) {
                    arr.at(v).first = every_libs.at(i).dependencies.at(v).first;
                    arr.at(v).second = 0;
                }

                find(every_libs, arr, z, f);
                for (int c = 0; c < f; c++) {
                    if (arr.at(c).second == 0) {
                        every_libs.at(i).compatibility = 0;
                        std::string needed_name = every_targets.at(y).name;
                        version<std::string> needed_border_1 = every_targets.at(y).borders.first;
                        version<std::string> needed_border_2 = every_targets.at(y).borders.second;
                        int m = 0;
                        collecting_stack_dependencies_deeper(libs_indexes_set, m, i, every_libs);

                        std::vector<int> l = libs_indexes_set.give();
                        int v = l.size();
                        for (int v1 = 0; v1 < v; v1++) {
                            every_libs.at(l.at(v1)).compatibility = 0;
                        }
                        libs_indexes_set.clear();
                    }
                }
            }
        }
    }
}

void controlling_dependencies(std::vector<struct target> &every_targets, std::vector<struct library> &every_libs) {
    int d = every_libs.size();
    int d1 = every_targets.size();
    for (int i = 0; i < d; i++) {
        if (every_libs.at(i).compatibility == 1) {
            int g = every_libs.at(i).dependencies.size();
            int m = 0;
            for (int y = 0; y < g; y++) {
                std::string name_check = every_libs.at(i).dependencies.at(y).first;
                version<std::string> border_1 = every_libs.at(i).dependencies.at(y).second.first;
                version<std::string> border_2 = every_libs.at(i).dependencies.at(y).second.second;
                for (int p = 0; p < d; p++) {
                    if (((every_libs.at(p).name == name_check) && (every_libs.at(p).compatibility == 1)) && ((comp_less(p, every_libs, border_2)) && (comp_more(p, every_libs, border_1)))) {
                        m = 1;
                    }
                }
                for (int k = 0; k < d1; k++) {
                    if (every_libs.at(i).name == every_targets.at(k).name) {
                        m = 1;
                        break;
                    }
                }
                try {
                    if (m == 0)
                        throw std::logic_error("Unable to resolve targets.");
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what();
                    exit(1);
                }
            }

            int x = every_libs.at(i).conflicts.size();
            int s = 0;
            for (int y = 0; y < x; y++) {
                std::string name_check = every_libs.at(i).conflicts.at(y).first;
                version<std::string> border_1 = every_libs.at(i).conflicts.at(y).second.first;
                version<std::string> border_2 = every_libs.at(i).conflicts.at(y).second.second;
                for (int p = 0; p < d; p++) {
                    if (((every_libs.at(p).name == name_check) && (every_libs.at(p).compatibility == 1)) && ((comp_less(p, every_libs, border_2)) && (comp_more(p, every_libs, border_1)))) {
                        try {
                            throw std::logic_error("Unable to resolve targets.");
                        }
                        catch(const std::exception& e)
                        {
                            std::cerr << e.what();
                            exit(1);
                        }
                    }
                }
            }
        }
    }
}

void exploring_kinds(std::vector<struct target> &every_targets, std::vector<struct library> &every_libs) {
    int a = 0;
    std::vector<std::pair<std::string, std::pair<version<std::string>, version<std::string>>>> arr5;
    int c = every_targets.size();
    for (int i = 0; i < c; i++) {
        arr5.resize(a + 1);
        arr5.at(a).first = every_targets.at(i).name;
        arr5.at(a).second.first = every_targets.at(i).borders.first;
        arr5.at(a).second.second = every_targets.at(i).borders.second;
        a++;
    }
    int b = every_libs.size();
    for (int i = 0; i < b; i++) {
        if (every_libs.at(i).compatibility == 1) {
            int h = every_libs.at(i).dependencies.size();
            for (int y = 0; y < h; y++) {
                arr5.resize(a + 1);
                arr5.at(a).first = every_libs.at(i).dependencies.at(y).first;
                arr5.at(a).second.first = every_libs.at(i).dependencies.at(y).second.first;
                arr5.at(a).second.second = every_libs.at(i).dependencies.at(y).second.second;
                a++;
            }
        }
    }

    int l1 = every_libs.size();
    int l2 = arr5.size();

    for (int u2 = 0; u2 < l2; u2++) {
        for (int u1 = 0; u1 < l1; u1++) {
            version<std::string> needed_border_1 = arr5.at(u2).second.first;
            version<std::string> needed_border_2 = arr5.at(u2).second.second;
            if ((every_libs.at(u1).compatibility == 1) && (arr5.at(u2).first == every_libs.at(u1).name) &&
                (comp_less(u1, every_libs, needed_border_2)) &&
                (comp_more(u1, every_libs, needed_border_1))) {
                every_libs.at(u1).kind = u2;
            }
        }
    }

    int y1 = every_libs.size();
    int y2 = arr5.size();
    for (int s2 = 0; s2 < y2; s2++) {
        version<std::string> max;
        max = "0.0";
        for (int s1 = 0; s1 < y1; s1++) {
            if ((every_libs.at(s1).compatibility == 1) && (every_libs.at(s1).kind == s2)) {
                if (every_libs.at(s1).vers > max) {
                    max = every_libs.at(s1).vers;
                }
            }
        }
        for (int s1 = 0; s1 < y1; s1++) {
            if ((every_libs.at(s1).compatibility == 1) && (every_libs.at(s1).kind == s2) &&
                (every_libs.at(s1).vers != max)) {
                every_libs.at(s1).compatibility = 0;
            }
        }
    }
}

void showing_results(std::vector<struct library> &every_libs, std::ostream &out) {
    int z = every_libs.size();
    int m = 0;
    for (int i = 0; i < z; i++) {
        if (every_libs.at(i).compatibility == 1) {
            m = 1;
        }
    }
    if (m == 0) {
        std::cerr << "Unable to resolve targets.";
        exit(1);
    } else
        for (int i = 0; i < z; i++) {
            if (every_libs.at(i).compatibility == 1) {
                out << every_libs.at(i).name << " " << every_libs.at(i).vers.give() << std::endl;
            }
        }
}
