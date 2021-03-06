CC = g++
TARGET = p2_check

$(TARGET) : p2.o check.o
	$(CC) -o $(TARGET) p2.o check.o -lpthread

p2.o : p2.cpp
	$(CC) -c -o p2.o p2.cpp

check.o : check.cpp
	$(CC) -c -o check.o check.cpp

clean : 
	rm *.o $(TARGET)
