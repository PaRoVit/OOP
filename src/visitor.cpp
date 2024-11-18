#include "../include/npc.hpp"
#include "../include/visitor.hpp"
#include "../include/bear.hpp"
#include "../include/outlaw.hpp"
#include "../include/werewolf.hpp"

NPCVisitor::NPCVisitor(std::shared_ptr<NPC> attacker) : attacker_(attacker) {}

bool NPCVisitor::visit(Bear& bear) {
    return attacker_->kill(std::make_shared<Bear>(bear));
}

bool NPCVisitor::visit(Outlaw& outlaw) {
    return attacker_->kill(std::make_shared<Outlaw>(outlaw));
}

bool NPCVisitor::visit(Werewolf& werewolf) {
    return attacker_->kill(std::make_shared<Werewolf>(werewolf));
}