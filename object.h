//
// Created by drsve on 2019-05-02.
//

#ifndef UNTITLED_CIRCLE_HITBOX_H
#define UNTITLED_CIRCLE_HITBOX_H

#include <SFML/Graphics.hpp>

#include "definitions.h"

class ground;

class object: public sf::Sprite
{
public:
    explicit object (sf::Sprite sprite,sf::Vector2f startvel = sf::Vector2f{0.f,0.f});
    float getradius() const;

    bool is_collision(object const& obj)const;



    void set_velocity(sf::Vector2f new_vec);
   virtual void add_velocity (sf::Vector2f new_vec);
    sf::Vector2f const & get_velocity() const;

    virtual void update()=0;

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const = 0;
    sf::Vector2f velocity;
};

#endif //UNTITLED_CIRCLE_HITBOX_H
