CXX = g++
CFLAGS = -std=c++14 -O2 -Wall -g

TARGET = main
OBJS = ../src/log/*.cpp ../src/buffer/*.cpp ../src/main.cpp

all: $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o ../bin/$(TARGET)  -pthread -lmysqlclient

clean:
	rm -rf ../bin/$(OBJS) $(TARGET)




