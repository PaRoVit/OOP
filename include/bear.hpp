#pragma once

#include "npc.hpp"
#include "visitor.hpp"

class Bear : public NPC {
public:
    Bear(const std::string &name, int x, int y);
    Bear(const std::string &name, std::istream &inputStream);

    void display() override;
    
    std::string getType() const override;

    bool kill(std::shared_ptr<Outlaw> other) override;
    bool kill(std::shared_ptr<Werewolf> other) override;
    bool kill(std::shared_ptr<Bear> other) override;

    void save(std::ostream &outputStream) override;

    bool acceptVisitor(Visitor &visitor) override;

    friend std::ostream &operator<<(std::ostream &outputStream, Bear &bear);
};