//
//  rocketlauncher.hpp
//  germs1
//
//  Created by Oskar Åsbrink on 2019-05-09.
//  Copyright © 2019 Oskar Åsbrink. All rights reserved.
//

#ifndef rocketlauncher_hpp
#define rocketlauncher_hpp

#include <stdio.h>
#include "weapon.hpp"
#include "rocket.hpp"

class rocketlauncher: public weapon{
public:
    rocketlauncher(sf::Sprite sprite,sf::Vector2f pos, sf::Texture* projtex);
    rocket* fire(sf::Vector2f mousepos);
private:

};



#endif /* rocketlauncher_hpp */
