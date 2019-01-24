#include "functions.h"

using std::vector;
using std::pair;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

bool sort_rep(const pair<string, int> &a, const pair<string, int> &b) {
    return (a.second > b.second);
}

int input_check(int argc, char *argv[], int &amount, int &repetitions, ostream &out) {
    switch (argc) {
        case 1:
            break;
        case 2:
            break;
        case 4:
            if (argv[1][1] == 'n')
                amount = atoi(argv[2]);
            else
                repetitions = atoi(argv[2]);
            break;
        case 6:
            if (argv[1][1] == 'n') {
                amount = atoi(argv[2]);
                repetitions = atoi(argv[4]);
            } else {
                repetitions = atoi(argv[2]);
                amount = atoi(argv[4]);
            }
            break;
        default: {
            out << "Incorrect input data" << endl;
            return 1;
        }
    }

    if ((amount < 1) || (repetitions < 1)) {
        out << "Incorrect input data" << endl;
        return 1;
    }

    return 0;
}

vector<pair<string, int>> make_phrases(int amount, istream &stream) {
    vector<pair<string, int>> phrases;

    int m = 0;
    int y = 1;

    auto *words = new string[amount];

    stream >> words[m];

    while (stream) {
        if (m == amount - 1) {
            string phrase;
            for (int k = 0; k < amount; k++) {
                phrase += words[k];
                if (k != amount - 1)
                    phrase += " ";
            }

            unsigned long f = phrases.size();
            if (f != 0) {
                for (int i = 0; i < f; i++) {
                    if (phrases[i].first == phrase) {
                        (phrases[i].second)++;
                        break;
                    }
                    if (i == f - 1) {
                        phrases.reserve(f + 1);
                        phrases.emplace_back(phrase, 1);
                    }
                }
            } else {
                phrases.reserve(1);
                phrases.emplace_back(phrase, 1);
            }

            for (int j = 0; j < amount - 1; j++) {
                words[j] = words[j + 1];
            }
            m--;
        }
        m++;
        stream >> words[m];

    }

    delete[] words;

    sort(phrases.begin(), phrases.end(), sort_rep);

    return phrases;
}

void print_res(vector<pair<string, int>> phrases, int repetitions, std::ostream &out) {
    unsigned long f = phrases.size();

    for (int i = 0; i < f; i++) {
        if (phrases[i].second >= repetitions) {
            out << phrases[i].first << "(" << phrases[i].second << ")" << endl;
        }
    }
}