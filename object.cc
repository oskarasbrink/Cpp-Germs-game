#include <utility>

//
// Created by drsve on 2019-05-02.
//

#include "object.h"
#include "math.h"

float length_of(sf::Vector2f item);

object::object(sf::Sprite sprite ,sf::Vector2f startvel) : Sprite{std::move(sprite)},velocity{startvel}
{
    setScale(1,1);
    setRotation(0.f);
    setOrigin(getradius(),getradius());
}

float object::getradius() const
{
    return (getGlobalBounds().height / 2.f );
}

bool object::is_collision(object const& obj) const
{
    return length_of(getPosition() - obj.getPosition()) <= getradius()+ obj.getradius();
}

void object::set_velocity(sf::Vector2f new_vec)
{
    velocity = new_vec;
}

void object::add_velocity(sf::Vector2f new_vec)
{
    velocity += new_vec;
}

sf::Vector2f const & object::get_velocity()const
{
    return velocity;
}


