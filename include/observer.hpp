#pragma once

#include <memory>
#include <string>
#include <fstream>
#include <mutex>
#include "npc.hpp"



class ConsoleObserver : public IBattleObserver {
public:
    static std::shared_ptr<IBattleObserver> createInstance() {
        static ConsoleObserver instance;
        return std::shared_ptr<IBattleObserver>(&instance, [](IBattleObserver *) {});
    }

    void handleBattle(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool isWin){
        if (isWin) {
            std::lock_guard<std::mutex> lck(std::mutex print_mutex);
            std::cout << std::endl << "Murder: --------" << std::endl;
            attacker->display();
            defender->display();
            std::cout << attacker->getName() << " killed " << defender->getName() << std::endl;
        }
    }
};


class FileObserver : public IBattleObserver {
private:
    std::ofstream file;
public:
    FileObserver(const std::string &filename) {
        file.open(filename, std::ios_base::app);
        if (!file.is_open()) {
            throw std::runtime_error("Error with opening the log file");
        }
    }

    static std::shared_ptr<IBattleObserver> createInstance(const std::string &filename) {
        return std::make_shared<FileObserver>(filename);
    }

    void handleBattle(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool isWin) {
        if (file.is_open()) {
            file << (isWin ? "[VICTORY]" : "[DEFEAT]") << " Battle Log:" << std::endl;
            file << attacker->getType() << " " << *attacker << std::endl;
            file << defender->getType() << " " << *defender << std::endl;
            file << attacker->getName() << (isWin ? " defeated " : " lost to ") 
                    << defender->getName() << std::endl;
        }
    }
    
    ~FileObserver(){
        if (file.is_open()) {
            file.close();
        }
    }
};