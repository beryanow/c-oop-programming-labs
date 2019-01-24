#include "resolver_overall.h"

int main() {
    std::ifstream libs_in("libs.txt");
    std::vector<struct library> every_libs;
    filling_every_libs_up(libs_in, every_libs);

    std::ifstream targets_in("targets.txt");
    std::vector<struct target> every_targets;
    filling_every_targets_up(targets_in, every_targets);

    stack libs_indexes_set;
    stack indexes_set;

    int h = every_targets.size();

    finding_compatibilities(every_targets, h, libs_indexes_set, indexes_set, every_libs);
    finding_conflicts(every_targets, h, every_libs, libs_indexes_set);
    finding_unsuitable_dependencies_version(every_libs, libs_indexes_set);
    finding_unsuitable_conflicts_version(every_libs, libs_indexes_set);
    checking_for_existence(h, every_targets, every_libs, libs_indexes_set);
    checking_for_validity(every_targets, every_libs, std::cout);
    controlling_dependencies(every_targets, every_libs);
    exploring_kinds(every_targets, every_libs);
    showing_results(every_libs, std::cout);

    return 0;
}
