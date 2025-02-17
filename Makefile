.PHONY: all clean

all: main

clean:
	rm main

main: main.cpp
	g++ main.cpp -o main -lSDL2 -lpython3.11 -lSDL2_image
