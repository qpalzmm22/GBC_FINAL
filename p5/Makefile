CC = g++
TARGET = p5_check

$(TARGET) : p5.o check.o
	$(CC) -o $(TARGET) p5.o check.o -lpthread

p5.o : p5.cpp
	$(CC) -c -o p5.o p5.cpp

check.o : check.cpp
	$(CC) -c -o check.o check.cpp

clean : 
	rm *.o $(TARGET)
