TARGET ?= test

all:
	g++ -O3 -Wall -std=c++11 norm.cpp $(TARGET).cpp -o $(TARGET)

check:
	$(MAKE) TARGET=test
	./test
	rm ./test

bench:
	$(MAKE) TARGET=bench
	./bench
	rm ./bench
