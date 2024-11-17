#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <array>

#include <iostream>

namespace sf::KeyboardUtils
{
    bool isKeyHasPressed(sf::Keyboard::Key key)
    {
        static std::array<bool, sf::Keyboard::Key::KeyCount> KeysHasPressedMap;

        bool keyPressed = sf::Keyboard::isKeyPressed(key);

        if(keyPressed && !KeysHasPressedMap[key])
        {
            KeysHasPressedMap[key] = true;
            return true;
        }
        else if(!keyPressed)
        {
            KeysHasPressedMap[key] = false;
        }

        return false;
    }
}
