bst: bst.o test_bst.o
	g++ bst.o test_bst.o -o bst -lgtest -lpthread
bst.o:
	g++ -c bst.cpp -lgtest -lpthread
test_bst.o:
	g++ -c test_bst.cpp -lgtest -lpthread
clean:
	rm *.o bst
