//
//  rocketlauncher.cpp
//  germs1
//
//  Created by Oskar Åsbrink on 2019-05-09.
//  Copyright © 2019 Oskar Åsbrink. All rights reserved.
//

#include "rocketlauncher.hpp"
#include <math.h>
#include <iostream>

rocketlauncher::rocketlauncher(sf::Sprite sprite,sf::Vector2f pos, sf::Texture* projtex):weapon(sprite,pos,projtex)
{setOrigin(getGlobalBounds().width/8,getGlobalBounds().height/2);}

rocket* rocketlauncher::fire(sf::Vector2f mousepos)
{
    sf::Vector2f rotated;
    sf::Vector2f barrel(getGlobalBounds().width,
                        getGlobalBounds().height);

    rotated.x = (barrel.x * cos(getRotation() *  M_PI/180));
    rotated.y = (barrel.y * sin(getRotation() * M_PI/180) + barrel.y*sin(getRotation()* M_PI/180));
    barrel = getPosition() + rotated;
    std::cout<<"rotatedx  "<<rotated.x<<"  rotatedy  "<<rotated.y;
    sf::Vector2f vel{(cos(getRotation() * static_cast<float>(M_PI)) / 180),
                     (sin(getRotation() * static_cast<float>(M_PI)) / 180)};
 //  sf::Vector2f hej2 = 0.04f*(mousepos - getPosition());
    sf::Vector2f hej2{0.02f*(mousepos.x - getPosition().x), static_cast<float>(0.03*(mousepos.y - getPosition().y))};
    
    
    
    return new rocket{sf::Sprite{proj_tex}, hej2 ,barrel};

}

