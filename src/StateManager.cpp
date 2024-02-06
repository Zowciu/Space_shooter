#include "StateManager.hpp"

Engine::StateManager::StateManager() : add(false), replace(false), remove(false)
{

}

Engine::StateManager::~StateManager() 
{

}

void Engine::StateManager::AddState(std::unique_ptr<State> stateAdd, bool replace)
{
    add = true;
    newState = std::move(stateAdd);
    replace = replace;

}
void Engine::StateManager::PopCurrentState()
{
    remove = true;

}
void Engine::StateManager::ProcessStateChange()
{
    if(remove && (!stateStack.empty()))
    {
        stateStack.pop();
        if (!stateStack.empty())
        {
            stateStack.top()->Start();
        }
        remove = false;
    }

    if (add)
    {
        if(replace && (!stateStack.empty()))
        {
            stateStack.pop();
            replace = false;
        }
        
        if (!stateStack.empty())
        {
            stateStack.top()->Pause();
        }
        
        stateStack.push(std::move(newState));
        stateStack.top()->Init();
        stateStack.top()->Start();
        add = false;
    }
}
std::unique_ptr<Engine::State>& Engine::StateManager::GetCurrentState()
{
    return stateStack.top();
}