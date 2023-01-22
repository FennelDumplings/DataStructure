#include <vector>

using namespace std;

vector<int> floyd(vector<vector<vector<int> > >& g, int start, int N)
{
    vector<vector<int> > adj_matrix(N + 1, vector<int>(N + 1, -1));
    for(int i = 1; i <= N; ++i)
        adj_matrix[i][i] = 0;
    for(int u = 1; u <= N; ++u)
        for(vector<int> son: g[u])
            adj_matrix[u][son[0]] = son[1];

    for(int k = 1; k <= N; ++k)
        for(int i = 1; i <= N; ++i)
            for(int j = 1; j <= N; ++j)
                if(adj_matrix[i][k] != -1 && adj_matrix[k][j] != -1)
                {
                    if(adj_matrix[i][j] != -1)
                        adj_matrix[i][j] = min(adj_matrix[i][j], adj_matrix[i][k] + adj_matrix[k][j]);
                    else
                        adj_matrix[i][j] = adj_matrix[i][k] + adj_matrix[k][j];
                }

    vector<int> d(N + 1, -1);
    for(int i = 1; i <= N; ++i)
        d[i] = adj_matrix[start][i];

    return d;
}

