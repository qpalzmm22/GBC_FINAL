/* TCP/IP 연결
 *
 * UDP_SERVER는 서버용 프로그램이다.
 * 이에 연결하기 위한 UDP_CLIENT 프로그램을 만들어보자.
 *
 * comment 처리된 부분만 적절하게 채워넣는다면 서버와 연결이 가능하다.
 * 서버와 연결한 후 network 관련 용어들에 대한 답을 정확하게 제시하면 다음 문제를 위한 암호를 얻을 수 있다.
 *
 * ps. 답은 영소문자로 입력해야한다.
 * */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 300
#define END_MESSAGE "FINISH"
#define RCV_TIME 3

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

    struct timeval tv;
    tv.tv_sec = RCV_TIME;
    tv.tv_usec = 0;

    setsockopt( client_sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv,  sizeof(tv) );
    // Connect
    sendto(client_sock, message_from_client, BUF_SIZE, 0, (struct sockaddr*)&serv_adr, sizeof(serv_adr));


    // Receive Instruction from the server
    
     str_len = recvfrom(client_sock, message_from_client, BUF_SIZE, 0, (struct sockaddr*)&serv_adr, &serv_adr_size);

    if(str_len < 0)
        error_handling("Server not responding\n");
    printf("%s\n", message_from_client);
    
    while(1){

        memset(message_from_serv, 0, BUF_SIZE);
        str_len = recvfrom(client_sock, message_from_serv, BUF_SIZE, 0, (struct sockaddr*)&serv_adr, &serv_adr_size);

        if(str_len < 0)
            error_handling("Server not responding\n");
        

        if(!strncmp(message_from_serv, END_MESSAGE, str_len)) {
            exit_ok = 1;
            break;
        }

        printf("%s\n", message_from_serv);
        
        scanf("%s", message_from_client);
        sendto(client_sock, message_from_client, BUF_SIZE, 0, (struct sockaddr*)&serv_adr, sizeof(serv_adr));
    }


    close(client_sock);

    return 0;
}

