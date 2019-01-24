#include "functions.h"

using std::vector;
using std::pair;
using std::string;
using std::cin;
using std::cout;
using std::endl;

int main(int argc, char *argv[]) {

    int repetitions = 2;
    int amount = 2;

    if (!input_check(argc, argv, amount, repetitions, cout)) {
        if (argc != 1) {
            if (strcmp(argv[argc - 1], "-"))
                freopen(argv[argc - 1], "r", stdin);
        }
        vector<pair<string, int>> phrases = make_phrases(amount, cin);
        print_res(phrases, repetitions, cout);
    }

    return 0;
}
