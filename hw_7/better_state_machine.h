#ifndef _BETTER_STATE_MACHINE_H
#define _BETTER_STATE_MACHINE_H


#include <iostream>
#include <set>
#include <vector>
#include "elma/elma.h"
#include <json/json.h>

using namespace elma;
using nlohmann::json;

class BetterStateMachine : public StateMachine {
    public:
    BetterStateMachine(std::string name) : StateMachine(name), _name(name){}  
    json to_json() const {
        json j;
        j["name"] = _name;
        std::set<std::string> stateSet;
        for (auto trans : _transitions) {
            std::string f = trans.from().name();
            std::string t = trans.to().name();
            std::string e = trans.event_name();
            stateSet.insert(f);
            stateSet.insert(t);
            j["transitions"].push_back({ {"from", f}, {"to", t}, {"when", e} });
        }

        j["states"] = stateSet;

        return j;
    }

    private:
    std::string _name;
};

#endif