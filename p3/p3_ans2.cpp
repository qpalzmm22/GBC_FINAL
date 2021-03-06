#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX = 1000;

int node[MAX];
int N;
int M;
int V;  // start node

vector< vector<int> > edge;

//Visited Vector
vector<bool> dfs_V;
vector<bool> bfs_V;


//dfs
void dfs(int curNode){
        dfs_V[curNode] = true;
        printf("%d ", curNode);
        sort(edge[curNode].begin(),edge[curNode].end());
        for(int i = 0; i < edge[curNode].size(); i++){
                int nextNode = edge[curNode][i];
                if(dfs_V[nextNode]) continue;
                dfs(nextNode);
        }
}



//bfs
void bfs(){
        queue<int> q;

        q.push(V);
        bfs_V[V]= true;
        while(!q.empty()){
                int curNode = q.front();  
                q.pop();
                printf("%d ", curNode);
                for(int i = 0; i < edge[curNode].size(); i++){
                        int nextNode = edge[curNode][i];
                        if(bfs_V[nextNode]) continue;
                        bfs_V[nextNode] = true;
                        q.push(nextNode);
                }
        }
}


int main(){
        int from, to;
        scanf("%d %d %d", &N, &M, &V);

        dfs_V.resize(N + 1);
        bfs_V.resize(N + 1);
        edge.resize(N + 1);
        for(int i = 0; i < M; i++){
                scanf("%d %d", &from, &to);
                edge[from].push_back(to);
                edge[to].push_back(from);
        }

        //dfs 
        dfs(V);
        puts("");

        //bfs
        bfs();


        return 0;
}
