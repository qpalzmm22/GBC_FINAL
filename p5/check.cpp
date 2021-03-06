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

#define MAX 10000

using namespace std;

extern bool use_union(vector<pair<int, int>> query, int a, int b);
extern int parent[MAX];
extern int N, M;

int valid = 1; // it's valid

void test_union(){
        vector<pair<int, int>> t_query1, t_query2;

        vector<bool> result;
        vector<bool> answer;

        t_query1.push_back(make_pair(1,2));
        t_query1.push_back(make_pair(2,3));
        t_query1.push_back(make_pair(4,5));
        t_query1.push_back(make_pair(4,6));

        t_query2.push_back(make_pair(7,8));
        t_query2.push_back(make_pair(7,9));
        t_query2.push_back(make_pair(7,10));

        result.push_back(use_union(t_query1, 1, 3));
        answer.push_back(true);
        result.push_back(use_union(t_query1, 1, 6));
        answer.push_back(false);
        result.push_back(use_union(t_query2, 7, 10));
        answer.push_back(true);

        for(int i = 0; i < answer.size(); i++){
                if(result[i] == answer[i])
                        printf("testcase %d : correct\n", i);
                else{
                        printf("testcase %d : incorrcet\n", i);
                        valid = 0;      // incorrect algorithm
                }
        }
}

void * thread_main(void *arg){
        int *pWorkStatus = (int*) arg;

        printf("\n");
        test_union();

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
        while(time_taken < 1){
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
                        printf("Good job!\n\nPassword is 4r5t6y\n");
        }
        else{
                printf("time took longer than 1 sec\n");
        }
        sleep(2);
}

int main(){
        // Check if algorithm is valid
        checktime();

        return 0;
}
