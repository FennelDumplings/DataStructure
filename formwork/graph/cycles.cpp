
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

void dfs(const vector<vector<int>>& g, int node, int prev, vector<int>& path, vector<bool>& visited, vector<vector<int>>& result)
{
    for(int son: g[node])
    {
        if(son == path[0] && prev != son)
            result.push_back(path);
        if(visited[son]) continue;
        visited[son] = true;
        path.push_back(son);
        dfs(g, son, node, path, visited, result);
        path.pop_back();
        visited[son] = false;
    }
}

vector<vector<int>> get_cycles(const vector<vector<int>>& g)
{
    int N = g.size() - 1;
    vector<bool> visited(N + 1, false);
    vector<vector<int>> result;
    for(int i = 1; i <= N; ++i)
    {
        vector<int> path(1, i);
        visited[i] = true;
        dfs(g, i, -1, path, visited, result);
    }
    return result;
}

void show(const vector<vector<int>>& cycles)
{
    for(const vector<int>& cycle: cycles)
    {
        for(int i: cycle) cout << i << " ";
        cout << endl;
    }
}

void test()
{
    int N, M;
    fstream fin("cycles.test");
    fin >> N >> M;
    vector<vector<int>> g(N + 1);
    for(int i = 1; i <= M; ++i)
    {
        int u, v;
        fin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<vector<int>> cycles = get_cycles(g);
    show(cycles);
}

int main()
{
    test();
}

