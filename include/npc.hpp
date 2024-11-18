#pragma once

#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <fstream>
#include <set>
#include <random>
#include <memory>
#include <time.h>
#include "observer.hpp"

class NPC;
class Bear;
class Outlaw;
class Werewolf;
class Visitor;
using set_t = std::set<std::shared_ptr<NPC>>;

enum NpcType {
    Unknown = 0,
    BearType = 1,
    OutlawType = 2,
    WerewolfType = 3
};

class NPC: public std::enable_shared_from_this<NPC> {
private:
    NpcType type;
    std::string name;
    int x{0};
    int y{0};

protected:
    void notifyBattleObservers(const std::shared_ptr<NPC>& opponent, bool result);

public:
    std::vector<std::shared_ptr<IBattleObserver>> battleObservers;

    NPC(NpcType type, const std::string &_name, int _x, int _y);
    NPC(NpcType type, const std::string &_name, std::istream &inputStream);
    
    const std::string& getName() const;
    virtual std::string getType() const = 0;
    
    void addObserver(std::shared_ptr<IBattleObserver> observer);

    virtual bool isWithinDistance(const std::shared_ptr<NPC> &other, size_t distance) const;

    virtual bool kill(std::shared_ptr<Bear> opponent) = 0;
    virtual bool kill(std::shared_ptr<Outlaw> opponent) = 0;
    virtual bool kill(std::shared_ptr<Werewolf> opponent) = 0;

    virtual void display() = 0;
    
    virtual void save(std::ostream &outputStream);

    virtual bool acceptVisitor(Visitor &visitor) = 0;

    friend std::ostream &operator<<(std::ostream &outputStream, NPC &npc);

    virtual ~NPC() = default;
};