#include <vector>
#include <queue>
#include <stack>
#include <cmath>

using namespace std;

vector<vector<int> > g; // 邻接表
int n;

void init(int nn)
{
    n = nn;
    g.assign(n, vector<int>());
}

void add_edge(int u, int v)
{
    g[u].push_back(v);
    //g[v].push_back(u); // 无向图
}

int bfs(int st, int ed)
{
    vector<int> d(n, -1);
    vector<int> pre(n, -1); // 若需要保存路径
    queue<int> q;
    d[st] = 0;
    q.push(st);
    int f = 0;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int v: g[u])
        {
            if(d[v] != -1) continue;
            d[v] = d[u] + 1;
            pre[v] = u;
            if(v == ed)
            {
                f = 1;
                break;
            }
            q.push(v);
        }
    }
    if(!f) return f;
    stack<int> sta;
    // 输出最短路
    int u = ed;
    while(u != -1)
    {
        sta.push(u);
        u = pre[u];
    }
    while(!sta.empty())
    {
        sta.pop();
    }
    return -1;
}

// 双向 BFS
int bibfs(int st, int ed)
{
    vector<int> d(n, 0); // 0 代表未访问, +-号代表颜色(起点色，终点色)
    queue<int> q;
    d[st] = 1;
    d[ed] = -1;
    q.push(st);
    q.push(ed);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int v: g[u])
        {
            if(d[v] == 0) // 未访问过
            {
                d[v] = (d[u] > 0 ? d[u] + 1 : d[u] - 1);
                q.push(v);
            }
            else
            {
                if((d[u] ^ d[v]) < 0) // 异号，颜色不同
                    return abs(d[u]) + abs(d[v]);
            }
        }
    }
    return -1;
}
