
#include <vector>
#include <stack>
#include <iostream>
#include <fstream>

using namespace std;

void dfs1(const vector<vector<int>>& g, int node, vector<int>& backtrack_seq, vector<bool>& visited, vector<vector<int>>& gt)
{
    for(int son: g[node])
    {
        gt[son].push_back(node);
        if(visited[son])
            continue;
        visited[son] = true;
        dfs1(g, son, backtrack_seq, visited, gt);
    }
    backtrack_seq.push_back(node);
}

void dfs2(const vector<vector<int>>& gt, int node, vector<bool>& visited, vector<vector<int>>& scc)
{
    for(int son: gt[node])
    {
        if(visited[son]) continue;
        scc.back().push_back(son);
        visited[son] = true;
        dfs2(gt, son, visited, scc);
    }
}

vector<vector<int>> get_scc(const vector<vector<int>>& g)
{
    int N = g.size() - 1;
    vector<bool> visited(N + 1, false); // 标记 dfs1 已访问
    vector<int> backtrack_seq; // 按回溯顺序插入
    vector<vector<int>> gt(N + 1); // 反图
    for(int i = 1; i <= N; ++i)
    {
        if(visited[i]) continue;
        visited[i] = true;
        dfs1(g, i, backtrack_seq, visited, gt);
    }
    visited.assign(N + 1, false); // 标记 dfs2 已访问
    vector<vector<int>> scc;
    for(auto it = backtrack_seq.rbegin(); it != backtrack_seq.rend(); ++it)
    {
        int node = *it;
        if(visited[node]) continue;
        scc.push_back({});
        scc.back().push_back(node);
        visited[node] = true;
        dfs2(gt, node, visited, scc);
    }
    return scc;
}


void test()
{
    int N, M;
    fstream fin("scc.test");
    fin >> N >> M;
    vector<vector<int>> g(N + 1);
    for(int i = 1; i <= M; ++i)
    {
        int u, v;
        fin >> u >> v;
        g[u].push_back(v);
    }
    vector<vector<int>> scc = get_scc(g);
    for(vector<int> &item: scc)
    {
        for(int i: item)
            cout << i << " ";
        cout << endl;
    }
}

int main()
{
    test();
}
