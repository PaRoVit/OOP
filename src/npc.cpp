#include "../include/npc.hpp"
#include "../include/observer.hpp"
#include "../include/bear.hpp"       // Включаем полное определение Bear
#include "../include/outlaw.hpp"     // Включаем полное определение Outlaw
#include "../include/werewolf.hpp"

NPC::NPC(NpcType type, const std::string &_name, int _x, int _y) : type(type), name(_name), x(_x), y(_y) {}

NPC::NPC(NpcType type, const std::string &_name, std::istream &inputStream) : type(type), name(_name) {
    inputStream  >> name >> x >> y;
}

const std::string& NPC::getName() const { 
    return name; 
}

NpcType NPC::getType() {
    std::lock_guard<std::mutex> lck(mtx);
    return type;
}

std::pair<int, int> NPC::position() {
    std::lock_guard<std::mutex> lck(mtx);
    return {x, y};
}

void NPC::addObserver(std::shared_ptr<IBattleObserver> observer) {
    battleObservers.push_back(observer);
}

void NPC::notifyBattleObservers(const std::shared_ptr<NPC>& defender, bool isWin) {
    for (const auto &observer : battleObservers) {
        observer->handleBattle(std::shared_ptr<NPC>(this, [](NPC *) {}), defender, isWin);
    }
}

bool NPC::isWithinDistance(const std::shared_ptr<NPC> &other, size_t distance){
    auto [other_x, other_y] = other->position();
    std::lock_guard<std::mutex> lck(mtx);
    if ((std::pow(x - other_x, 2) + std::pow(y - other_y, 2)) <= std::pow(distance, 2)) {
        return true;
    } else {
        return false;
    }
}

void NPC::save(std::ostream &outputStream) {
    outputStream << name << " at {" << x << ", " << y << "} " << std::endl;
}

void NPC::move(int shift_x, int shift_y, int max_x, int max_y) {
    std::lock_guard<std::mutex> lck(mtx);

    if ((x + shift_x >= 0) && (x + shift_x <= max_x))
        x += shift_x;
    if ((y + shift_y >= 0) && (y + shift_y <= max_y))
        y += shift_y;
}

bool NPC::isAlive() {
    std::lock_guard<std::mutex> lck(mtx);
    return alive;
}

void NPC::mustDie() {
    std::lock_guard<std::mutex> lck(mtx);
    alive = false;
}

std::ostream &operator<<(std::ostream &outputStream, NPC &npc) {
    outputStream << npc.name << " at {" << npc.x << ", " << npc.y << "} ";
    return outputStream;
}

std::shared_ptr<NPC> createNPC(const std::string &name, std::istream &inputStream, const std::string &filename) {
    std::shared_ptr<NPC> npc;
    int type = 0;

    if (inputStream >> type) {
        switch (type) {
            case BearType:
                npc = std::make_shared<Bear>(name, inputStream);
                break;
            case OutlawType:
                npc = std::make_shared<Outlaw>(name, inputStream);
                break;
            case WerewolfType:
                npc = std::make_shared<Werewolf>(name, inputStream);
                break;
            default:
                std::cerr << "Unknown NPC type: " << type << std::endl;
                return nullptr;
        }
    }

    if (npc) {
        npc->addObserver(ConsoleObserver::createInstance());
        npc->addObserver(FileObserver::createInstance(filename));
    }

    return npc;
}

std::shared_ptr<NPC> createNPC(NpcType type, const std::string &name, int x, int y, const std::string &filename) {
    std::shared_ptr<NPC> npc;

    switch (type) {
        case BearType:
            npc = std::make_shared<Bear>(name, x, y);
            break;
        case OutlawType:
            npc = std::make_shared<Outlaw>(name, x, y);
            break;
        case WerewolfType:
            npc = std::make_shared<Werewolf>(name, x, y);
            break;
        default:
            std::cerr << "Unknown NPC type: " << type << std::endl;
            return nullptr;
    }

    if (npc) {
        npc->addObserver(ConsoleObserver::createInstance());
        npc->addObserver(FileObserver::createInstance(filename));
    }

    return npc;
}

void save(const set_t &array, const std::string &filename) {
    std::ofstream fs(filename);
    fs << array.size() << std::endl;
    for (auto &n : array)
        n->save(fs);
    fs.flush();
    fs.close();
}

set_t simulateBattles(const set_t &NPCs, size_t distance) {
    set_t defeatedCharacters;

    for (const auto &attacker : NPCs) {
        for (const auto &defender : NPCs) {
            if (attacker != defender && attacker->isWithinDistance(defender, distance) && defender->acceptVisitor(attacker)) {
                defeatedCharacters.insert(defender);
            }
        }
    }

    return defeatedCharacters;
}

set_t load(const std::string &name, const std::string &filename) {
    set_t result;
    std::ifstream is(filename);
    if (is.good() && is.is_open()) {
        int count;
        is >> count;
        for (int i = 0; i < count; ++i)
            result.insert(createNPC(name, is, filename));
        is.close();
    } else {
        std::cerr << "Error: " << std::strerror(errno) << std::endl;
    }
    return result;
}

std::ostream &operator<<(std::ostream &outputStream, const set_t &array) {
    for (auto &n : array)
        n->display();
    return outputStream;
}