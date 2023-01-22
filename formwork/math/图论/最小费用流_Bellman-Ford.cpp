#include <vector>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 4;
const int M = 5;
int a[M] = {1, 2, 3, 1, 2};
int b[M] = {2, 3, 4, 3, 4};
int c[M] = {1, 1, 1, 2, 2};

const int V = N;
const int INF = 0x3f3f3f3f;
struct Edge
{
    int to,cap,cost,rev;
    Edge(int t,int c,int co,int r):to(t),cap(c),cost(co),rev(r) {}
};

vector<Edge> G[V];
int prevv[V],preve[V];
int dist[V];

void add_edge(int from,int to,int cap,int cost)
{
    G[from].push_back(Edge(to, cap, cost, G[to].size()));
    G[to].push_back(Edge(from, 0, -cost, G[from].size() - 1));
}

int min_cost_flow(int s, int t, int f)
{
    int res = 0;
    while(f > 0)
    {
        //Bellman-Ford求s-t最短路
        fill(dist, dist + V, INF);
        dist[s] = 0;
        bool update = true;
        while(update)
        {
            update = false;
            for(int v = 0; v < V; v++)
            {
                if(dist[v] == INF) continue;
                for(int i = 0; i < G[v].size(); i++)
                {
                    Edge &e = G[v][i];
                    if(e.cap>0 && dist[e.to] > dist[v] + e.cost)
                    {
                        dist[e.to] = dist[v] + e.cost;
                        prevv[e.to] = v;
                        preve[e.to] = i;
                        update = true;
                    }
                }
            }
        }
        if(dist[t] == INF)
        {
            //不能再増广
            return -1;
        }
        //沿着s-t的最短路尽量増广
        int d = f;
        for(int v = t; v != s; v = prevv[v])
        {
            d = min(d , G[prevv[v]][preve[v]].cap);
        }
        f -= d;
        res += d * dist[t];
        for(int v = t; v != s; v = prevv[v])
        {
            Edge &e = G[prevv[v]][preve[v]];
            e.cap -= d;
            G[v][e.rev].cap += d;
        }
    }
    return res;
}
