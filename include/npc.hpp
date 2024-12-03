#pragma once

#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <fstream>
#include <set>
#include <random>
#include <memory>
#include <shared_mutex>




class NPC;
class Bear;
class Outlaw;
class Werewolf;
using set_t = std::set<std::shared_ptr<NPC>>;

enum NpcType {
    Unknown = 0,
    BearType = 1,
    OutlawType = 2,
    WerewolfType = 3
};

class IBattleObserver {
public:
    virtual void handleBattle(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool isWin) = 0;
};

class NPC {
private:
    std::mutex mtx;
    NpcType type;
    std::string name;
    int x{0};
    int y{0};
    bool alive = true;
    std::vector<std::shared_ptr<IBattleObserver>> battleObservers;

public:
    NPC(NpcType type, const std::string &_name, int _x, int _y);
    NPC(NpcType type, const std::string &_name, std::istream &inputStream);

    const std::string &getName() const;
    NpcType getType();
    std::pair<int, int> position();

    void addObserver(std::shared_ptr<IBattleObserver> observer);
    void notifyBattleObservers(const std::shared_ptr<NPC>& defender, bool isWin);
    virtual bool isWithinDistance(const std::shared_ptr<NPC> &other, size_t distance);

    virtual bool kill(std::shared_ptr<class Bear> opponent) = 0;
    virtual bool kill(std::shared_ptr<class Outlaw> opponent) = 0;
    virtual bool kill(std::shared_ptr<class Werewolf> opponent) = 0;

    virtual void display() = 0;
    virtual void save(std::ostream &outputStream);
    virtual bool acceptVisitor(const std::shared_ptr<NPC> &visitor) = 0;

    void move(int shift_x, int shift_y, int max_x, int max_y);
    bool isAlive();
    void mustDie();

    friend std::ostream &operator<<(std::ostream &outputStream, NPC &npc);

    ~NPC() = default;
};

std::shared_ptr<NPC> createNPC(const std::string &name, std::istream &is, const std::string &filename);
std::shared_ptr<NPC> createNPC(NpcType type, const std::string &name, int x, int y, const std::string &filename);

void save(const set_t &array, const std::string &filename);
set_t load(const std::string &name, const std::string &filename);
set_t simulateBattles(const set_t &array, size_t distance);

std::ostream &operator<<(std::ostream &os, const set_t &array);