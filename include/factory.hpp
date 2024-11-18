#pragma once

#include <iostream>
#include <fstream>
#include <set>
#include <memory>
#include "npc.hpp"

std::shared_ptr<NPC> createNPC(const std::string &name, std::istream &inputStream, const std::string &filename);
std::shared_ptr<NPC> createNPC(NpcType type, const std::string &name, int x, int y, const std::string &filename);

using NPCSet = std::set<std::shared_ptr<NPC>>;

NPCSet simulateBattles(const NPCSet &NPCs, size_t distance);

void save(const NPCSet &NPCs, const std::string &filename);
NPCSet load(const std::string &name, const std::string &filename);

std::ostream &operator<<(std::ostream &outputStreamos, const NPCSet &NPCs);