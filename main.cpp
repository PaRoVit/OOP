#include <iostream>
#include "include/observer.hpp"
#include "include/visitor.hpp"
#include "include/factory.hpp"
#include "include/bear.hpp"
#include "include/outlaw.hpp"
#include "include/werewolf.hpp"

int main() {
    NPCSet characters;

    std::string characterNames[10] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" };

    std::srand(time(NULL));
    for (size_t i = 0; i < 10; ++i) {
        auto characterType = static_cast<NpcType>(std::rand() % 3 + 1);
        characters.insert(createNPC(characterType, characterNames[i], std::rand() % 500, std::rand() % 500, "log.txt"));
    }
    std::cout << "Saving characters..." << std::endl;
    save(characters, "log.txt");

    std::cout << "Starting battles..." << std::endl;
    std::cout << characters;
 
    for (size_t distance = 20; (distance <= 100) && !characters.empty(); distance += 10) {
        auto defeatedCharacters = simulateBattles(characters, distance);

        // Удаление побежденных
        for (const auto &defeated : defeatedCharacters) {
            characters.erase(defeated);
        }

        std::cout << "\nBattle summary ----------" << std::endl
                  << "Distance: " << distance << std::endl
                  << "Defeated: " << defeatedCharacters.size() << std::endl
                  << std::endl;
    }

    // Вывод выживших
    std::cout << "Surviving characters:\n" << characters;

    return 0;

}