main: longest_increasing_subsequence.o test.o
	g++ longest_increasing_subsequence.o test.o -o main -lgtest -lpthread
main.o:
	g++ -c longest_increasing_subsequence.cpp
test.o:
	g++ -c test.cpp	-lgtest -lpthread

clean:
	rm *.o ./main
