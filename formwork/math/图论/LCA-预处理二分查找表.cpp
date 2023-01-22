#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAX_V = 10005;
const int MAX_LOG_V = 15;
int V;
vector<int> G[MAX_V];
int root;//根节点编号
int parent[MAX_LOG_V][MAX_V];//向上走2^k步所到点，超过N为-1
int depth[MAX_V];//节点深度

void add_edge(int from, int to)
{
	G[from].push_back(to);
}

void dfs(int v, int p, int d)
{
	parent[0][v] = p;
	depth[v] = d;
	for(int i = 0; i < G[v].size(); ++i)
	{
		if(G[v][i] != p)
			dfs(G[v][i], v, d + 1);
	}
}

void init()
{
	//预处理parent[0]和depth
	dfs(root, -1, 0);
	for(int k = 0; k < MAX_LOG_V; ++k)
	{
		for(int v = 0; v < V; ++v)
		{
			if(parent[k][v] < 0)
				parent[k + 1][v] = -1;
			else
				parent[k + 1][v] = parent[k][parent[k][v]];
		}
	}
}

int lca(int u, int v)
{
	//u，v向上走到同一深度
	if(depth[u] > depth[v])
		swap(u, v);
	for(int k = 0; k < MAX_LOG_V; ++k)
	{
		if((depth[v] - depth[u]) >> k & 1)
		{
			v = parent[k][v];
		}
	}
	if(u == v)
		return u;

	for(int k = MAX_LOG_V; k >= 0; --k)
	{
		if(parent[k][v] != parent[k][u])
		{
			u = parent[k][u];
			v = parent[k][v];
		}
	}
	return parent[0][u];
}