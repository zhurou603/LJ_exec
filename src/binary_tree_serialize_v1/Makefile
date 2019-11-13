serialize: bst_serialize_v1.o test_bst_serialize_v1.o
	g++ bst_serialize_v1.o test_bst_serialize_v1.o -o serialize -lgtest -lpthread
   
bst_serialize.o:
	g++ -c bst_serialize_v1.cpp
    
test_bst_serialize.o:
	g++ -c test_bst_serialize_v1.cpp -lgtest -lpthread

clean:
	rm *.o serialize
