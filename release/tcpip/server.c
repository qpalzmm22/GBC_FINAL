#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 200
#define END_MESSAGE "FINISH"
#define YES "y"


void error_handling(char *message);

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}


// 1. recieve answer from client
// 2. check if the recieved answer is correct
// 3. if correct send next level question
//      (if not correct send previous question)

int question(char* quest, char* ans, int sock){
    int str_len;
    int valid_test = 0;
    char message[BUF_SIZE];

    write (sock, quest, strlen(quest));

    str_len = read(sock, message, BUF_SIZE);

    if(strncmp(message, ans, str_len) == 0)   // if the recieved message was "ans"
        valid_test = 1;

    return valid_test; 
}

int main(int argc, char *argv[]){
    int serv_sock, clnt_sock;
    char message[BUF_SIZE];

    struct sockaddr_in serv_adr, client_adr;

    socklen_t client_adr_size;
    int str_len;

    // needs to initialized to 0
    int ready;
    int valid1, valid2, valid3, valid4, valid5;

    if(argc != 2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));         // Initialize serv_adr to 0
    serv_adr.sin_family = AF_INET;                  // IPv4
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1)   // binding
        error_handling("bind() error");

    // 연결대기요청 Queue size = 5  
    if(listen(serv_sock, 5) == -1)
        error_handling("listen() error");                                                                           

    client_adr_size = sizeof(client_adr);

    // Signal to identify the client
    clnt_sock = accept(serv_sock, (struct sockaddr*)&client_adr, &client_adr_size);
    if(clnt_sock == -1)
        error_handling("accept() error");
    else
        printf("Connected to client \n");

    // read if client is ready?
    str_len = read(clnt_sock, message, BUF_SIZE);

    //write (clnt_sock, message, str_len);


    if(strncmp(message, YES, str_len) == 0){   // if the recieved message was "YES"
        ready = 1;
    }

    while(ready){

        char* q1 = "\n1. 네트워크방식 중 하나로 csma/cd를 사용하는 방식은?\n 답 : _______\n";
        char* q2 = "\n2. OSI 7 layer의 앞글자를 입력하시오.\n 답 : _______\n";
        char* q3 = "\n3. hub는 한 포트로 들어오는 데이터를 나머지 모든 포트로 뿌려주는 특성 때문에 multiport ________ 라고 불린다.\n";
        char* q4 = "\n4. 다음은 어떠한 ip class 인가요?\nip address : 193.1.7.18   _ class\n";
        char* q5 = "\n5. ____ 번호는 컴퓨터에게 부여하는 값이 아닌 프로그램 상에서 생성되는 소켓을 구분하기 위해 소켓에 부여되는 번호이다.\n";

        char* ans1 = "ethernet";
        char* ans2 = "apstndp";
        char* ans3 = "repeater";
        char* ans4 = "c";
        char* ans5 = "port";



        if(valid1 || (valid1 = question(q1, ans1, clnt_sock))){
            if(valid2 || (valid2 = question(q2, ans2, clnt_sock))){
                if(valid3 || (valid3 = question(q3, ans3, clnt_sock))){
                    if(valid4 || (valid4 = question(q4, ans4, clnt_sock))){
                        if(valid5 || (valid5 = question(q5, ans5, clnt_sock))){
                            printf("GOOD JOB!\n");
                            write(clnt_sock, END_MESSAGE, sizeof(END_MESSAGE));
                            break;
                        }
                    }
                }
            }
        }
    }

    close(clnt_sock);

    close(serv_sock);

    return 0;
}
