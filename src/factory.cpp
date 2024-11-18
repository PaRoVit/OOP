#include "../include/factory.hpp"
#include "../include/visitor.hpp"
#include "../include/observer.hpp"
#include "../include/bear.hpp"
#include "../include/outlaw.hpp"
#include "../include/werewolf.hpp"

std::shared_ptr<NPC> createNPC(const std::string &name, std::istream &inputStream, const std::string &filename) {
    std::shared_ptr<NPC> npc;
    int type = 0;

    if (inputStream >> type) {
        switch (type) {
            case BearType:
                npc = std::make_shared<Bear>(name, inputStream);
                break;
            case OutlawType:
                npc = std::make_shared<Outlaw>(name, inputStream);
                break;
            case WerewolfType:
                npc = std::make_shared<Werewolf>(name, inputStream);
                break;
            default:
                std::cerr << "Unknown NPC type: " << type << std::endl;
                return nullptr;
        }
    }

    if (npc) {
        npc->addObserver(ConsoleObserver::createInstance());
        npc->addObserver(FileObserver::createInstance(filename));
    }

    return npc;
}

std::shared_ptr<NPC> createNPC(NpcType type, const std::string &name, int x, int y, const std::string &filename) {
    std::shared_ptr<NPC> npc;

    switch (type) {
        case BearType:
            npc = std::make_shared<Bear>(name, x, y);
            break;
        case OutlawType:
            npc = std::make_shared<Outlaw>(name, x, y);
            break;
        case WerewolfType:
            npc = std::make_shared<Werewolf>(name, x, y);
            break;
        default:
            std::cerr << "Unknown NPC type: " << type << std::endl;
            return nullptr;
    }

    if (npc) {
        npc->addObserver(ConsoleObserver::createInstance());
        npc->addObserver(FileObserver::createInstance(filename));
    }

    return npc;
}

NPCSet simulateBattles(const NPCSet &NPCs, size_t distance) {
    NPCSet defeatedCharacters;

    for (const auto &attacker : NPCs) {
        for (const auto &defender : NPCs) {
            if (attacker != defender && attacker->isWithinDistance(defender, distance)) {
                NPCVisitor visitor(attacker);
                bool result = defender->acceptVisitor(visitor);

                if (result) {
                    defeatedCharacters.insert(defender);
                }
            }
        }
    }

    return defeatedCharacters;
}

void save(const NPCSet &NPCs, const std::string &filename) {
    std::ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        std::cerr << "Failed to open log file for saving: " << filename << std::endl;
        return;
    }

    outputFile << NPCs.size() << std::endl;

    for (const auto &character : NPCs) {
        character->save(outputFile);
    }
}

NPCSet load(const std::string &name, const std::string &filename) {
    NPCSet characters;
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Failed to open log file for loading: " << filename << std::endl;
        return characters;
    }

    int characterCount;
    inputFile >> characterCount;

    for (int i = 0; i < characterCount; ++i) {
        auto character = createNPC(name, inputFile, filename);
        if (character) {
            characters.insert(character);
        }
    }

    return characters;
}

std::ostream &operator<<(std::ostream &outputStream, const NPCSet &NPCs) {
    for (const auto &character : NPCs) {
        character->display();
    }
    return outputStream;
}