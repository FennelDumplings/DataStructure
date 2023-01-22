/*
*/

int V; //顶点数
vector<int> G[V];//邻接表
int match[V];//所匹配顶点
bool used[V];//DFS访问标记

//向图中增加u->v的边
void add_edge(int u, int v)//所有边容量都为1
{
	G[u].push_back(v);
	G[v].push_back(u);
}

//DFS寻找增广路
bool dfs(int v)
{
	used[v] = true;
	for(int i = 0; i < G[v].size(); ++i)
	{
		int u = G[v][i], w = match[u];
		if(w < 0 || !used[w] && dfs(w))
		{
			match[v] = u;
			match[u] = v;
			return true;
		}
	}
	return false;
}

int bipartite_matching()
{
	int res = 0;
	memset(match, -1, sizeof(match));
	for(int v = 0; v < V; ++v)
	{
		if(match[v] < 0)
		{
			memset(used, 0, sizeof(used));
			if(dfs(v))
				res++;
		}
	}
	return res;
}