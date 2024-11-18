#pragma once

#include <memory>
#include <string>
#include <fstream>

class NPC;

class IBattleObserver {
public:
    virtual ~IBattleObserver() = default;
    virtual void handleBattle(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool isWin) = 0;
};

class ConsoleObserver : public IBattleObserver {
public:
    static std::shared_ptr<IBattleObserver> createInstance();
    void handleBattle(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool isWin) override;
};

class FileObserver : public IBattleObserver {
private:
    std::ofstream file;
public:
    FileObserver(const std::string &filename);
    static std::shared_ptr<IBattleObserver> createInstance(const std::string &filename);
    void handleBattle(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool isWin) override;
    ~FileObserver();
};