#pragma once

#include "npc.hpp"

class Outlaw : public NPC {
public:
    Outlaw(const std::string &name, int x, int y);
    Outlaw(const std::string &name, std::istream &inputStream);

    void display() override;

    bool kill(std::shared_ptr<Outlaw> other) override;
    bool kill(std::shared_ptr<Werewolf> other) override;
    bool kill(std::shared_ptr<Bear> other) override;

    void save(std::ostream &outputStream) override;

    bool acceptVisitor(const std::shared_ptr<NPC> &visitor) override;

    friend std::ostream &operator<<(std::ostream &outputStream, Outlaw &outlaw);
};