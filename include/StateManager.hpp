#pragma once

#include <stack>
#include <memory>
#include <State.hpp>

namespace Engine
{
    class StateManager 
    {
    private:
        std::stack<std::unique_ptr<State>> stateStack;
        std::unique_ptr<State> newState;

        bool add;
        bool replace;
        bool remove;
        
    public:
        StateManager();
        ~StateManager();

        void AddState(std::unique_ptr<State> stateAdd, bool replace = false);
        void PopCurrentState();
        void ProcessStateChange();
        std::unique_ptr<State> &GetCurrentState();
    };

} // namespace Engine

