CC = g++
TARGET = p1.exe

$(TARGET) : .p1.o .check.o
	$(CC) -o $(TARGET) .p1.o .check.o -lpthread

.p1.o : p1.cpp
	$(CC) -c -o .p1.o p1.cpp

.check.o : .check.cpp
	$(CC) -c -o .check.o .check.cpp

clean : 
	rm .*.o $(TARGET)
