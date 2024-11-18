#include "../include/npc.hpp"

NPC::NPC(NpcType type, const std::string &_name, int _x, int _y) : type(type), name(_name), x(_x), y(_y) {}

NPC::NPC(NpcType type, const std::string &_name, std::istream &inputStream) : type(type), name(_name) {
    inputStream  >> name >> x >> y;
}

const std::string& NPC::getName() const { 
    return name; 
}

void NPC::addObserver(std::shared_ptr<IBattleObserver> observer) {
    battleObservers.push_back(observer);
}

void NPC::notifyBattleObservers(const std::shared_ptr<NPC>& opponent, bool result) {
    for (const auto &observer : battleObservers) {
        observer->handleBattle(shared_from_this(), opponent, result);
    }
}

bool NPC::isWithinDistance(const std::shared_ptr<NPC> &other, size_t distance) const {
    int dx = x - other->x;
    int dy = y - other->y;
    return (dx * dx + dy * dy) <= static_cast<int>(distance * distance);
}

void NPC::save(std::ostream &outputStream) {
    outputStream << name << " at {" << x << ", " << y << "} " << std::endl;
}

std::ostream &operator<<(std::ostream &outputStream, NPC &npc) {
    outputStream << npc.name << " at {" << npc.x << ", " << npc.y << "} ";
    return outputStream;
}