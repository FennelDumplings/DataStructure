#include <iostream>
#include <vector>
using namespace std;

const int MAX_V = 10005;
vector<int> G[MAX_V];
int root;//根节点编号
int parent[MAX_V];//父节点, 根节点父为-1
int depth[MAX_V];//节点深度

void add_edge(int from, int to)
{
	G[from].push_back(to);
}

void dfs(int v, int p, int d)
{
	parent[v] = p;
	depth[v] = d;
	for(int i = 0; i < G[v].size(); ++i)
	{
		if(G[v][i] != p)
			dfs(G[v][i], v, d + 1);
	}
}

void init()
{
	dfs(root, -1, 0);
}

int lca(int u, int v)
{
	while(depth[u] > depth[v]) u = parent[u];
	while(depth[u] < depth[v]) v = parent[v];
	while(u != v)
	{
		u = parent[u];
		v = parent[v];
	}
	return u;
}