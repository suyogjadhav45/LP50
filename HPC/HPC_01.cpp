#include<iostream>
#include<vector>
#include<queue>
#include<omp.h>
using namespace std;

struct Graph{
    int V;
    vector<vector<int>>adj;
    Graph(int V){
        this->V=V;
        adj.resize(V);
    }
    void addEdge(int u,int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void BFS(int start){
        vector<bool>visited(V,false);
        queue<int>q;
        visited[start]=true;
        q.push(start);
        while(!q.empty()){
            int u=q.front();
            q.pop();
            cout<<u<<" ";
            #pragma omp parallel for
            for(int i=0;i<adj[u].size();i++){
                int v=adj[u][i];
                if(!visited[v]){
                    visited[v]=true;
                    q.push(v);
                }
            }
        }
        cout<<endl;
    }
    


void DFS(int start){
    vector<bool>visited(V,false);
    #pragma omp parallel
    {
        #pragma omp single nowait
        DFSutil(start,visited);
    }
    cout<<endl;
}
void DFSutil(int u,vector<bool>& visited){
    visited[u]=true;
    cout<<u<<" ";
    #pragma omp parallel for
    for(int i=0;i<adj[u].size();i++){
        int v=adj[u][i];
        if(!visited[v]){
            DFSutil(v,visited);
        }
    }
}
};
int main(){
    int v;
    cout<<"Enter number of vertices: ";
    cin>>v;
    Graph g(v);

    int Edgecount;
    cout<<"Enter number of edges: ";
    cin>>Edgecount;

    cout<<"Enter edges(in format 'source destination'): \n";
    for(int i=0;i<Edgecount;i++){
        int u, v;
        cin>>u>>v;
        g.addEdge(u,v);
    }
    cout << "BFS traversal starting from node 0: ";
    g.BFS(0);

    cout << "DFS traversal starting from node 0: ";
    g.DFS(0);

    return 0;
}

/*
Enter number of vertices: 7
Enter number of edges: 6
Enter edges(in format 'source destination'): 
0 1
0 2
1 3
1 4
2 5
2 6
BFS traversal starting from node 0: 0 1 2 3 4 5 6 
DFS traversal starting from node 0: 0 1 3 4 2 5 6
*/ 
