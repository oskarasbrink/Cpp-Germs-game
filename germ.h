//
// Created by drsve on 2019-05-02.
//

#ifndef GERMS_GERM_H
#define GERMS_GERM_H

#include <SFML/Graphics.hpp>
#include "object.h"
#include "ground.hpp"
#include "projectile.hpp"


class germ: public object
{
public:
    enum direction {LEFT,RIGHT, NONE};
    void land ( ground* ground1);
    germ(sf::Sprite sprite, sf::Vector2f pos,std::string the_name, sf::Font const& font, sf::Color farg );
    virtual void move(const sf::Vector2f& offset);
    virtual void setPosition (const sf::Vector2f& position);
    void update (ground* mark);
    virtual void update() override;
    void explosion_at(sf::Vector2f pos, float radius,int dmg);
    void set_islocked(bool setval);
    bool get_islocked();
    void walk (direction dir,ground* marky);
    void jump(direction dir = NONE);
    float get_climbing_height() const;
    void damage(int dmg);
    int& getHp();
   

    float get_kopf_height()const;
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
    bool islocked_land;
    int hitpoints{100};
    sf::Text name;
    sf::Text hp;
};


#endif //GERMS_GERM_H
