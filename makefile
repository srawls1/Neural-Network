cpp = g++
flags = -std=c++17 -Wall -Wextra -pedantic

all: Main

Main: main.o NeuralNetwork.o
	$(cpp) $(flags) main.o NeuralNetwork.o -o Main

main.o: main.cpp NeuralNetwork.h Vector.h Types.h
	$(cpp) $(flags) -c main.cpp

NeuralNetwork.o: NeuralNetwork.cpp NeuralNetwork.h Vector.h Types.h
	$(cpp) $(flags) -c NeuralNetwork.cpp

clean:
	rm *.o Main
