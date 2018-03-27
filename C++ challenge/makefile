run: main.o lodepng.o
	g++ -o run lodepng.o main.o 

lodepng.o: lodepng.cpp lodepng.h
	g++ -c lodepng.cpp

main.o: main.cpp
	g++ -c main.cpp 
