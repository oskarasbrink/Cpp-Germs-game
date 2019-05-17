//
//  lazergun.cpp
//  germs1
//
//  Created by Oskar Åsbrink on 2019-05-14.
//  Copyright © 2019 Oskar Åsbrink. All rights reserved.
//

#include "lazergun.hpp"
#include "math.h"

lazergun::lazergun(sf::Sprite sprite, sf::Vector2f pos, sf::Texture* projtex):weapon(sprite,pos,projtex){setOrigin(getGlobalBounds().width/8,getGlobalBounds().height/2);}


lazer* lazergun::fire(sf::Vector2f mousepos)
{
    sf::Vector2f rotated;
    sf::Vector2f barrel(getGlobalBounds().width,
                        getGlobalBounds().height);
    rotated.x = (barrel.x * cos(getRotation() * M_PI / 180));
    rotated.y = (barrel.y * sin(getRotation() * M_PI / 180));
    barrel = getPosition() + rotated;
    sf::Vector2f hej2{(15*cos(getRotation() * static_cast<float>(M_PI) / 180)),(15*sin(getRotation() * static_cast<float>(M_PI) / 180))};

  //  sf::Vector2f hej2 {0.03f*(mousepos.x - getPosition().x),0.03f*(mousepos.y-getPosition().y)};
    
    
    
    return new lazer{sf::Sprite{proj_tex}, hej2 ,barrel};
}

