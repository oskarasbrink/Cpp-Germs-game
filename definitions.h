//
// Created by drsve on 2019-05-03.
//

#ifndef GERMS_DEFINITIONS_H
#define GERMS_DEFINITIONS_H
#include <SFML/Graphics.hpp>
#include <math.h>
#include <SFML/Audio.hpp>

//#define DEBUG
static sf::Texture grentex;
static sf::Texture guntex;
static sf::Font font;
static sf::Texture germtex;
static sf::Texture groundtex;
static sf::Texture lazertex;
static sf::Texture beamtext;
static sf::Texture scope;
static sf::Texture walltex;

const uint8_t pixel_size = 13;
static const sf::Vector2f chunk_size{104.f,104.f};
const float gravity = 1.5f;

const float germ_walkspeed = 4.0;

int const width  { 1280 };
int const height { 960 };
int const world_width{ 1280 };
int const world_height{ 960 };

#endif //GERMS_DEFINITIONS_H
