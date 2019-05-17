//
//  lazergun.hpp
//  germs1
//
//  Created by Oskar Åsbrink on 2019-05-14.
//  Copyright © 2019 Oskar Åsbrink. All rights reserved.
//

#ifndef lazergun_hpp
#define lazergun_hpp

#include <stdio.h>
#include "weapon.hpp"
#include "lazer.hpp"


class lazergun: public weapon{
    
public:
    lazergun(sf::Sprite sprite, sf::Vector2f pos, sf::Texture* projtex);
    lazer* fire(sf::Vector2f mousepos);
    
private:
    
};


#endif /* lazergun_hpp */
