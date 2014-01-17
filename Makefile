main: model.o ai.o application.o player.o gameexception.o gamer.o main.o menu.o options.o view.o applayer.o
	g++ model.o ai.o application.o player.o gameexception.o gamer.o main.o menu.o options.o view.o applayer.o -o main -lsfml-graphics -lsfml-window -lsfml-system
main.o: main.cpp application.h gameexception.h
	g++ -c main.cpp
model.o: model.cpp model.h gamer.h ai.h view.h application.h gameexception.h player.h options.h applayer.h
	g++ -c model.cpp
ai.o: ai.cpp ai.h model.h player.h options.h view.h application.h
	g++ -c ai.cpp
application.o: application.cpp application.h model.h options.h menu.h mapeditor.h
	g++ -c application.cpp
player.o: player.cpp player.h model.h gameexception.h
	g++ -c player.cpp
gameexception.o: gameexception.cpp gameexception.h
	g++ -c gameexception.cpp
gamer.o: gamer.cpp gamer.h player.h model.h application.h options.h view.h
	g++ -c gamer.cpp
menu.o: menu.cpp menu.h applayer.h application.h model.h view.h 
	g++ -c menu.cpp
options.o: options.cpp options.h applayer.h view.h application.h
	g++ -c options.cpp
view.o: view.cpp view.h applayer.h application.h model.h options.h 
	g++ -c view.cpp
applayer.o: applayer.cpp applayer.h
	g++ -c applayer.cpp
clean:
	rm -f *.o; rm main
install:
	cp  sfml/lib/*.* /usr/lib/; rm -r /usr/include/SFML; mkdir /usr/include/SFML; cp -R sfml/include/SFML/* /usr/include/SFML/
