#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

// 链式前向星, 网络流一般这么写
const int MV = 1e5 + 5;
const int ME = 1e5 + 5; // 无向图的话，边数要乘2
const int INF = 0x3f3f3f3f;
int n, m;

struct Edge
{
    int u, v, w;
    int nxt; // 指向下一个位置
    Edge(int u = 0, int v = 0, int w = 0, int nxt=0)
        :u(u),v(v),w(w),nxt(nxt){}
}edge[ME*2]; // 无向图 ME 一定要乘 2

int head[MV]; // head 指针
int nne; // 当前已经有的边数

void init()
{
    memset(head, -1, sizeof(head)); // -1 在计算机里是补码，全都是1, 少数可以用 memset 刷的 int 值
    nne = 0;
}

void add_edge(int u, int v, int w)
{
    edge[nne] = Edge(u, v, w, head[u]);
    head[u] = nne;
    nne++; // 到下一个位置
    // 如果是无向图，插量词, 此时 e -> e^1 (e的反向边是 e^1) 这是一个好特性
}

// 不适合快速找点
void tran(int u)
{
    for(int e = head[u]; e!=-1; e=edge[e].nxt)
    {
        int v = edge[e].v, w = edge[e].w;
        cout << v << w;
    }
}


// 在 vector 里面存的时候，要写反向边的写法
struct Edge_2
{
    int v, w, re;
    Edge_2(int v=0, int w=0, int re=0)
        :v(v),w(w),re(re){}
};
vector<Edge_2> g[MV];
void add_edge_2(int u, int v, int w)
{
    g[u].emplace_back(v, w, g[v].size());
    g[v].emplace_back(u, w, g[u].size()-1);
}
