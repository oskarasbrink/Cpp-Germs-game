//
// Created by Jakob on 2019-04-29.
//

#ifndef UNTITLED_GROUND_HPP
#define UNTITLED_GROUND_HPP

#include <SFML/Graphics.hpp>

#include "definitions.h"
class germ;
class object;

class ground : public sf::Drawable
{
public:
    ground(int width,int height,uint8_t pxl_size, sf::Texture &the_texture);
    void climb_germ(germ & germ1)const;
    void explosion_at(sf::Vector2f pos,float radius);
    bool is_collision(object const& circleHitbox1) const;

    bool kopf_blocked (germ const& germ1) const;
    bool butt_blocked (germ const& germ1) const;
    bool side_blocked (germ const& germ1) const;
    bool right_blocked(germ const& germ1) const;
    bool left_blocked(germ const& germ1) const;


private:
    struct map_chunk;
    struct map_block;
    void set_chunks(int w, int h);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
    sf::Texture texture;
    std::vector<map_chunk> chunks;
    std::vector<map_block*> blocks;
};

struct ground::map_block:public sf::Drawable
{

    friend class ground;
    map_block(unsigned height, unsigned width,sf::Vector2f pos1 ,sf::Vector2f pos2);
    void explosion_at(sf::Vector2f pos,float radius);
    bool affected(sf::Vector2f pos, float radius)const;
    bool rekt(sf::Vector2f pos, float radius)const;

#ifdef DEBUG
    void setprimitive (sf::PrimitiveType prim,sf::Color color);

#endif

    sf::Vector2f top_left;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
    sf::VertexArray block;

};

struct ground::map_chunk
{
    explicit map_chunk(sf::Vector2f pos):rect{pos,chunk_size}{}

    bool contains (object const& object1)const;
    bool is_collision( object const& object1)const;
    std::vector<map_block*> grounds;
    sf::FloatRect rect;
};

#endif //UNTITLED_GROUND_HPP
