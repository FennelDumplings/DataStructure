#include <vector>

using namespace std;

vector<int> bellman_ford(vector<vector<vector<int> > >& g, int start, int N)
{
    vector<int> d(N + 1, -1);
    d[start] = 0;

    for(int cnt = 1; cnt <= N - 1; ++cnt)
    {
        for(int u = 1; u <= N; ++u)
        {
            if(d[u] == -1) continue;
            for(vector<int> &son: g[u])
            {
                int v = son[0], w = son[1];
                if(d[u] + w < d[v] || d[v] == -1)
                    d[v] = d[u] + w;
            }
        }
    }
    return d;
}

