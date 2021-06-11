#include "gtest/gtest.h"
#include "elma/elma.h"
#include "robot.h"
#include "better_state_machine.h"


using namespace std::chrono;
using namespace elma;


namespace {
   
    TEST(Robot, Safety) {

        Robot robot("What a very nice robot.");

        Manager m;
        m.schedule(robot, 10_ms)
         .init()
         .start();

        EXPECT_EQ(robot.current().name(), "Wander");
        m.emit(Event("intruder detected"));
        EXPECT_EQ(robot.current().name(), "Make Noise");
        m.emit(Event("proximity warning"));
        EXPECT_EQ(robot.current().name(), "Evade");
        m.emit(Event("battery full"));
        EXPECT_EQ(robot.current().name(), "Evade"); 
        m.emit(Event("battery low"));
        EXPECT_EQ(robot.current().name(), "Find Recharge Station");

    }

    TEST(BetterStateMachine, Robot_Test) {
        Robot robot("robot");

        json j = robot.to_json();
        ASSERT_EQ(j["name"], "robot");
        ASSERT_EQ(j["states"].size(), 5);
    }

}

