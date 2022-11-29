CC=g++ -std=c++11 -g

OBJS=main.o Building.o Point2D.o Vector2D.o GameObject.o GameCommand.o PokemonCenter.o Model.o Trainer.o PokemonGym.o View.o

default: PA3

PA3: $(OBJS)
	$(CC) -o PA3 $(OBJS) 

Vector2D.o: Vector2D.cpp Vector2D.h
	$(CC) -c Vector2D.cpp -o Vector2D.o 
	
Point2D.o: Point2D.cpp Point2D.h Vector2D.h
	$(CC) -c Point2D.cpp -o Point2D.o 

Building.o: Building.cpp Building.h
	$(CC) -c Building.cpp -o Building.o

GameObject.o: GameObject.cpp GameObject.h Point2D.h Vector2D.h
	$(CC) -c GameObject.cpp -o GameObject.o 

PokemonCenter.o: PokemonCenter.cpp PokemonCenter.h GameObject.h Point2D.h
	$(CC) -c PokemonCenter.cpp -o PokemonCenter.o

Model.o: Model.cpp Model.h GameObject.h Trainer.h PokemonGym.h PokemonCenter.h View.h
	$(CC) -c Model.cpp -o Model.o 

PokemonGym.o: PokemonGym.cpp PokemonGym.h GameObject.h Point2D.h
	$(CC) -c PokemonGym.cpp -o PokemonGym.o

View.o: View.cpp View.h GameObject.h Point2D.h
	$(CC) -c View.cpp -o View.o 

Trainer.o: Trainer.cpp Trainer.h GameObject.h Point2D.h Vector2D.h PokemonCenter.h PokemonGym.h
	$(CC) -c Trainer.cpp -o Trainer.o

GameCommand.o: GameCommand.cpp GameCommand.h Model.h GameObject.h Trainer.h PokemonGym.h PokemonCenter.h
	$(CC) -c GameCommand.cpp -o GameCommand.o
	
main.o: main.cpp Building.h Point2D.h Vector2D.h GameCommand.h PokemonCenter.h Model.h Trainer.h PokemonGym.h GameObject.h View.h
	$(CC) -c main.cpp -o main.o

#checkpoint commands below

checkpoint1: TestCheckPoint1.cpp Point2D.o Vector2D.o GameObject.o
	$(CC) -o checkpoint1.exe TestCheckPoint1.cpp Point2D.o Vector2D.o GameObject.o
	
checkpoint2: TestCheckPoint2.cpp Point2D.o Vector2D.o GameObject.o Building.o PokemonCenter.o PokemonGym.o
	$(CC) -o checkpoint2.exe TestCheckPoint2.cpp Point2D.o Vector2D.o GameObject.o Building.o PokemonCenter.o PokemonGym.o
	
#add your own tests for other checkpoints here

finalcheckpoint: main.cpp Point2D.o Vector2D.o GameObject.o Building.o PokemonCenter.o PokemonGym..o Trainer.o Model.o View.o GameCommand.o
	$(CC) -g -o PA3.exe main.cpp Point2D.o Vector2D.o GameObject.o Building.o PokemonCenter.o PokemonGym.o Trainer.o Model.o View.o GameCommand.o

clean: 
	rm $(OBJS) PA3 *.exe