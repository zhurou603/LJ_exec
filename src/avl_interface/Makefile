AVL: test_avl.o avl.o
	g++ test_avl.o avl.o -o AVL -lgtest -lpthread
test_avl.o: test_avl.cpp
	g++ -c test_avl.cpp -lgtest -lpthread
avl.o: avl.cpp
	g++ -c avl.cpp
clean:
	rm *.o
