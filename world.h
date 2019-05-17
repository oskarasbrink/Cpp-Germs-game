//
// Created by drsve on 2019-05-13.
//

#ifndef GERMS_WORLD_H
#define GERMS_WORLD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include "germ.h"
#include "ground.hpp"
#include "weapon.hpp"
#include <list>
class world;
class player
{
public:
    friend class world;

    player(sf::Color colr);
    void add_germ(sf::Sprite sprite, sf::Vector2f pos,std::string the_name, sf::Font const& font);
    void update();
    germ& current();
    void handle_event(sf::Event& event);
    void next_turn();

private:

    sf::Color team_colr;
    std::list<germ> team;
    world* world1;
};

class world: public sf::Drawable
{
public:

    explicit world(ground* mark);
    void add_player(player & newP);
    void add_weapon(weapon* wep);
    void add_projectile(projectile* proj);
    void update(sf::RenderWindow const& window);
    void explosion_at(sf::Vector2f pos, float radius, int dmg);
    void swap_weapon();
    weapon& current_weapon()const;
    
    germ& curr();
    void rotate();
    bool is_projectile();
private:
    std::list<player*> players;
    std::vector<weapon*> weapons;


    std::vector<projectile*> projectiles;

    //std::vector<germ*> germs;
    ground* grounden;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
};


#endif //GERMS_WORLD_H
