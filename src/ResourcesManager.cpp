#include "ResourcesManager.hpp"

Engine::ResourcesManager::ResourcesManager() {

}

Engine::ResourcesManager::~ResourcesManager() {

}

void Engine::ResourcesManager::AddTexture(int id, const std::string &filepath)
{
    auto texture = std::make_unique<sf::Texture>();
    if(texture->loadFromFile(filepath))
    {
        textures[id] = std::move(texture);
    }
}
void Engine::ResourcesManager::AddFont(int id, const std::string &filepath)
{
    auto font = std::make_unique<sf::Font>();
    if(font->loadFromFile(filepath))
    {
        fonts[id] = std::move(font);
    }
}
// void Engine::ResourcesManager::AddSound(int id, const std::string &filepath)
// {
//     auto sound = std::make_unique<sf::Sound>();
//     if(sound->)
//     {
//         sounds[id] = std::move(sound);
//     }
// }

const sf::Texture &Engine::ResourcesManager::GetTexture(int id)
{
    return *(textures.at(id).get());
}
const sf::Font &Engine::ResourcesManager::GetFont(int id)
{
    return *(fonts.at(id).get());
}
// const sf::Sound &Engine::ResourcesManager::GetSound(int id)
// {

// }