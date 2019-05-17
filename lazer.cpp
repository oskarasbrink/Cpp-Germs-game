//
//  lazer.cpp
//  germs1
//
//  Created by Oskar Åsbrink on 2019-05-14.
//  Copyright © 2019 Oskar Åsbrink. All rights reserved.
//

#include "lazer.hpp"




lazer::lazer(sf::Sprite lazersprite, sf::Vector2f velocity, sf::Vector2f pos):projectile(lazersprite,velocity,pos,0.1f){
    setScale(0.2f,0.2f);
    setRotation(atan(velocity.y/velocity.x)*180.f/M_PI);
}

void lazer::explode(ground* mark){
    mark->explosion_at(getPosition(), blast_rad);
    exploded = true;
}

void lazer::add_velocity(sf::Vector2f new_vec){
    //denna ska vara tom
}
