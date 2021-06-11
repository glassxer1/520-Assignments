#ifndef _ROBOT_H
#define _ROBOT_H


#include <iostream>
#include "elma/elma.h"
#include "better_state_machine.h"

using namespace elma;

class Mode : public State {
    public:
    Mode(std::string name) : State(name) {}
    void entry(const Event& e) {}
    void during() {}
    void exit(const Event&) {}
};

class Robot : public StateMachine {

    public:

    Robot(std::string name) : StateMachine(name), wander("Wander"), recharge("Recharge"),
                                find_recharge_station("Find Recharge Station"), evade("Evade"),
                                make_noise("Make Noise") {
        set_initial(wander);
        add_transition("intruder detected", wander, make_noise);
        add_transition("battery full", recharge, wander);
        add_transition("found recharge station", find_recharge_station, recharge);
        add_transition("proximity warning", make_noise, evade);
        add_transition("reset", make_noise, wander);
        add_transition("reset", evade, make_noise);
        add_transition("battery low", evade, find_recharge_station);
        add_transition("battery low", wander, find_recharge_station);
    }

    private:

    Mode wander;
    Mode recharge;
    Mode find_recharge_station;   
    Mode evade;
    Mode make_noise;   

};

#endif