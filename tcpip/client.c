/* TCP/IP 연결
 *
 * TCP_SERVER는 서버용 프로그램이다.
 * 이에 연결하기 위한 TCP_CLIENT 프로그램을 만들어보자.
 *
 * comment 처리된 부분만 적절하게 채워넣는다면 서버와 연결이 가능하다.
 * 서버와 연결한 후 network 관련 용어들에 대한 답을 정확하게 제시하면 다음 문제를 위한 암호를 얻을 수 있다.
 * 
 * ps. 답은 영소문자로 입력해야한다.
 *
 */

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

    client_sock = /* 1.           */;
    if(client_sock == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));


    serv_adr_size = sizeof(serv_adr);

    // Connect
    if(/* 2.                                        */ == -1)
        error_handling("Connect() error!");

    printf("Ready to solve? (y/n)\n");
    scanf("%s", message_from_client);

    // send message_from_client to server
    write(/* 3.                                              */));

    while(1){

        memset(message_from_serv, 0, BUF_SIZE);

        // recieve message from server
        str_len = /* 4.                                       */

        printf("%s\n", message_from_serv);

        if(!strncmp(message_from_serv, END_MESSAGE, str_len)) {
            exit_ok = 1;
            break;
        }

        scanf("%s", message_from_client);

        write(/* 5.                                               */);
    }

    close(client_sock);

    return 0;
}

