//
//  weapon.hpp
//  germs1
//
//  Created by Oskar Åsbrink on 2019-05-08.
//  Copyright © 2019 Oskar Åsbrink. All rights reserved.
//

#ifndef weapon_hpp
#define weapon_hpp

#include <stdio.h>
#include "object.h"
#include <SFML/Graphics.hpp>
#include "projectile.hpp"


class weapon: public sf::Sprite{
public:
    weapon(sf::Sprite weaponsprite, sf::Vector2f pos,sf::Texture* proj_tex);
    virtual projectile* fire(sf::Vector2f mousepos) = 0;
    void update(sf::Vector2f pos,sf::RenderWindow const& window);

protected:
    sf::Texture proj_tex;
    
};

#endif /* weapon_hpp */
