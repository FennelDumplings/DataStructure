#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

// 邻接矩阵
const int MV = 1000;
const int INF = 0x3f3f3f3f;
int n, m; // 点数，边数
int g[MV][MV];

void init()
{
    memset(g, 0, sizeof(g));
    // memset(g, INF, sizeof(g));
}

void add_edge(int u, int v)
{
    g[u][v] = 1;
    // g[u][v]++ 有重边的情况
}

//
void add_edge(int u, int v, int w)
{
    g[u][v] = w; // g[u][v] = min(g[u][v], w)
    // g[v][u] = w; 无向图的情况
}

bool is_edge(int u, int v)
{
    return g[u][v];
}

vector<int> aj(int u) // 相邻的边
{
    vector<int> ans;
    for(int i = 0; i < n; i++)
        if(is_edge(u, i))
            ans.push_back(i);
    return ans;
}
