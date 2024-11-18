#pragma once

#include <memory>

class NPC;
class Bear;
class Outlaw;
class Werewolf;

class Visitor {
public:
    virtual ~Visitor() = default;

    virtual bool visit(Bear& bear) = 0;
    virtual bool visit(Outlaw& outlaw) = 0;
    virtual bool visit(Werewolf& werewolf) = 0;
};

class NPCVisitor : public Visitor {
public:
    NPCVisitor(std::shared_ptr<NPC> attacker);
    
    bool visit(Bear& bear) override;
    bool visit(Outlaw& outlaw) override;
    bool visit(Werewolf& werewolf) override;

private:
    std::shared_ptr<NPC> attacker_;
};