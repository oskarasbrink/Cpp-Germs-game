//
//  rocket.cpp
//  germs1
//
//  Created by Oskar Åsbrink on 2019-05-08.
//  Copyright © 2019 Oskar Åsbrink. All rights reserved.
//

#include "rocket.hpp"


rocket::rocket(sf::Sprite rocketsprite,sf::Vector2f velocity,sf::Vector2f pos):projectile(rocketsprite,velocity,pos,150.f){setScale(0.1f,0.1f); setOrigin(getGlobalBounds().width/2,getGlobalBounds().height/2);}



void rocket::explode(ground* mark){
    mark->explosion_at(getPosition(), blast_rad);
    exploded = true;
    
}



