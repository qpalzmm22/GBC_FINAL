CC = gcc
CLIENT = UDP_Client
SERVER = UDP_Server

all : $(CLIENT) $(SERVER)

$(CLIENT) : client.c
	$(CC) -o $(CLIENT) client.c

$(SERVER) : server.c
	$(CC) -o $(SERVER) server.c

clean : 
	rm *.o $(CLIENT) $(SERVER)
