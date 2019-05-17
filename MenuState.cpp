#ifndef MENU
#define MENU
#include <SFML/Graphics.hpp>
#include "State.cpp"
#include "GameState.cpp"
#include <queue>
#include <string>
#include <vector>
class MenuState : public State{

 private:
  sf::Texture texture;
  sf::Sprite sprite;
  sf::Text text;
  sf::CircleShape tester;
  sf::Font font;
  sf::RectangleShape butt;
  sf::Event event;
  bool play;
  int anicount{0};
  bool aninc;
  std::string boxtext;
  std::vector<std::string> name;
  std::vector<std::string> output{"Player1","P1Germ1","P1Germ2","P1Germ3","P1Germ4","Player2","P2Germ1","P2Germ2","P2Germ3","P2Germ4"};
  sf::Text text2;
 public:
  MenuState():
    texture{},sprite{},text{},tester{3},font{},butt{sf::Vector2f(720.f, 160.f)},event{},play{false},aninc{true},boxtext{""},text2{}
    {
      if ( !texture.loadFromFile ("wall.jpg") )
	{
	  //TODO
	}
      if ( !font.loadFromFile ("font.ttf") )
	{
	  //TODO
	}
      statename="Menu";
      // skapa sprite
      sprite.setTexture( texture );
      auto size { texture.getSize () };
      sprite.setOrigin (size.x / 2, size.y / 2);
      sprite.scale(0.5f,0.5f);
      sprite.setPosition (640,360);

      originCenterer(butt,butt.getGlobalBounds());
      butt.setFillColor(sf::Color(255, 203, 73));
      butt.setOutlineColor(sf::Color::Black);
      butt.setOutlineThickness(-5.f);
      butt.setPosition(sprite.getPosition());

      text.setFont(font);
      text.setString(boxtext);
      text.setColor(sf::Color::Red);
      //text.setOutlineColor(sf::Color::Black);
      //text.setOutlineThickness(2);
      text2.setFont(font);
      text2.setString("Enter "+output[anicount]+"'s name: ");
      text2.setColor(sf::Color::Black);
      //text2.setOutlineColor(sf::Color::White);
      //text2.setOutlineThickness(2);
      text2.setOrigin(0,text.getGlobalBounds().height/2);
      text.setOrigin(text2.getOrigin());
      text2.setPosition(butt.getPosition().x-320.f,butt.getPosition().y-20);
      text.setPosition(text2.getPosition().x+text2.getGlobalBounds().width,text2.getPosition().y);
      }
  void handle(sf::Event event,world &world1,rocketlauncher &rock, ground &mark, sf::RenderWindow &window)
  {
	if (event.type == sf::Event::Closed){
	  close=true;
	}  
	if( event.type == sf::Event::TextEntered )
	  {
	    
	    if( event.text.unicode == 8 )
	      {
		if (boxtext.size()!=0)boxtext.erase( boxtext.size( ) - 1 );
	      }
	    else if( event.text.unicode == 13)
	      {
		name.push_back(boxtext);
		boxtext="";
		anicount++;
	       	
	      }
	    else if( event.text.unicode == 9)
	      {
		for(std::string s:name) boxtext+=(s+"\n");
	      }
	    else if(boxtext.size()<=13)
	      {
		boxtext+=(char)event.text.unicode;
	      }
	  if(anicount==10){
		  play=true;
	  }
	  else{
	    text2.setString("Enter "+output[anicount]+"'s name: ");
	    text.setString(boxtext);
	  }
	  }
	/*else if (!play && sf::Mouse::isButtonPressed(sf::Mouse::Left))
      {
	sf::Vector2i position = sf::Mouse::getPosition();
	auto buttbox = butt.getGlobalBounds();
	if(buttbox.contains(float(position.x),float(position.y))){
	    play=true;
	    text.setString("");
	    boxtext="";
	  }
	  }*/
    
 };
  void update(){
    //Dunno
    /*if(aninc){
      anicount++;
      if(anicount==144)aninc=false;
    }
    else{
      anicount--;
      if(anicount==48)aninc=true;
      }
    text.setCharacterSize(anicount/2);
    originCenterer(text,text.getLocalBounds());*/
    };
  void render(std::queue<State*> &k, sf::RenderWindow &window, world &world1, rocketlauncher &rock){
    if(close)window.close();
    if(play){
      k.pop();
    std::vector<std::string> name;
    k.push(new GameState{name});
    
    }      
    else if(window.isOpen()){
      window.clear();
      window.draw(sprite);
      window.draw(butt);
      window.draw(text);
      window.draw(text2);
      window.draw(tester);
      window.display();
    }
    //else{ k.pop(); }
  };
};
#endif
