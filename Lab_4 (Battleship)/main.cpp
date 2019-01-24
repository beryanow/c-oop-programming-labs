#include "battle_header.h"

int main() {
    std::string message;
    std::cin >> message;
    Initializer game;
    Field instructions;
    while ((message != "Win!") && (message != "Lose")) {
        if (message == "Arrange!") {
            std::string field = create_table();
            std::cout << field;
        } else if (message == "Shoot!") {
            std::cout << instructions.Shot();
        } else if (message == "Miss") {
            instructions.Missed();
        } else if (message == "Hit") {
            std::cout << instructions.Hit();
        } else if (message == "Kill") {
            std::cout << instructions.Killed();
        }
        std::cin >> message;
    }
    return 0;
}