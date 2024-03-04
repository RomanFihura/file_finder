file-finder: file-finder.o main.o
	g++ file-finder.o main.o -o file-finder

file-finder.o: file-finder.cpp
	g++ -c file-finder.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o file-finder