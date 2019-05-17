//
//  Rocket.hpp
//  germs1
//
//  Created by Oskar Åsbrink on 2019-05-08.
//  Copyright © 2019 Oskar Åsbrink. All rights reserved.
//

#ifndef rocket_hpp
#define rocket_hpp

#include <stdio.h>
#include "projectile.hpp"

class rocket : public projectile{
      
public:
    rocket():projectile(){}
    rocket(sf::Sprite rocketsprite,sf::Vector2f velocity,sf::Vector2f pos);
    void explode(ground* mark);
    
    void update();
    int getDamage(){return damage;}
    //projectile operator=(rocket const& rhs)noexcept;
    
    
    
private:
    int damage{20};
    
    
};

#endif /* rocket_hpp */
