//
// Created by drsve on 2019-05-13.
//

#include "world.h"
#include "definitions.h"
#include <iostream>

player::player( sf::Color colr): world1{nullptr},team_colr{colr}
{}

void player::update()
{
    auto it = std::remove_if(team.begin(),team.end(),[](germ& tagga_pallen_haha_snagga_ballen_kanske)
                             {
                                 return(tagga_pallen_haha_snagga_ballen_kanske.getHp()<=0.f);
                             });
    team.erase(it,team.end());
}

void player::add_germ(sf::Sprite sprite, sf::Vector2f pos,std::string the_name, sf::Font const& font)
{
    team.emplace_back(germ{std::move(sprite),pos,std::move(the_name),font,team_colr});
};

germ& player::current()
{
    return team.front();
}

void player::next_turn()
{
    std::rotate(team.begin(),++team.begin(),team.end());
}

void player::handle_event(sf::Event &event)
{}


world::world(ground * mark) :grounden{mark}
{
    
}

void world::add_player(player & newP)
{
    players.emplace_back(&newP);
}

void world::add_weapon(weapon* wep)
{
    weapons.push_back(wep);
}

void world::swap_weapon(){
    std::rotate(weapons.begin(),++weapons.begin(),weapons.end());
}

weapon& world::current_weapon()const{
    return *(weapons.front());
}


void world::update(sf::RenderWindow const& window)
{
    
    ////<uppdaterar germs pos>///
    std::for_each(players.begin(),players.end(),[this](player* gamer_boy)
                  {
                      std::for_each(gamer_boy->team.begin(),gamer_boy->team.end(),[this](germ& germ1)
                                    {
                                        if (!germ1.get_islocked())
                                        {
                                            germ1.add_velocity(sf::Vector2f{0,gravity});
                                        }
                                        germ1.update(grounden);
                                    });
                  });
    ////</uppdaterar germs pos>///
    
    if(is_projectile())
    {
        //////<uppdaterar projektil && sköter kollision med projektil>///
        projectiles.at(0)->add_velocity(sf::Vector2f{0,0.3f});
        projectiles.at(0)->update();
        
        if(is_projectile() &&
           (grounden->is_collision(*projectiles.at(0)) ||
            std::any_of(players.begin(),players.end(),[this](player* gamer_boy)
                        {
                            return std::any_of(gamer_boy->team.begin(),gamer_boy->team.end(),[this](germ& germ1)
                                               {
                                                   return projectiles.at(0)->is_collision(germ1);
                                               });
                        })))
        {
            explosion_at(projectiles.at(0)->getPosition(),projectiles.at(0)->get_blast_rad(),projectiles.at(0)->getDamage());
            projectiles.at(0)->exploded=true;
        }
    
    //////</uppdaterar projektil && sköter kollision med projektil>///
    
        //<rensar döda projektiler>//
        if(projectiles.at(0)->exploded)
        {
            projectiles.clear();
        }
        //</rensar döda projektiler>//
    }
    //uppdaterar vapen pos och vapen rotation
    current_weapon().update(curr().getPosition(), window);
    
    //dödar alla döda germs:
   std::for_each(players.begin(),players.end(),[](player* er)
    {
        er->update();
    });
}

germ& world::curr()
{
    return (players.front()->current());
}

void world::explosion_at(sf::Vector2f pos, float radius,int dmg)
{
    grounden->explosion_at(pos,radius);
    
    std::for_each(players.begin(),players.end(),[&pos,&radius,&dmg](player* gamer_boy)
                  {
                      std::for_each(gamer_boy->team.begin(),gamer_boy->team.end(),[&pos,&radius,&dmg](germ& germ1)
                                    {
                                        germ1.explosion_at(pos,radius,dmg);
                                        
                                    });
                  });
}

void world::add_projectile(projectile* proj){
    projectiles.push_back(proj);
}

void world::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    std::for_each(players.begin(),players.end(),[&target,&states](player* gamer_boy)
                  {
                      std::for_each(gamer_boy->team.begin(),gamer_boy->team.end(),[&target,&states](germ& germ1)
                                    {
                                        target.draw(germ1,states);
                                    });
                  });
    
    std::for_each(projectiles.begin(),projectiles.end(),[&target,&states](projectile* proj)
                  {
                      target.draw( *proj,states);
                  });
    
    target.draw(*grounden,states);
    target.draw(current_weapon());
}

void world::rotate()
{
    players.front()->next_turn();
    std::rotate(players.begin(),++players.begin(),players.end());
}


bool world::is_projectile(){
    return !projectiles.empty();
}
