#include "../include/bear.hpp"
#include "../include/outlaw.hpp"
#include "../include/werewolf.hpp"

Outlaw::Outlaw(const std::string &name, int x, int y) : NPC(OutlawType, name, x, y) {}
Outlaw::Outlaw(const std::string &name, std::istream &is) : NPC(OutlawType, name, is) {}

void Outlaw::display() {
    std::cout << *this;
}

bool Outlaw::kill(std::shared_ptr<Bear> other) {
    notifyBattleObservers(other, true);
    return true;
}

bool Outlaw::kill(std::shared_ptr<Werewolf> other) {
    notifyBattleObservers(other, false);
    return false;
}

bool Outlaw::kill(std::shared_ptr<Outlaw> other) {
    notifyBattleObservers(other, false);
    return false;
}

void Outlaw::save(std::ostream &outputStream) {
    outputStream << OutlawType << std::endl;
    NPC::save(outputStream);
}

bool Outlaw::acceptVisitor(const std::shared_ptr<NPC> &visitor) {
    return visitor->kill(std::shared_ptr<Outlaw>(this,[](Outlaw*){}));;
}

std::ostream &operator<<(std::ostream &os, Outlaw &outlaw) {
    os << "outlaw: " << *static_cast<NPC *>(&outlaw) << std::endl;
    return os;
}