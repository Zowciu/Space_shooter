#pragma once

#include <map>
#include <memory>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/Sound.hpp>

namespace Engine
{
    class ResourcesManager {
    private:
        std::map<int, std::unique_ptr<sf::Texture>> textures;
        std::map<int, std::unique_ptr<sf::Font>> fonts;
        std::map<int, std::unique_ptr<sf::Sound>> sounds;
    public:
        ResourcesManager();
        ~ResourcesManager();

        void AddTexture(int id, const std::string &filepath);
        void AddFont(int id, const std::string &filepath);
        //void AddSound(int id, const std::string &filepath);

        const sf::Texture &GetTexture(int id);
        const sf::Font & GetFont(int id);
        //const sf::Sound & GetSound(int id);
    };
} // namespace Engine

