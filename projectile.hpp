//
//  projectile.hpp
//  germs1
//
//  Created by Oskar Åsbrink on 2019-05-08.
//  Copyright © 2019 Oskar Åsbrink. All rights reserved.
//

#ifndef projectile_hpp
#define projectile_hpp

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "object.h"
#include "ground.hpp"

class projectile: public object{
    
public:
    projectile(sf::Sprite projectilesprite, sf::Vector2f velocity, sf::Vector2f pos, float blast_rad);
    projectile();
    void update()override;
    bool exploded{false};
    virtual int getDamage() = 0;
    virtual void explode(ground* mark) = 0;
    float get_blast_rad();
protected:
    float blast_rad;
    void draw(sf::RenderTarget& target, sf::RenderStates states)const;

    
    
};

#endif /* projectile_hpp */
