CXX = g++
CFLAGS = -g -std=c++17 -O2

SRCS=main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))
all:helloData


main.o:
	$(CXX) $(CFLAGS) -c main.cpp -o main.o 


helloData: $(OBJS)
	$(CXX) $(CFLAGS) -o helloData $(OBJS)

.PHONY: test clean

test: 
		./helloData

clean:
	rm -f helloData
