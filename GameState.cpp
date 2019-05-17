#ifndef Game
#define Game
#include <SFML/Graphics.hpp>
#include "State.cpp"
#include "definitions.h"
#include "world.h"
#include "rocket.hpp"
#include "rocketlauncher.hpp"
#include <queue>
#include <exception>
#include <vector>
#include <iostream>
using namespace sf;

class GameState : public State{
 
private:
  
public:
  GameState(std::vector<std::string> names)
    {
    //fixa namn
    //
      statename="Game";
      std::cout<<"Konstruk"<<std::endl;
    }
  void handle(sf::Event event,world &world1,rocketlauncher &rock, ground &mark,sf::RenderWindow &window){
    std::cout<<"Handle"<<std::endl;
    if (event.type == sf::Event::Closed){
      close=true;
    }
    else if (event.type == Event::MouseMoved) {
                auto mouse = event.mouseMove;
    }
    else if (event.type == Event::MouseButtonPressed) {
      auto mouse{event.mouseButton};
        // är det vänster musknapp?
    if (mouse.button == Mouse::Button::Left)
      {
          if(!world1.is_projectile()){
              
              world1.add_projectile(world1.current_weapon().fire(sf::Vector2f(mouse.x,mouse.y)));
              world1.rotate(); }
      }
    else if(mouse.button == Mouse::Button::Right)
      {
	world1.rotate();
      }

    }
    
    if (Keyboard::isKeyPressed(Keyboard::A))
      {
	if(Keyboard::isKeyPressed(Keyboard::Space))
	  {
	    world1.curr().jump(germ::LEFT);
	  }
	else
	  {
	    world1.curr().walk(germ::LEFT, &mark);
	  }
      }
    if (Keyboard::isKeyPressed(Keyboard::D))
      {
	if(Keyboard::isKeyPressed(Keyboard::Space))
            {
	      world1.curr().jump(germ::RIGHT);
            }
	else
	  {
	    world1.curr().walk(germ::RIGHT, &mark);
	  }
      }
    if(Keyboard::isKeyPressed(Keyboard::Space))
      {
            world1.curr().jump();
      }
    world1.update(window);
    rock.update(world1.curr().getPosition(),window);      
  }
  void update(){
   

  }
  void render(std::queue<State*> &k, sf::RenderWindow &window, world &world1, rocketlauncher &rock){
     if(close)window.close();
    if(window.isOpen()){
	  window.clear();
#ifndef DEBUG
	  window.draw(world1);
	  window.draw(rock);
#else
	  window.draw(world1);
#endif
	  window.display();
    }
    else{ k.pop(); }
    
  }
};
#endif
