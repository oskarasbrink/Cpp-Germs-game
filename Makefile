main: main.o germ.o ground.o object.o projectile.o rocket.o rocketlauncher.o weapon.o world.o State.o GameState.o MenuState.o
	g++ main.o germ.o ground.o object.o projectile.o rocket.o rocketlauncher.o weapon.o world.o State.o GameState.o MenuState.o statemachine.o -o Oskar -Wno-deprecated-declarations -Wall -Wextra -pedantic -std=c++1z -Weffc++ -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
#part
main.o: main.cpp definitions.h ground.hpp germ.h rocket.hpp rocketlauncher.hpp world.h
	g++ -Wno-deprecated-declarations -Wall -Wextra -pedantic -std=c++1z -Weffc++ -c main.cpp -L$(SFML_ROOT)/lib -I$(SFML_ROOT)/include

germ.o: germ.cc germ.h ground.hpp definitions.h
	g++ -Wno-deprecated-declarations -Wall -Wextra -pedantic -std=c++1z -Weffc++ -c germ.cc -L$(SFML_ROOT)/lib -I$(SFML_ROOT)/include

ground.o: ground.cpp ground.hpp germ.h definitions.h
	g++ -Wno-deprecated-declarations -Wall -Wextra -pedantic -std=c++1z -Weffc++ -c ground.cpp -L$(SFML_ROOT)/lib -I$(SFML_ROOT)/include

object.o: object.cc object.h
	g++ -Wno-deprecated-declarations -Wall -Wextra -pedantic -std=c++1z -Weffc++ -c object.cc -L$(SFML_ROOT)/lib -I$(SFML_ROOT)/include

projectile.o: projectile.cpp projectile.hpp 
	g++ -Wno-deprecated-declarations -Wall -Wextra -pedantic -std=c++1z -Weffc++ -c projectile.cpp -L$(SFML_ROOT)/lib -I$(SFML_ROOT)/include

rocket.o: rocket.cpp rocket.hpp 
	g++ -Wno-deprecated-declarations -Wall -Wextra -pedantic -std=c++1z -Weffc++ -c rocket.cpp -L$(SFML_ROOT)/lib -I$(SFML_ROOT)/include

rocketlauncher.o: rocketlauncher.cpp rocketlauncher.hpp 
	g++ -Wno-deprecated-declarations -Wall -Wextra -pedantic -std=c++1z -Weffc++ -c rocketlauncher.cpp -L$(SFML_ROOT)/lib -I$(SFML_ROOT)/include

weapon.o: weapon.cpp weapon.hpp 
	g++ -Wno-deprecated-declarations -Wall -Wextra -pedantic -std=c++1z -Weffc++ -c weapon.cpp -L$(SFML_ROOT)/lib -I$(SFML_ROOT)/include

world.o: world.cc world.h definitions.h 
	g++ -Wno-deprecated-declarations -Wall -Wextra -pedantic -std=c++1z -Weffc++ -c world.cc -L$(SFML_ROOT)/lib -I$(SFML_ROOT)/include

State.o: State.cpp
	g++ -Wno-deprecated-declarations -Wall -Wextra -pedantic -std=c++1z -Weffc++ -c State.cpp -I$(SFML_ROOT)/include
GameState.o: GameState.cpp State.cpp definitions.h 
	g++ -Wno-deprecated-declarations -Wall -Wextra -pedantic -std=c++1z -Weffc++ -c GameState.cpp -I$(SFML_ROOT)/include

MenuState.o: MenuState.cpp State.cpp 
	g++ -Wno-deprecated-declarations -Wall -Wextra -pedantic -std=c++1z -Weffc++ -c MenuState.cpp -I$(SFML_ROOT)/include

statemachine.o: statemachine.hpp statemachine.cpp world.h 
	g++ -Wno-deprecated-declarations -Wall -Wextra -pedantic -std=c++1z -Weffc++ -c statemachine.cpp -I$(SFML_ROOT)/include

zap:
	@ \rm -rf *.o *.out

