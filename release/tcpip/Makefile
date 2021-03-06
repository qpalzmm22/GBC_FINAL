CC = gcc
CLIENT = TCP_Client
SERVER = TCP_Server

all : $(CLIENT) $(SERVER)

$(CLIENT) : client.c
	$(CC) -o $(CLIENT) client.c

$(SERVER) : server.c
	$(CC) -o $(SERVER) server.c

clean : 
	rm *.o $(CLIENT) $(SERVER)
