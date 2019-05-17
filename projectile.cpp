//
//  projectile.cpp
//  germs1
//
//  Created by Oskar Åsbrink on 2019-05-08.
//  Copyright © 2019 Oskar Åsbrink. All rights reserved.
//




/*
class projectile: public object{
    
public:
    projectile(sf::Sprite projectilesprite, sf::Vector2f velocity, sf::Vector2f pos);
    virtual void update(ground*mark)=0;
    void draw(sf::RenderTarget& target, sf::RenderStates states);
    
    
    
protected:
    int damage;*/
#include "projectile.hpp"

projectile::projectile(sf::Sprite projectilesprite,sf::Vector2f velocity, sf::Vector2f pos, float blast_rad) : object(projectilesprite,velocity),blast_rad{blast_rad}{
    
    setPosition(pos);

}

void projectile::draw(sf::RenderTarget& target, sf::RenderStates states)const {
    target.draw(sf::Sprite(*this), states);
}

float projectile::get_blast_rad(){
    return blast_rad;
}
void projectile::update(){
    
    
    if(!exploded)
        
    {move(velocity.x,velocity.y);}
}










