main: main.o test.o
	g++ main.o test.o -o main -lgtest -lpthread
main.o:
	g++ -c main.cpp
test.o:
	g++ -c test.cpp -lgtest -lpthread
clean:
	rm *.o main