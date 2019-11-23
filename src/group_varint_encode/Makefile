gve: group_varint_encode.o test_group_varint_encode.o
	g++ group_varint_encode.o test_group_varint_encode.o -o gve -lgtest -lpthread
group_varint_encode.o:
	g++ -c -g group_varint_encode.cpp
test_group_varint_encode.o:
	g++ -c test_group_varint_encode.cpp -lgtest -lpthread
clean:
	rm *.o gve
