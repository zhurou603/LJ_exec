FILE_SORT: test_filesort.o file_sort.o
	g++ test_filesort.o file_sort.o -o FILE_SORT -lgtest -lpthread

test_filesort.o:
	g++ -c test_filesort.cpp -lgtest -lphread

file_sort.o:
	g++ -c file_sort.cpp
