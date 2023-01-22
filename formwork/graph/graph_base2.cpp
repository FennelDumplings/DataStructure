#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

// 邻接表
const int MV = 100000;
const int INF = 0x3f3f3f3f;
int n, m;
vector<int> g[MV];
vector<vector<int> > gg; // leetcode 的写法

using PII = pair<int, int>; // 要存权重信息的写法
vector<PII> g2[MV];

void init()
{
    for(int i = 0; i < MV; i++)
    {
        g[i].clear();
    }
    gg.assign(n, vector<int>()); // leetcode 的写法
}

void add_edge(int u, int v)
{
    g[u].push_back(v);
    // g[v].push_back(u);
}

void add_edge(int u, int v, int w)
{
    g2[u].emplace_back(v, w);
}

vector<int> aj(int u)
{
    return g[u];
}

void tran(int u)
{
    for(int i: g[u])
    {
        cout << i << " ";
    }
    for(PII p:g2[u])
    {
        cout << p.first << p.second << endl;
    }
}
