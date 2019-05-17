
#include <iostream>

#include <SFML/Graphics.hpp>

#include "definitions.h"
#include "ground.hpp"
#include "germ.h"
#include "rocket.hpp"
#include "rocketlauncher.hpp"
#include "lazergun.hpp"
#include "ResourcePath.hpp"
#include "world.h"



using namespace sf;

int main() {
   // sf::View fixed = window.getView();

   
    groundtex.setRepeated(true);
    Music bestmusic;
    if(!groundtex.loadFromFile(resourcePath() + "ground.png"))
    {
        return 1;
    }
    if(!bestmusic.openFromFile(resourcePath() + "game music lol.wav")){
        return EXIT_FAILURE;
    }
    bestmusic.play();
    bestmusic.setLoop(true);
    if(!germtex.loadFromFile(resourcePath() + "germ.png"))
    {
        return 69;
    }
    if(!font.loadFromFile(resourcePath() + "font.ttf"))
    {return 1337;}

    if(!guntex.loadFromFile(resourcePath() + "gun.png"))
    {return 13237;}

    if(!grentex.loadFromFile(resourcePath() + "grenade.png")){
        return 123;
    }
    if(!lazertex.loadFromFile(resourcePath()+ "Picture2.png")){
        return 70;
    }
    if(!beamtext.loadFromFile(resourcePath()+ "Picture1.png")){
        return 70;
    }
    if(!scope.loadFromFile(resourcePath()+ "92-512.png")){
        return 70;
    }
    
    
    

    
    RenderWindow window {
        VideoMode { width, height },
        "mmmmmmmm..."
    };
    window.setMouseCursorVisible(false);
    
    ground mark (world_width, world_height, pixel_size, groundtex);
    world world1(&mark);
    
    player player1{Color::Red};
    player player2 {Color::Blue};
    player1.add_germ(Sprite{germtex}, Vector2f{width/2,50.f}, "Greve Jackula" ,font);
    player2.add_germ(Sprite{germtex},Vector2f{width/4.f,50.f}, "Eminem(not afraid)" ,font);
    player1.add_germ(Sprite{germtex},Vector2f{width/8.f,50.f},"THANOS",font);
    world1.add_player(player1);
    world1.add_player(player2);
    
    sf::Sprite beam{beamtext};
    sf::Sprite grenade{grentex};
    Sprite* lol = &grenade;
    sf::Sprite cursorscope{scope};
    cursorscope.setOrigin(cursorscope.getGlobalBounds().width/2.f,cursorscope.getGlobalBounds().height/2.f);
    cursorscope.setScale(0.1f,0.1f);

    Clock clock;
    
    world1.add_weapon(new rocketlauncher {Sprite {guntex}, world1.curr().getPosition(), &grentex});
    world1.add_weapon(new lazergun{Sprite {lazertex},world1.curr().getPosition(),&beamtext});
    

#ifndef DEBUG

    double const fps { 60.0 };
#else
    double const fps{12.0};
#endif
    // beräkna hur lång tid vi har per frame
    auto const target { milliseconds ( 1000.0 / fps ) };

    while( window.isOpen())
    {
        clock.restart();
        Event event;
        while (window.pollEvent(event))
        {
            
            if (event.type == Event::Closed){ window.close(); }
            else if (event.type == Event::MouseMoved) {
                auto mouse = event.mouseMove;
                cursorscope.setPosition(mouse.x,mouse.y);

            } else if (event.type == Event::MouseButtonPressed) {
                auto mouse{event.mouseButton};
                // är det vänster musknapp?
                    if (mouse.button == Mouse::Button::Left)
                {

                    if(!world1.is_projectile()){

                        world1.add_projectile(world1.current_weapon().fire(sf::Vector2f(mouse.x,mouse.y)));
               world1.rotate(); }
                }
                    else if(mouse.button ==Mouse::Button::Right)
                    {
                       
                        world1.rotate();
                    }

            }
            else if(event.type==Event::KeyPressed){
                if (event.key.code == Keyboard::Num1){
                    world1.swap_weapon();
                }
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
        window.clear();
        

        window.draw(cursorscope);
        window.draw(world1);
        window.display();
        auto wait_time { target - clock.getElapsedTime () };
        
        std::cout<<wait_time.asMilliseconds()<<" x: "<<world1.curr().getPosition().x<<" y : "<<world1.curr().getPosition().y<<'\n';
        
        
        sleep (wait_time);
        
        
    }
    return EXIT_SUCCESS;
}

  
