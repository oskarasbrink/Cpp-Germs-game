//
//  lazer.hpp
//  germs1
//
//  Created by Oskar Åsbrink on 2019-05-14.
//  Copyright © 2019 Oskar Åsbrink. All rights reserved.
//

#ifndef lazer_hpp
#define lazer_hpp

#include <stdio.h>
#include "projectile.hpp"

class lazer: public projectile{
    
public:
    lazer():projectile(){}
    lazer(sf::Sprite lazersprite, sf::Vector2f velocity, sf::Vector2f pos);
    void explode(ground* mark);
    void add_velocity(sf::Vector2f new_vec);
    int getDamage(){return damage;}
private:
    int damage{30};
    
    
};


#endif /* lazer_hpp */
