#ifndef UNTITLED1_FUNCTIONS_H

#define UNTITLED1_FUNCTIONS_H

#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <algorithm>

bool sort_rep(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b);

int input_check(int argc, char *argv[], int &amount, int &repetitions, std::ostream &out);

std::vector<std::pair<std::string, int>> make_phrases(int amount, std::istream& stream);

void print_res (std::vector<std::pair<std::string, int>> phrases, int repetitions, std::ostream &out);

#endif

