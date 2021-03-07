#pragma once

#include <stdio.h>
#include <vector>
#include <time.h>
#include <unistd.h>
#include <utility>
#include <bits/stdc++.h>
#include <pthread.h>

#define MAX     10000000
#define PASS    "ws9f87"

using namespace std;

extern vector<long long> prefix_Sum(vector<int> arr, int num_query, vector <pair<int,int>> query);
void test_prefix_sum();

int valid = 0; // false


void * thread_main(void *arg){
        int *pWorkStatus = (int*) arg;

        test_prefix_sum();
        *pWorkStatus = 1;
        return NULL;
}

void test_prefix_sum(){
        vector<int> test_array;
        
        // { 0, 1, 2, 3, 4, 5, 6, 7, 8..., MAX-1}
        for(int i = 0; i < MAX; i++){ 
                test_array.push_back(i);
        }
        vector <pair <int, int>> test_query;
        vector<long long> answer_array;
        
        test_query.push_back(make_pair(3, 10));
        answer_array.push_back(52);
        test_query.push_back(make_pair(1, 1000000));
        answer_array.push_back(500000500000);
        test_query.push_back(make_pair(2234313, 5000444));
        answer_array.push_back(10006146424962);

        for(int i = 0; i < 10000; i++){
                test_query.push_back(make_pair(1,9999998));
                answer_array.push_back(49999985000001);
        }


        // sum of [0 + 1] to [arr.size() - 1]

        vector<long long> result_array = prefix_Sum(test_array, test_query.size(), test_query);

        // check if the function is valid
        for(int i = 0; i < test_query.size(); i++){
                long long result = result_array[i];
                long long answer = answer_array[i];
                if(result == answer)
                        valid = 1;
                else{
                        printf("result : %lld, answer: %lld\n",result, answer); 
                        valid = 0;
                        break;
                }
        }
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
                printf("The algorithm took %lf seconds\n", time_taken);
                if(valid == 1){
                        printf("Good Job!\nPassword : %s\n", PASS);
                }
        }
        else{
                printf("time took longer than 1 sec\n");
        }
        sleep(2);
}

int main(){

        vector<int> arr = { 4, 1, 0, 7, 9, 3, 2, 6, 5, 8 };
        int num_query = 1;
        vector <pair <int, int>> query;
        // sub sum of [2] ~ [3]
        query.push_back(make_pair(2,3));

        vector<long long> result_arr = prefix_Sum(arr, num_query, query);

        for(int i = 0; i < num_query; i++){
                printf("%lld\n", result_arr[i]);
        }
        
        // Check if algorithm is valid
        checktime();

        return 0;
}
