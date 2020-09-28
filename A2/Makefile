.default: all

all: A2

clean:
	rm -f A2 *.o

A2: AzulGame.o Factory.o Node.o Player.o PlayerBoard.o Tile.o TileBag.o main.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^