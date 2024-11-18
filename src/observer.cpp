#include "../include/observer.hpp"
#include "../include/npc.hpp"

std::shared_ptr<IBattleObserver> ConsoleObserver::createInstance() {
    static ConsoleObserver instance;
    return std::shared_ptr<IBattleObserver>(&instance, [](IBattleObserver *) {});
}

std::shared_ptr<IBattleObserver> FileObserver::createInstance(const std::string &filename) {
    return std::make_shared<FileObserver>(filename);
}

void ConsoleObserver::handleBattle(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool isWin) {
    std::cout << (isWin ? "[VICTORY]" : "[DEFEAT]") << " Battle log:" << std::endl;
    attacker->display();
    defender->display();std::cout << attacker->getName() << (isWin ? " defeated " : " lost to ") 
              << defender->getName() << std::endl;
}

FileObserver::FileObserver(const std::string &filename) {
    file.open(filename, std::ios_base::app);
    if (!file.is_open()) {
        throw std::runtime_error("Error with opening the log file");
    }
}

void FileObserver::handleBattle(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool isWin) {
    if (file.is_open()) {
        file << (isWin ? "[VICTORY]" : "[DEFEAT]") << " Battle Log:" << std::endl;
        file << attacker->getType() << " " << *attacker << std::endl;
        file << defender->getType() << " " << *defender << std::endl;
        file << attacker->getName() << (isWin ? " defeated " : " lost to ") 
                << defender->getName() << std::endl;
    }
}

FileObserver::~FileObserver() {
    if (file.is_open()) {
        file.close();
    }
}