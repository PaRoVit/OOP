#include <gtest/gtest.h>

#include "../include/npc.hpp"
#include "../include/observer.hpp"
#include "../include/bear.hpp"
#include "../include/outlaw.hpp"
#include "../include/werewolf.hpp"


TEST(FightTest1, BearVsOutlaw) {
    testing::internal::CaptureStdout();

    auto bear = createNPC(BearType, "Bear", 0, 0, "test_fight.txt");
    auto outlaw = createNPC(OutlawType, "Outlaw", 1, 1, "test_fight.txt"); //! will be killed
    EXPECT_FALSE(outlaw->acceptVisitor(bear));
    outlaw->mustDie();

    EXPECT_TRUE(bear->isAlive());
    EXPECT_FALSE(outlaw->isAlive());

    testing::internal::GetCapturedStdout();
}

TEST(FightTest2, BearVsWerewolf) {
    testing::internal::CaptureStdout();

    auto bear = createNPC(BearType, "Bear", 0, 0, "test_fight.txt");
    auto werewolf = createNPC(WerewolfType, "Werewolf", 1, 1, "test_fight.txt"); //! will be killed
    ASSERT_TRUE(werewolf->acceptVisitor(bear));
    werewolf->mustDie();

    ASSERT_TRUE(bear->isAlive());
    ASSERT_FALSE(werewolf->isAlive());

    testing::internal::GetCapturedStdout();
}

TEST(FightTest3, MainFighting) {
    
    set_t NPCs;
    NPCs.insert(createNPC(BearType, "Bear1", 15, 15, "test_fight.txt")); 
    NPCs.insert(createNPC(BearType, "Bear2", 10, 10, "test_fight.txt"));
    NPCs.insert(createNPC(BearType, "Bear3", 15, 15, "test_fight.txt"));
    NPCs.insert(createNPC(BearType, "Bear4", 10, 10, "test_fight.txt"));
    NPCs.insert(createNPC(OutlawType, "Outlaw1", 10, 10, "test_fight.txt")); 
    NPCs.insert(createNPC(OutlawType, "Outlaw2", 30, 30, "test_fight.txt")); 
    NPCs.insert(createNPC(WerewolfType, "Werewolf1", 10, 10, "test_fight.txt")); 
    NPCs.insert(createNPC(WerewolfType, "Werewolf2", 15, 15, "test_fight.txt")); 
    set_t killed;
    
    EXPECT_EQ(8, NPCs.size());
    testing::internal::CaptureStdout();
    for (auto& attacker : NPCs) {
        for (auto& defender : NPCs) {
            if (attacker->isAlive())
                if (defender->isAlive())
                    if (defender->acceptVisitor(attacker)) {
                        defender->mustDie();
                        killed.insert(defender);
                    }
        }
    }
    testing::internal::GetCapturedStdout();
    
    EXPECT_EQ(6, killed.size());
    for (const auto& npc : killed) {
        NPCs.erase(npc);
    }
    EXPECT_EQ(2, NPCs.size());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}