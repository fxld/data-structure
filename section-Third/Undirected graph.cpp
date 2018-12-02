//
//  main.cpp
//  图的最短路程（相邻矩阵）
//
//  Created by dream on 2018/11/22.
//  Copyright © 2018 dream. All rights reserved.
//

#include <iostream>
#include <deque>

using namespace std;

#define Unvisited 0;
#define Visited 1;
#define Infiniy 65535;

class Edge{
public:
    int from,to,weight;
    Edge(){
        from=-1;
        to=-1;
        weight=0;
    }
    Edge(int f,int t,int w){
        from=f;to=t;weight=w;
    }
};
class Gragh{
public:
    int numVertex;
    int numEdge;
    int *Mark;
    int *Indegree;
    Gragh(int numVert){
        numVertex=numVert;
        numEdge=0;
        Indegree=new int [numVert+1];
        Mark=new int [numVert+1];
        for (int i=0; i<numVertex; i++)
        {
            Mark[i]=Unvisited;
            Indegree[i]=0;
        }
    }
    int VeticesNum()
    {
        return numVertex;
    }
    bool IsEdge(Edge oneEdge)
    {
        if(oneEdge.weight>0) {
            return true;
        }
        else
        {
            return false;
        }
    }
};
class Graghm:public Gragh{
private:
    int **matrix;
    int **matrix2;
public:
    Graghm(int numVert):Gragh(numVert){
        int i,j;
        matrix=(int **)new int*[numVertex];
        matrix2=(int **)new int*[numVertex];
        for (i=0; i<numVertex; i++)
        {
            matrix[i]=new int [numVertex];
            matrix2[i]=new int [numVertex];
        }
        for (i=0; i<numVertex; i++)
        {
            for(j=0; j<numVertex;j++)
            {
                matrix[i][j]=0;
                matrix2[i][j]=0;
            }
        }
    }
    void setEdge(int from,int to,int weight)  //此处讨论无向图
    {
        if (matrix[from][to]==0)
        {
            numEdge++;
            Indegree[to]++;
        }
        matrix[to][from]=weight;
        matrix[from][to]=weight;
    }
    void setMoney(int from,int to,int Money)
    {
        matrix2[to][from]=Money;
        matrix2[from][to]=Money;
    }
    int edgeWeight(int from,int to)
    {
        int temp;
        temp=matrix[from][to];
        return temp;
    }
    int edgemoney(int from,int to)
    {
        int temp;
        temp=matrix2[from][to];
        return temp;
    }
    int EdgeNum()
    {
        int count=0;
        for (int i=0; i<numVertex; i++)
        {
            for (int j=0; j<numVertex; j++)
            {
                if (matrix[i][j]!=0)
                {
                    count++;
                }
            }
        }
        return count;
    }
    int EdgeLeught(int from,int to)
    {
        return matrix[from][to];
    }
    Edge* FirstEdge(int from)
    {
        for (int i=0; i<numVertex; i++)
        {
            if (matrix[from][i]>0)
            {
                Edge *edge=new Edge(from,i,matrix[from][i]);
                return edge;
            }
        }
        return NULL;
    }
    Edge *NextEdge(int from,int to)
    {
        for (int i=to+1; i<numVertex; i++)
        {
            if (matrix[from][i]>0)
            {
                Edge *edge=new Edge();
                edge->from=from;
                edge->to=i;
                edge->weight=matrix[from][i];
                return edge;
            }
        }
        return NULL;
    }
};

void DFS_Graghm(Graghm &G,int s)
{
    Edge* p;
    p=G.FirstEdge(s);
    G.Mark[p->from]=Visited;
    cout<<p->from;
    for (; p!=NULL;p=G.NextEdge(s,p->to) ) {
        if (!G.Mark[p->to])
        {
            DFS_Graghm(G, p->to);
        }
    }
}

void BFS_Graghm(Graghm &G,int s)
{
    cout<<endl;
    int temp;
    for (int i=0; i<G.numVertex; i++) //引用可能会改变了mark数组的值
    {
        G.Mark[i]=Unvisited;
    }
    deque<int> Deque;
    Deque.push_front(s);
    cout<<s;
    G.Mark[s]=Visited;
    while (!Deque.empty())
    {
        temp=Deque.front();
        Deque.pop_front();
        for (Edge *p=G.FirstEdge(temp);p!=NULL ; p=G.NextEdge(temp,p->to))
        {
            if (!G.Mark[p->to]) {
            cout<<p->to;
            Deque.push_back(p->to);
            G.Mark[p->to]=Visited;
            }
        }
    }
    
}
void Dijkstra(Graghm &G,int s,int d)
{
    cout<<endl;
    for (int i=0; i<G.numVertex; i++) //因为前面的深度优先遍历会把mark数组改变了
    {
        G.Mark[i]=Unvisited;
    }
    int *path;
    path=new int [G.numVertex];
    int *cost;
    cost=new int [G.numVertex];
    for (int i=0; i<G.numVertex; i++)
    {
        path[i]=G.edgeWeight(s,i);
        cost[i]=G.edgemoney(s,i);
    }
    G.Mark[s]=Visited;
    int temp=Infiniy;
    int temp2=s;
    for (int i=0; i<G.numVertex; i++)
    {
        temp=Infiniy;
        for (int j=0; j<G.numVertex; j++)
        {
            if (!G.Mark[j]&&path[j]<temp)
            {
                temp=path[j];
                temp2=j;
            }
        }
        if (temp2!=s)
        {
            G.Mark[temp2]=Visited;
        }
        else
            break;
        Edge *e;
        for (e=G.FirstEdge(temp2); e!=NULL; e=G.NextEdge(e->from, e->to))
        {
            if (e->weight+path[temp2]<path[e->to]&&!G.Mark[e->to])
            {
                path[e->to]=e->weight+path[temp2];
                cost[e->to]=cost[temp2]+G.edgemoney(temp2, e->to);
            }
            else if(e->weight+path[temp2]==path[e->to]&&(G.edgemoney(temp2, e->to)+cost[temp2])<cost[e->to])
            {
                cost[e->to]=G.edgemoney(temp2, e->to)+cost[temp2];
            }
        }
    }
    cout<<path[d]<<" ";
    cout<<cost[d];
}

int main(){
    int N,M,S,D;
    int city1,city2,weight;
    int money;
    cin>>N>>M>>S>>D;
    Graghm G(N);
    for (int i=0; i<M; i++)
    {
        cin>>city1>>city2>>weight>>money;
        G.setEdge(city1, city2, weight);
        G.setMoney(city1, city2, money);
    }
    DFS_Graghm(G, S);
    BFS_Graghm(G,S);
    topological_sort(G);
    Dijkstra(G,S,D);
    return 0;
}
