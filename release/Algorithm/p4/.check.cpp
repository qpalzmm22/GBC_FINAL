/* 1. turn test cases into arrays to test variety of test cases
 * 2. make global variables minimum somehow
 * 3. consider how users can test their own codes without the danger of harming the function of this codea
 *
 */

#pragma once

#include <stdio.h>
#include <vector>
#include <time.h>
#include <unistd.h>
#include <utility>
#include <bits/stdc++.h>
#include <pthread.h>

#define MAX_VALUE 1001
#define PASS "jkjlk2"

using namespace std;

extern int gcd(int a, int b);

int valid = 1; // it's valid( gcd algorithm works as is )
 
void test_gcd(){
        
        vector<int> result;
        vector<int> answer;

        result.push_back(gcd(722, 190));
        answer.push_back(38);

        result.push_back(gcd(126542, 4142131));
        answer.push_back(157);

        result.push_back(gcd(24, 12));
        answer.push_back(12);
        
        result.push_back(gcd(2147483646, 2127423247));
        answer.push_back(1);

        for(int i = 0; i < answer.size(); i++){
                if(answer[i] != result[i]){
                        printf("%d : %d, %d", i ,answer[i], result[i]);
                        valid = 0;        
                
                }
        }
}

void * thread_main(void *arg){
        int *pWorkStatus = (int*) arg;

        printf("\n");
        test_gcd();

        *pWorkStatus = 1;
        return NULL;
}

void checktime(){
        clock_t start, end;  
        long long ans;
        pthread_t _test_thread;
        int thread_status = 0;

        start = clock();
        pthread_create(&_test_thread, NULL, thread_main, (void *)&thread_status);
        pthread_detach(_test_thread);


        double time_taken = 0;

        
        // After 1 sec
        while(time_taken < 2){
                end = clock(); 
                time_taken = double(end - start) / double(CLOCKS_PER_SEC);
                if(thread_status == 1)
                        break;
        }
        
        

        printf("\n\n");
        // Check if the thread is alive
        if(thread_status == 1){
                printf("The algorithm took %lf seconds to finish\n\n", time_taken);
                
                if(valid == 1) 
                        printf("Good job!\n\nPassword is %s\n", PASS);
        }
        else{
                printf("time took longer than 2 sec\n");
        }
        sleep(2);
}

int main(){
        // Check if algorithm is valid
        checktime();

        return 0;
}
