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
#define PASS "f7a89a"

using namespace std;

extern vector<long long> prefix_Sum(vector<int> arr, int num_query, vector <pair<int,int>> query);
extern void dfs(int v);
extern void bfs(int v);

extern vector<int> g_dfs_result;
extern vector<int> g_bfs_result;
extern int mat[MAX_VALUE][MAX_VALUE];
extern int N, V;        // N == num of nodes, V == starting node

int dfs_valid = 0; // false
int bfs_valid = 0; // false

vector<int> g_dfs_answer;
vector<int> g_bfs_answer;


// testcase #1
void testcase1(){
        N = 6;
        V = 1;  
        vector<pair <int, int>> E; // edges 
        E.push_back(make_pair(1, 2));
        E.push_back(make_pair(1, 6));
        E.push_back(make_pair(2, 3));
        E.push_back(make_pair(2, 5));
        E.push_back(make_pair(2, 6));
        E.push_back(make_pair(3, 4));
        E.push_back(make_pair(3, 5));
        
        

        for(int i = 0; i < E.size() ; i++){
                int p1 = E[i].first;
                int p2 = E[i].second;
                mat[p1][p2] = mat[p2][p1] = 1;
        }

        g_dfs_answer.push_back(1);
        g_dfs_answer.push_back(2);
        g_dfs_answer.push_back(3);
        g_dfs_answer.push_back(4);
        g_dfs_answer.push_back(5);
        g_dfs_answer.push_back(6);
        
        
        g_bfs_answer.push_back(1);
        g_bfs_answer.push_back(2);
        g_bfs_answer.push_back(6);
        g_bfs_answer.push_back(3);
        g_bfs_answer.push_back(5);
        g_bfs_answer.push_back(4);
}

void test_dfs(){

        dfs(V);
        int result_size = g_dfs_result.size();
        
        dfs_valid = 1;
        for(int i = 0; i < result_size; i++){
                if(g_dfs_result[i] != g_dfs_answer[i]) dfs_valid = 0;
                printf("%d ",g_dfs_result[i]);
        }

}

void test_bfs(){
        
        bfs(V);
        int result_size = g_bfs_result.size();
        
        bfs_valid = 1;
        for(int i = 0; i < result_size; i++){
                if(g_dfs_result[i] != g_dfs_answer[i]) dfs_valid = 0;
                printf("%d ",g_bfs_result[i]);
        }
}


void * thread_main(void *arg){
        int *pWorkStatus = (int*) arg;

        testcase1();

        printf("dfs : ");
        test_dfs();

        printf("\n");

        printf("bfs : ");
        test_bfs();
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
         
                if(dfs_valid == 1) printf("dfs() correct\n");
                else printf("dfs() incorret\n");

                if(bfs_valid == 1) printf("bfs() correct\n");
                else printf("bfs() incorrect\n");
                
                if(dfs_valid && bfs_valid) 
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
