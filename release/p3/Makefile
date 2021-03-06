CC = g++
TARGET = p3.exe

$(TARGET) : .p3.o .check.o
	$(CC) -o $(TARGET) .p3.o .check.o -lpthread

.p3.o : p3.cpp
	$(CC) -c -o .p3.o p3.cpp

.check.o : .check.cpp
	$(CC) -c -o .check.o .check.cpp

clean : 
	rm .*.o $(TARGET)
