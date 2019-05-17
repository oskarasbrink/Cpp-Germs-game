//
//  weapon.cpp
//  germs1
//
//  Created by Oskar Åsbrink on 2019-05-08.
//  Copyright © 2019 Oskar Åsbrink. All rights reserved.
//

#include "weapon.hpp"
#include "math.h"

weapon::weapon(sf::Sprite weaponsprite, sf::Vector2f pos, sf::Texture* proj_tex):Sprite{weaponsprite},proj_tex{*proj_tex}{
    setPosition(pos);
}

void weapon::update(sf::Vector2f pos,sf::RenderWindow const& window)
{
    setPosition(pos.x, pos.y);

    auto mouse = sf::Mouse::getPosition(window);
    sf::Vector2f hej = sf::Vector2f{static_cast<float>(mouse.x), static_cast<float>(mouse.y)} - getPosition();
    float rotate = 180 * atan(hej.y / hej.x) / M_PI;
    setRotation(rotate);
    if(hej.x < 0){setRotation(getRotation() + 180);
        
    }
}
