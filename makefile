main: fun.o
	g++ -O3 -o main main.cpp fun.o
fun:
	g++ -O3 -c fun.cpp
test: fun_test.o
	g++ -std=c++11 -o fun_test fun_test.cpp fun.cpp 
clean:
	rm*.o main test