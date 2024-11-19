#include <gtest/gtest.h>
#include "../include/npc.hpp"
#include "../include/visitor.hpp"
#include "../include/factory.hpp"
#include "../include/bear.hpp"
#include "../include/outlaw.hpp"
#include "../include/werewolf.hpp"

TEST(Game, InsertTest) {
    NPCSet characters;

    characters.insert(createNPC(BearType, "bear", 10, 40, "log1.txt"));
    EXPECT_TRUE(characters.size() == 1);
}

TEST(Game, KillTest) {
    Bear bear("b", 10, 20);
    Outlaw outlaw("o", 5, 40);
    Werewolf werewolf("w", 50, 100);

    EXPECT_TRUE(bear.kill(std::make_shared<Werewolf>(werewolf)));
    EXPECT_TRUE(outlaw.kill(std::make_shared<Bear>(bear)));
    EXPECT_TRUE(werewolf.kill(std::make_shared<Outlaw>(outlaw)));

    EXPECT_FALSE(bear.kill(std::make_shared<Outlaw>(outlaw)));
    EXPECT_FALSE(outlaw.kill(std::make_shared<Werewolf>(werewolf)));
    EXPECT_FALSE(werewolf.kill(std::make_shared<Bear>(bear)));

}

TEST(Game, BattleTest) {
    testing::internal::CaptureStdout();
    
    NPCSet characters;

    characters.insert(createNPC(BearType, "Bear1", 0, 50, "test_fight.txt")); 
    characters.insert(createNPC(OutlawType, "Outlaw1", 5, 5, "test_fight.txt")); 
    characters.insert(createNPC(WerewolfType, "Werewolf1", 10, 40, "test_fight.txt"));  

    characters.insert(createNPC(BearType, "Bear2", 60, 90, "test_fight.txt")); 
    characters.insert(createNPC(OutlawType, "Outlaw2", 25, 35, "test_fight.txt"));
    characters.insert(createNPC(WerewolfType, "Werewolf2", 0, 2, "test_fight.txt")); 

    characters.insert(createNPC(BearType, "Bear3", 20, 100, "test_fight.txt")); 
    characters.insert(createNPC(OutlawType, "Outlaw3", 40, 50, "test_fight.txt"));
    characters.insert(createNPC(WerewolfType, "Werewolf3", 80, 90, "test_fight.txt"));

    auto dead_list = simulateBattles(characters, 20);
    for (auto &d : dead_list)
        characters.erase(d);

    testing::internal::GetCapturedStdout();

    EXPECT_EQ(characters.size(), 5);
}

TEST(Observer, ObserverTest) {
    auto bear = std::make_shared<Bear>("Bear", 0, 5);
    auto outlaw = std::make_shared<Outlaw>("Outlaw", 5, 10);
    
    testing::internal::CaptureStdout();

    auto textObserver = std::make_shared<ConsoleObserver>();
    bear->addObserver(textObserver);
    bear->kill(outlaw);

    std::string textOutput = testing::internal::GetCapturedStdout();
    std::string expectedOutput = "[DEFEAT] Battle log:\nbear: Bear at {0, 5} \noutlaw: Outlaw at {5, 10} \nBear lost to Outlaw\n";

    EXPECT_EQ(textOutput, expectedOutput);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
