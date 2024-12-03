#include "observer.hpp"
#include "npc.hpp"

#include <thread>
#include <chrono>
#include <queue>
#include <optional>
#include <array>
#include <sstream>
#include <mutex>
#include <shared_mutex>

using namespace std::chrono_literals;

std::mutex output_lock;

struct Logger : std::ostringstream {
    ~Logger() {
        std::lock_guard<std::mutex> lock(output_lock);
        std::cout << this->str() << std::flush;
    }
};

// Событие боя между двумя персонажами
struct BattleEvent {
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> target;
};

// Менеджер, управляющий очередью боевых событий
class BattleManager {
private:
    std::queue<BattleEvent> eventQueue;
    std::shared_mutex queueLock;

    BattleManager() {}

public:
    static BattleManager& instance() {
        static BattleManager instance;
        return instance;
    }

    void pushEvent(BattleEvent&& event) {
        std::lock_guard<std::shared_mutex> lock(queueLock);
        eventQueue.push(std::move(event));
    }

    void operator()() {
        while (true) {
            std::optional<BattleEvent> currentEvent;

            {
                std::lock_guard<std::shared_mutex> lock(queueLock);
                if (!eventQueue.empty()) {
                    currentEvent = std::move(eventQueue.front());
                    eventQueue.pop();
                }
            }

            if (currentEvent) {
                if (currentEvent->attacker->isAlive() &&
                    currentEvent->target->isAlive() &&
                    currentEvent->target->acceptVisitor(currentEvent->attacker)) {
                    currentEvent->target->mustDie();
                }
            } else {
                std::this_thread::sleep_for(1s);
            }
        }
    }
};

// Основной класс симуляции игры
class GameEngine {
private:
    static constexpr int GRID_WIDTH = 20;
    static constexpr int GRID_HEIGHT = 20;
    static constexpr int NPC_COUNT = 20;

    static constexpr int MAX_MOVE_BEAR = 20;
    static constexpr int MAX_MOVE_OUTLAW = 5;
    static constexpr int MAX_MOVE_WEREWOLF = 5;

    static constexpr int ATTACK_RANGE_BEAR = 10;
    static constexpr int ATTACK_RANGE_OUTLAW = 5;
    static constexpr int ATTACK_RANGE_WEREWOLF = 10;

    set_t npcSet;
    set_t survivors;

public:
    void initializeNPCs() {
        std::cout << "Initializing NPCs...\n";
        std::vector<std::string> names(50);

        std::srand(static_cast<unsigned>(time(nullptr)));

        for (int i = 0; i < 50; ++i) {
            char letter = 'A' + std::rand() % 26;
            names[i] = letter + std::to_string(i);
        }

        for (int i = 0; i < 50; ++i) {
            npcSet.insert(createNPC(NpcType(std::rand() % 3 + 1), names[i], std::rand() % GRID_WIDTH, std::rand() % GRID_HEIGHT, "log.txt"));
        }

        save(npcSet, "log.txt");

        std::cout << "Initial NPC list:\n" << npcSet;
    }

    void updateNPCPositions() {
        while (true) {
            for (auto& npc : npcSet) {
                if (npc->isAlive()) {
                    int deltaX = 0, deltaY = 0;
                    switch (npc->getType()) {
                        case BearType:
                            deltaX = std::rand() % (2 * MAX_MOVE_BEAR + 1) - MAX_MOVE_BEAR;
                            deltaY = std::rand() % (2 * MAX_MOVE_BEAR + 1) - MAX_MOVE_BEAR;
                            break;
                        case OutlawType:
                            deltaX = std::rand() % (2 * MAX_MOVE_OUTLAW + 1) - MAX_MOVE_OUTLAW;
                            deltaY = std::rand() % (2 * MAX_MOVE_OUTLAW + 1) - MAX_MOVE_OUTLAW;
                            break;
                        case WerewolfType:
                            deltaX = std::rand() % (2 * MAX_MOVE_WEREWOLF + 1) - MAX_MOVE_WEREWOLF;
                            deltaY = std::rand() % (2 * MAX_MOVE_WEREWOLF + 1) - MAX_MOVE_WEREWOLF;
                            break;
                        default:
                            std::cout << "Unknown NPC type!\n";
                            break;
                    }

                    npc->move(deltaX, deltaY, GRID_WIDTH, GRID_HEIGHT);
                }
            }

            for (auto& npc1 : npcSet) {
                for (auto& npc2 : npcSet) {
                    if (npc1 != npc2 && npc1->isAlive() && npc2->isAlive()) {
                        int attackRange = 0;
                        switch (npc1->getType()) {
                            case BearType:
                                attackRange = ATTACK_RANGE_BEAR;
                                break;
                            case OutlawType:
                                attackRange = ATTACK_RANGE_OUTLAW;
                                break;
                            case WerewolfType:
                                attackRange = ATTACK_RANGE_WEREWOLF;
                                break;
                            default:
                                std::cout << "Unknown NPC type!\n";
                                break;
                        }

                        int attackPower = std::rand() % 6 + 1;
                        int defensePower = std::rand() % 6 + 1;

                        if (attackPower > defensePower) {
                            BattleManager::instance().pushEvent({npc1, npc2});
                        }
                    }
                }
            }

            std::this_thread::sleep_for(100ms);
        }
    }

    void displaySurvivors() {
        auto start = std::chrono::steady_clock::now();

        while (true) {
            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(now - start).count() >= 30) {
                std::cout << "Survivors after 30 seconds:\n";
                for (const auto& npc : npcSet) {
                    if (npc->isAlive()) {
                        survivors.insert(npc);
                        npc->display();
                    }
                }
                std::cout << "Simulation finished.\n";
                exit(0);
            }

            renderGrid();
            std::this_thread::sleep_for(1s);
        }
    }

private:
    void renderGrid() {
        std::array<char, NPC_COUNT * NPC_COUNT> grid{};
        const int cellWidth = GRID_WIDTH / NPC_COUNT;
        const int cellHeight = GRID_HEIGHT / NPC_COUNT;

        for (auto& npc : npcSet) {
            auto [x, y] = npc->position();
            int i = x / cellWidth;
            int j = y / cellHeight;

            if (npc->isAlive()) {
                char symbol = '?';
                switch (npc->getType()) {
                    case BearType:
                        symbol = 'B';
                        break;
                    case OutlawType:
                        symbol = 'O';
                        break;
                    case WerewolfType:
                        symbol = 'W';
                        break;
                }
                grid[i + j * NPC_COUNT] = symbol;
            } else {
                grid[i + j * NPC_COUNT] = '.';
            }
        }

        std::lock_guard<std::mutex> lock(output_lock);
        for (int y = 0; y < NPC_COUNT; ++y) {
            for (int x = 0; x < NPC_COUNT; ++x) {
                char symbol = grid[x + y * NPC_COUNT];
                std::cout << (symbol ? "[" + std::string(1, symbol) + "]" : "[ ]");
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
};

int main() {
    GameEngine engine;

    std::thread battleThread(std::ref(BattleManager::instance()));
    std::thread movementThread([&engine]() { engine.updateNPCPositions(); });
    engine.initializeNPCs();
    engine.displaySurvivors();

    movementThread.join();
    battleThread.join();

    return 0;
}
