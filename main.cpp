#include "game_engine.hpp"

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
