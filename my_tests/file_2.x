all: exe

exe: main.o sum_array.o
	g++-10 -Wall -g -std=c++11 -pthread main.o sum_array.o -o exe
	
main.o: main.cpp
	g++-10 -c main.cpp
	
sum_array.o: sum_array.cpp
	g++-10 -c sum_array.cpp
	
clean:
	rm -rf *.o exe
