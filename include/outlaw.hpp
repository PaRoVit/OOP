#pragma once

#include "npc.hpp"
#include "visitor.hpp"

class Outlaw : public NPC {
public:
    Outlaw(const std::string &name, int x, int y);
    Outlaw(const std::string &name, std::istream &inputStream);

    void display() override;
    
    std::string getType() const override;

    bool kill(std::shared_ptr<Outlaw> other) override;
    bool kill(std::shared_ptr<Werewolf> other) override;
    bool kill(std::shared_ptr<Bear> other) override;

    void save(std::ostream &outputStream) override;

    bool acceptVisitor(Visitor &visitor) override;

    friend std::ostream &operator<<(std::ostream &outputStream, Outlaw &outlaw);
};