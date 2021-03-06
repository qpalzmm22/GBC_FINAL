CC = g++
TARGET = p4_check

$(TARGET) : p4.o check.o
	$(CC) -o $(TARGET) p4.o check.o -lpthread

p4.o : p4.cpp
	$(CC) -c -o p4.o p4.cpp

check.o : check.cpp
	$(CC) -c -o check.o check.cpp

clean : 
	rm *.o $(TARGET)
