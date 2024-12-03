#include "../include/bear.hpp"
#include "../include/outlaw.hpp"
#include "../include/werewolf.hpp"

Bear::Bear(const std::string &name, int x, int y) : NPC(BearType, name, x, y) {}
Bear::Bear(const std::string &name, std::istream &is) : NPC(BearType, name, is) {}

void Bear::display() {
    std::cout << *this;
}

bool Bear::kill(std::shared_ptr<Werewolf> other) {
    notifyBattleObservers(other, true);
    return true;
}

bool Bear::kill(std::shared_ptr<Bear> other) {
    notifyBattleObservers(other, false);
    return false;
}

bool Bear::kill(std::shared_ptr<Outlaw> other) {
    notifyBattleObservers(other, false);
    return false;
}

void Bear::save(std::ostream &outputStream) {
    outputStream << BearType << std::endl;
    NPC::save(outputStream);
}

bool Bear::acceptVisitor(const std::shared_ptr<NPC> &visitor) {
    return visitor->kill(std::shared_ptr<Bear>(this,[](Bear*){}));;
}

std::ostream &operator<<(std::ostream &os, Bear &bear) {
    os << "bear: " << *static_cast<NPC *>(&bear) << std::endl;
    return os;
}