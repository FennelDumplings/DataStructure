
#include <vector>
#include <stack>
#include <iostream>
#include <fstream>

using namespace std;

void tarjan(const vector<vector<int>>& g, int x, vector<int>& dfn, int& id,
            stack<int>& st, vector<bool>& in_st, vector<int>& low, vector<vector<int>>& scc)
{
    dfn[x] = low[x] = ++id;
    st.push(x),
    in_st[x] = true;
    for(int y: g[x])
    {
        if(dfn[y] == -1)
        {
            tarjan(g, y, dfn, id, st, in_st, low, scc);
            low[x] = min(low[x], low[y]);
        }
        else if(in_st[y])
        {
            low[x] = min(low[x], dfn[y]);
        }
    }
    if(dfn[x] == low[x])
    {
        scc.push_back({});
        int y;
        do{
            y = st.top();
            st.pop();
            scc.back().push_back(y);
            in_st[y] = false;
        }
        while(y != x);
    }
}

vector<vector<int>> get_scc(const vector<vector<int>>& g)
{
    int N = g.size() - 1;
    vector<int> dfn(N + 1, -1);
    vector<int> low(N + 1, N + 1);
    int id = 0;
    stack<int> st;
    vector<bool> in_st(N + 1, false);
    vector<vector<int>> scc;
    for(int i = 1; i <= N; ++i)
    {
        if(dfn[i] == -1)
            tarjan(g, i, dfn, id, st, in_st, low, scc);
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
