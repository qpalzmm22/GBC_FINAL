#pragma once

#include <time.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <pthread.h>


#define MAX 499
#define ANS 86168291600238450732788312165664788095941068326060883324529903470149056115823592713458328176574447204501

using namespace std;

extern long long fib(long long n);

void * thread_main(void *arg){
        int *pWorkStatus = (int*) arg;
        fib(MAX);
        *pWorkStatus = 1;
        return NULL;
}


void checktime(){
        clock_t start, end;  
        long long ans;
        pthread_t _fib;
        int thread_status = 0;

        start = clock();
        pthread_create(&_fib, NULL, thread_main, (void *)&thread_status);
        pthread_detach(_fib);


        double time_taken = 0;


        // After 1 sec
        while(time_taken < 1){
                end = clock(); 
                time_taken = double(end - start) / double(CLOCKS_PER_SEC);
        }

        printf("\n\n");
        // Check if the thread is alive
        if(thread_status == 1){
                if(fib(MAX) == ANS){
                        printf("Good Job!\nPassword : 1q2w3e\n");
                }
        }
        else{
                printf("time took longer than 1 sec\n");
        }
        sleep(2);
}

int main(){
        checktime();
        return 0;
}
