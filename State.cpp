#ifndef STATE
#define STATE
#include <SFML/Graphics.hpp>
#include <queue>
#include <string>
#include "world.h"
#include "rocketlauncher.hpp"
#include "ground.hpp"
class State{
 public:
  virtual void handle(sf::Event event, world &world1, rocketlauncher &rock, ground &mark, sf::RenderWindow &window) = 0;
  virtual void update() = 0;
  virtual void render(std::queue<State*> &k,sf::RenderWindow &window, world &world1, rocketlauncher &rock) = 0;
  void originCenterer(sf::Transformable &obj, sf::FloatRect bounds)
  {
    obj.setOrigin(bounds.width/2,bounds.height/2);
  };
  std::string statename{"State"};
 protected:
  bool close{false};
  
};
#endif
