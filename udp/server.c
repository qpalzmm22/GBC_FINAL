#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 300
#define NUM_PROBLEMS 5
#define TIME_LIMIT 30
#define PASSWORD "213131"
#define END_MESSAGE "FINISH"

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

int question(char* quest, char* ans, int sock, struct sockaddr_in client_adr){
    int str_len;
    int valid_test = 0x0;
    char message[BUF_SIZE];
    socklen_t client_adr_size = sizeof(client_adr);


    sendto(sock, quest, strlen(quest), 0, (struct sockaddr*)&client_adr, sizeof(client_adr)); 
    str_len = recvfrom(sock, message, BUF_SIZE, 0, (struct sockaddr*)&client_adr, &client_adr_size);  // ready to recieve data from client

    if( str_len < 0 ){

        char error_message[100] = { 0x0 };
        sprintf(error_message, "No Response for %d Seconds.\nQuitting the Server Program", TIME_LIMIT);
        error_handling(error_message);
    }


    if(strncmp(message, ans, str_len) == 0)   // if the recieved message was "ans"
        valid_test = 1; 

    return valid_test; 
}

int main(int argc, char *argv[]){
    int host_sock;
    char message[BUF_SIZE];

    struct sockaddr_in host_adr, client_adr;

    socklen_t client_adr_size;
    int str_len;


    // needs to initialized to 0
    int valid[NUM_PROBLEMS];

    char* instruction = "\n클라이언트 프로그램을 성공적으로 만드셨군요! 축하합니다.\n이제 다음의 다섯 문제를 푼다면 다음 문제의 암호를 주도록하죠.\n각 문제를 푸는데 30초가 지나면 자동으로 서버가 종료됩니다! 서두르세요!\n";

    char* q_array[NUM_PROBLEMS];
    char* ans_array[NUM_PROBLEMS];

    int is_correct[NUM_PROBLEMS];

    int cur_problem_num;

    q_array[0] = "\n1. 한 대의 스위치를 여러개의 네트워크로 나누기 위해 사용하는 기술은?\n 답 : _______ LAN\n";
    q_array[1] = "\n2. 목적지와 목적지로 가려면 어느 인터페이스로 가야 하는지의 정보는 Routing _____ 에 기록된다.\n";
    q_array[2] = "\n3. 목적지까지의 거리와 어떤 인접 라우터를 거쳐서 가야하는 지를 저장하는 Vector.\n 답 : ________ Vector\n";
    q_array[3] = "\n4. Link state를 사용하는 Routing Protocol은?\n 답 : ____\n";
    q_array[4] = "\n5. 출발지에서 목적지 뿐만 아니라 중간 경로에 대한 정보와 소요시간을 확인해주는 프로그램의 이름은?\n 답 : _____\n";

    ans_array[0] = "virtual";
    ans_array[1] = "table";
    ans_array[2] = "distance";
    ans_array[3] = "ospf";
    ans_array[4] = "trace";

    struct timeval tv;

    tv.tv_sec = TIME_LIMIT;
    tv.tv_usec = 0;

    if(argc != 2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    host_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(host_sock == -1)
        error_handling("socket() error");

    memset(&host_adr, 0, sizeof(host_adr));         // Initialize host_adr to 0
    host_adr.sin_family = AF_INET;                  // IPv4
    host_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    host_adr.sin_port = htons(atoi(argv[1]));

    if(bind(host_sock, (struct sockaddr*) &host_adr, sizeof(host_adr)) == -1)   // binding
        error_handling("bind() error");


    // connect to the client. Trying to recieve.
    client_adr_size = sizeof(client_adr);

    // repeat until all answers are correct
    while(1){

        // Signal to identify the client
        str_len = recvfrom(host_sock, message, BUF_SIZE, 0, (struct sockaddr*)&client_adr, &client_adr_size);  // ready to recieve data from client

        // Send instruction
        sendto( host_sock, instruction, BUF_SIZE, 0, (struct sockaddr*)&client_adr, client_adr_size );

        setsockopt( host_sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(tv) );
        cur_problem_num = 0;

        // repeat until all questions are correct or there hasn't reponse for TIME_LIMIT 
        while( 1 ){
            if( cur_problem_num == NUM_PROBLEMS ){
                sendto( host_sock, END_MESSAGE, BUF_SIZE, 0, (struct sockaddr*)&client_adr, client_adr_size );
                printf("\n\nPASSWORD : %s\n\n", PASSWORD);
                break;
            }

            // + 1 if correct, else, repeat the question
            cur_problem_num += question(q_array[cur_problem_num], ans_array[cur_problem_num], host_sock, client_adr);

        }

        if(cur_problem_num == NUM_PROBLEMS) break;

        close(host_sock);
    }
    return 0;
}
