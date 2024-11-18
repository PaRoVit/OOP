#include "../include/bear.hpp"
#include "../include/outlaw.hpp"
#include "../include/werewolf.hpp"

Werewolf::Werewolf(const std::string &name, int x, int y) : NPC(WerewolfType, name, x, y) {}
Werewolf::Werewolf(const std::string &name, std::istream &is) : NPC(WerewolfType, name, is) {}

void Werewolf::display() {
    std::cout << *this;
}

std::string Werewolf::getType() const {
    return "Werewolf";
}

bool Werewolf::kill(std::shared_ptr<Outlaw> other) {
    notifyBattleObservers(other, true);
    return true;
}

bool Werewolf::kill(std::shared_ptr<Werewolf> other) {
    notifyBattleObservers(other, false);
    return false;
}

bool Werewolf::kill(std::shared_ptr<Bear> other) {
    notifyBattleObservers(other, false);
    return false;
}

void Werewolf::save(std::ostream &outputStream) {
    outputStream << WerewolfType << std::endl;
    NPC::save(outputStream);
}

bool Werewolf::acceptVisitor(Visitor &visitor) {
    return visitor.visit(*this);
}

std::ostream &operator<<(std::ostream &os, Werewolf &werewolf) {
    os << "werewolf: " << *static_cast<NPC *>(&werewolf) << std::endl;
    return os;
}