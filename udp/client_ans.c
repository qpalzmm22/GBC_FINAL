#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 200
#define END_MESSAGE "FINISH"

void error_handling(char *message);

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}



int main(int argc, char *argv[]){
    int client_sock;
    int exit_ok; // 1 to exit
    char message_from_client[BUF_SIZE];
    char message_from_serv[BUF_SIZE];

    struct sockaddr_in serv_adr;

    socklen_t serv_adr_size;
    int str_len;

    if(argc != 3){
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    client_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(client_sock == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));


    serv_adr_size = sizeof(serv_adr);

    // Connect
    printf("Ready to connect? (y/n)\n");
    scanf("%s", message_from_client);
    sendto(client_sock, message_from_client, BUF_SIZE, 0, (struct sockaddr*)&serv_adr ,sizeof(serv_adr));

    while(1){

        memset(message_from_serv, 0, BUF_SIZE);
        str_len = recvfrom(client_sock, message_from_serv, BUF_SIZE, 0, (struct sockaddr*)&serv_adr, &serv_adr_size);

        printf("%s\n", message_from_serv);

        if(!strncmp(message_from_serv, END_MESSAGE, str_len)) {
            exit_ok = 1;
            break;
        }

        scanf("%s", message_from_client);

        sendto(client_sock, message_from_client, BUF_SIZE, 0, (struct sockaddr*)&serv_adr, sizeof(serv_adr));
    }


    close(client_sock);

    return 0;
}

