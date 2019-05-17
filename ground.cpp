//
// Created by Jakob on 2019-04-29.
//

#include "ground.hpp"
#include <random>
#include <math.h>
#include <random>
#include "germ.h"
#include "definitions.h"

float length_of(sf::Vector2f item)
{
    return sqrt(item.x * item.x + item.y * item.y);
}

ground::map_block::map_block(unsigned height, unsigned width, sf::Vector2f pos1 ,sf::Vector2f pos2)
{
    block.resize(4);
    block.setPrimitiveType(sf::Quads);
    block[0].position = pos1+sf::Vector2f(0,height);
    block[1].position = pos1;
    block[2].position = pos2;
    block[3].position = pos1+sf::Vector2f(width,height);

    block[0].texCoords=pos1+sf::Vector2f(0,height);
    block[1].texCoords = pos1;
    block[2].texCoords = pos2;
    block[3].texCoords = pos1+sf::Vector2f(width,height);
}

bool ground::map_block::affected(sf::Vector2f pos, float radius)const
{
    return block.getVertexCount() && ( (length_of(block[0].position - pos) <= radius || length_of(block [1].position-pos)<= radius || length_of(block[2].position-pos)<= radius || length_of(block[3].position-pos)<= radius) );
}

bool ground::map_block::rekt(sf::Vector2f pos, float radius)const
{
    return length_of(block[0].position - pos) < radius && length_of(block [1].position-pos) < radius && length_of(block[2].position-pos) < radius && length_of(block[3].position-pos) < radius;
}

void ground::map_block::explosion_at(sf::Vector2f pos,float radius)
{

    if(rekt(pos,radius))
    {
        block.clear();
        block.resize(0);
    }
    else
    {
        for(int i = 0;i < 4;++i)
        {
            if (length_of(pos-block[i].position) < radius)
            {
                block[i].position += (block[i].position-pos)*(radius-length_of(block[i].position-pos))/length_of(block[i].texCoords-pos);
                block[i].texCoords+= (block[i].texCoords-pos) *(radius-length_of(block[i].texCoords-pos))/length_of(block[i].texCoords-pos);
            }
        }
    }

}
#ifdef DEBUG
void map_block::setprimitive(sf::PrimitiveType prim,sf::Color color)
{
    block.setPrimitiveType(prim);
    block[0].color =color;
    block[1].color =color;
    block[2].color =color;
    block[3].color =color;
}
#endif

void ground::map_block::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(block,states);
}

ground::ground(int width, int height,uint8_t pxl_size, sf::Texture &the_texture):texture{the_texture}
{

    texture.setRepeated(true);
    srand(time(NULL));
    std::mt19937 mt(rand() % 10000000000000);
    std::uniform_real_distribution<float> dist(350, 450.f);
    std::uniform_real_distribution<float> dist2(5.f, 10.f);
    float randcurr = dist(mt);
    int trap = 0;
    float q = dist2(mt);
    for (unsigned i = 0; i < width; i += pxl_size) {
        for (float j = 0.f; j <= randcurr; j += static_cast<float>(pxl_size)) {
            if (j >= (randcurr - static_cast<float>(pxl_size))) {
                if (++trap > 5) {
                    q = dist2(mt);

                    if(dist2(mt)>7.5f || randcurr < q * 5){q = -q;}
                    trap = 0;
                }
                blocks.push_back(new map_block{pxl_size, pxl_size, sf::Vector2f{static_cast<float>(i), height - randcurr},
                                               sf::Vector2f{static_cast<float>(i) + pxl_size, height - randcurr + q}});

                randcurr -= q;
                blocks.push_back(new map_block{pxl_size, pxl_size, sf::Vector2f{static_cast<float>(i), height - j},
                                               sf::Vector2f{static_cast<float>(i) + pxl_size, height - j}});

            } else {
                blocks.push_back(new map_block{pxl_size, pxl_size, sf::Vector2f{static_cast<float>(i), height - j},
                                               sf::Vector2f{static_cast<float>(i) + pxl_size, height - j}});
            }
        }
    }
    set_chunks(width,height);
#ifdef DEBUG
    std::for_each(blocks.begin(),blocks.end(),[](map_block*  block)

    {
        block->setprimitive(sf::Points,sf::Color::Red);
    });
#endif
}

bool ground::is_collision(object const& circle_hitbox1) const
{
    return std::any_of(chunks.begin(),chunks.end(),[&circle_hitbox1](map_chunk item)
    {
       return item.contains(circle_hitbox1) && item.is_collision(circle_hitbox1);
    });
}

void ground::explosion_at(sf::Vector2f pos, float radius)
{
    std::for_each(blocks.begin(),blocks.end(),[&pos,&radius](map_block* item)
    {
        if(item->affected(pos,radius))
        {
            item->explosion_at(pos,radius);
        }
    });
}

bool ground::right_blocked(germ const& germ1)const
{

    return std::any_of(chunks.begin(),chunks.end(),[&germ1](map_chunk const& house_musik_XD){
        return house_musik_XD.contains(germ1) && any_of(house_musik_XD.grounds.begin(),house_musik_XD.grounds.end(),[&germ1](map_block* item)
        {
            bool ret_val = false;
            for(uint8_t i = 0;i<4;i++)
            {
                if(item->affected(germ1.getPosition(), germ1.getradius())
                   && length_of(item->block[i].position - germ1.getPosition()) <= germ1.getradius() &&
                   ( item->block[i].position.y < germ1.get_climbing_height() && item->block[i].position.y>germ1.get_kopf_height() )
                   && item->block[i].position.x > germ1.getPosition().x)
                {ret_val = true;}
            }
            return  ret_val;
        });
    });


}

bool ground::left_blocked(germ const& germ1) const
{
    return std::any_of(chunks.begin(),chunks.end(),[&germ1](map_chunk const& house_musik_XD){
        return house_musik_XD.contains(germ1) && any_of(house_musik_XD.grounds.begin(),house_musik_XD.grounds.end(),[&germ1](map_block* item)
        {
            bool ret_val = false;

            for(uint8_t i = 0;i<4;i++)
            {
                if(item->affected(germ1.getPosition(), germ1.getradius())
                   && length_of(item->block[i].position - germ1.getPosition()) <= germ1.getradius() &&
                   (item->block[i].position.y < germ1.get_climbing_height() && item->block[i].position.y>germ1.get_kopf_height())
                   && item->block[i].position.x < germ1.getPosition().x )
                {ret_val = true;}
            }
            return  ret_val;
        });
    });

}

bool ground::side_blocked (germ const& germ1)const
{
    return right_blocked(germ1)||left_blocked(germ1);
}

bool ground::kopf_blocked(germ const& germ1) const
{
    return std::any_of(chunks.begin(),chunks.end(),[&germ1](map_chunk const& chnk)
    {
        return chnk.contains( germ1) && std::any_of(chnk.grounds.begin(),chnk.grounds.end(),[&germ1](map_block* item)
        {
            bool ret_val = false;
                for(uint8_t i = 0;i<4;i++)
                {
                 if(item->affected(germ1.getPosition(), germ1.getradius())
                    && length_of(item->block[i].position - germ1.getPosition()) <= germ1.getradius() &&
                    item->block[i].position.y < germ1.get_kopf_height() )
                 {ret_val = true;}
                }
            return  ret_val;
        });

    });
}

bool ground::butt_blocked(germ const &germ1) const
{
    return std::any_of(chunks.begin(),chunks.end(),[&germ1](map_chunk const& chnk) {
        return chnk.contains(germ1) && std::any_of(chnk.grounds.begin(), chnk.grounds.end(), [&germ1](map_block *item) {
            bool ret_val = false;

            for (uint8_t i = 0; i < 4; i++) {
                if (item->affected(germ1.getPosition(), germ1.getradius())
                    && length_of(item->block[i].position - germ1.getPosition()) <= germ1.getradius()
                    && item->block[i].position.y > germ1.get_climbing_height()) { ret_val = true; }
            }
            return ret_val;
        });
    });
}

void ground::climb_germ(germ & germ1) const
{
    float highest_move= 0;

    std::for_each(chunks.begin(),chunks.end(),
            [&germ1, &highest_move](map_chunk const& chnk)
            {
                if(chnk.contains(germ1))
                    {
                        std::for_each(chnk.grounds.begin(),chnk.grounds.end(),[&germ1, &highest_move](map_block* item)
                        {
                            if(item->affected(germ1.getPosition(),germ1.getradius()) )
                            {
                                for (uint8_t i =0 ;i<4;i++)
                                {
                                    sf::Vector2f circ_to_point =  item->block[i].position - germ1.getPosition();
                                    float lift_p = sqrt ( (germ1.getradius()*germ1.getradius()) - ( (item->block[i].position - germ1.getPosition()).x * (item->block[i].position-germ1.getPosition()).x) );

                                    if(length_of(item->block[i].position - germ1.getPosition()) <= germ1.getradius() &&
                                       item->block[i].position.y < germ1.get_climbing_height() )
                                    {
                                        highest_move = 0.f;
                                        break;
                                    }

                                    else if(length_of(item->block[i].position - germ1.getPosition()) <= germ1.getradius() &&
                                            item->block[i].position.y > germ1.get_climbing_height()&&
                                            lift_p-circ_to_point.y > highest_move)
                                    {
                                        highest_move = lift_p-circ_to_point.y;
                                    }
                                }
                            }
                        });
                    }
            });

    germ1.move(sf::Vector2f{0.f, - highest_move});
}

void ground::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
#ifdef DEBUG
    std::for_each(blocks.begin(),blocks.end(),[&states, &target](map_block*  block)

    {
        target.draw( *block,states);
    });

#else
    states.texture = &texture;

    std::for_each(blocks.begin(),blocks.end(),[&states, &target](map_block*  block){target.draw( *block,states);});

#endif
}

void ground::set_chunks(int w, int h)
{
    chunks.clear();
    for( int y = 0; y<h; y += floor(chunk_size.y) )
        {
            for( int x = 0; x < w ; x += floor(chunk_size.x) )
            {
                chunks.push_back( map_chunk{sf::Vector2f{static_cast<float>(x), static_cast<float>(y)}} );
                std::for_each(blocks.begin(),blocks.end(),[this](map_block* item)
                {
                    if(chunks.back().rect.intersects(sf::FloatRect{item->block[1].position,sf::Vector2f{pixel_size,pixel_size}}))
                    {
                        chunks.back().grounds.push_back(item);
                    }
                });
            }
        }
}

bool ground::map_chunk::contains(object const &object1)const
{
    return rect.intersects(object1.getGlobalBounds());
}

bool ground::map_chunk::is_collision(object const &object1)const
{
    return std::any_of(grounds.begin(),grounds.end(),[&object1](map_block* item)
    {
        return item->affected( object1.getPosition(), object1.getradius() );
    });
}
