//

#include "germ.h"
#include "ground.hpp"
#include "definitions.h"
#include <iostream>
float length_of(sf::Vector2f item);

germ::germ(sf::Sprite theSpriteLite, sf::Vector2f pos,std::string the_name,sf::Font const& font,sf::Color farg) : object(std::move(theSpriteLite)),
islocked_land{false},hitpoints{100},name{the_name, font},hp{std::to_string(hitpoints),font}
{   setScale(0.5,0.5);
    name.setOrigin(name.getGlobalBounds().width/2.f,name.getGlobalBounds().height/2.f);

    hp.setOrigin((hp.getGlobalBounds().width/2.f + name.getGlobalBounds().width + 20.f),hp.getGlobalBounds().height/2.f);
    name.setFillColor(farg);
    hp.setFillColor(farg);

    
    germ::setPosition(pos);
}

void germ::move(const sf::Vector2f &offset)
{
    Transformable::move(offset);
    name.move(offset);
    hp.move(offset);
}

void germ::setPosition(const sf::Vector2f& position)
{
    Transformable::setPosition(position);
    name.setPosition((getPosition() - sf::Vector2f(0.f ,getradius() ) *2.f));
    hp.setPosition((getPosition() - sf::Vector2f(0.f,getradius())*2.f));
}

void germ::update(ground* mark){
   
    hp.setString(std::to_string(hitpoints));
    if(!islocked_land)
    {
        auto old_pos = getPosition();

        move(velocity);

        if (mark->is_collision(*this))
        {
            if(length_of(velocity) > 19.f || !mark->butt_blocked(*this))
            {
                velocity = (velocity * -0.6f);
            }
            else if(mark->butt_blocked(*this) )
             {
                   land(mark);
             }
        }
        if(mark->side_blocked(*this) || mark->kopf_blocked(*this))
        {
            setPosition(old_pos);
        }

    }

}
void germ::update(){
    move(velocity);
}

void germ::land(ground* ground1)
{
    ground1->climb_germ(*this);
    velocity = sf::Vector2f{0,0};
    islocked_land = true;
}

void germ::explosion_at(sf::Vector2f pos, float radius, int dmg)
{
    
    if(length_of(getPosition() - pos) <=  getradius() + radius  )
    {
        add_velocity( (getPosition() - pos) * (25.f/length_of(pos - getPosition())) );
        islocked_land = false;
        hitpoints -= dmg;
    }
}

void germ::set_islocked(bool setval)
{
    islocked_land = setval;
}

bool germ::get_islocked()
{
    return islocked_land;
}

void germ::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
#ifdef DEBUG
    sf::CircleShape circle ;

    circle.setRadius(getradius());
    circle.setPosition(getPosition());
    circle.setOrigin(getradius(),getradius());

    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(sf::Color::Yellow);
    circle.setOutlineThickness(1.f);
    sf::VertexArray vert;
    vert.resize(1);
    vert[0].position = getPosition();
    vert[0].color= sf::Color::Red;
    vert.setPrimitiveType(sf::Points);

    target.draw(circle,states);
    target.draw(vert,states);
#else
    target.draw( sf::Sprite(*this),states);
    target.draw(name,states);
    target.draw(hp,states);
#endif
}

void germ::jump(direction dir)
{
    if(islocked_land)
    {
        switch (dir)
        {
            case RIGHT:
                add_velocity(sf::Vector2f{germ_walkspeed, 0.f});

                break;


            case LEFT:
                add_velocity(sf::Vector2f{-germ_walkspeed, 0.f});
                break;

            case NONE:
                break;

            default:
                break;
        }
        add_velocity(sf::Vector2f{0.f, -20.f});
        islocked_land = false;
    }

}
void germ::walk(direction dir, ground* marky)
{
    sf::Vector2f old_pos = getPosition();
    if(islocked_land) {
        switch (dir) {
            case LEFT: {
                move(sf::Vector2f{-germ_walkspeed, 0});
            }
                break;

            case RIGHT: {
                move(sf::Vector2f{germ_walkspeed, 0});
            }
                break;

            default:
                break;
        }

        /*
        islocked_land = marky->is_collision(*this);
        if (islocked_land)
        {
            marky->climb_germ(*this);
        }
        */
        if(marky->butt_blocked(*this))
        {
            land(marky);
        }

    if (marky->side_blocked(*this) || marky->kopf_blocked(*this))
    {
        setPosition(old_pos);
    }
    else{islocked_land = false;}

    }

}

float germ::get_climbing_height() const
{
    return getPosition().y;
    //return getPosition().y - getradius()/8.f;
}

float germ::get_kopf_height() const
{
    return getPosition().y - getradius()*(3.f/4.f);
}

void germ::damage(int dmg){
    hitpoints -= dmg;
    
}

int& germ::getHp(){
    return hitpoints;
}
