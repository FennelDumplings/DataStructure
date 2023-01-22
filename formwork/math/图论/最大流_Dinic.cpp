
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int INF = 1 << 30;
const int V = 10;//顶点数
//表示边的结构体
struct edge{int to, cap, rev;};//终点，容量，反向边

vector<edge> G[V];//临接表
//bool used[V];//DFS访问标记
int level[V];//顶点到源距离编号
int iter[V];//当前狐

void add_edge(int from, int to, int cap)//增加一条s到t的容量为cap的边
{
	G[from].push_back((edge){to, cap, G[to].size()});
	G[to].push_back((edge){from, 0, G[from].size() - 1});
}

//BFS
void bfs(int s)
{
	memset(level, -1, sizeof(level));
	queue<int> que;
	level[s] = 0;
	que.push(s);
	while(!que.empty())
	{
		int v = que.front();
		que.pop();
		for(int i = 0; i < G[v].size(); ++i)
		{
			edge &e = G[v][i];
			if(e.cap > 0 && level[e.to] < 0)
			{
				level[e.to] = level[v] + 1;
				que.push(e.to);
			}
		}
	}
}

//DFS寻找增广路
int dfs(int v, int t, int f)
{
	if(v == t)
		return f;
	//used[v] = true;
	//for(int i = 0; i < G[v].size(); ++i)
	for(int &i = iter[v]; i < G[v].size(); ++i)
	{
		edge &e = G[v][i];
		//if(used[e.to] && e.cap > 0)
		if(e.cap > 0 && level[v] < level[e.to])
		{
			int d = dfs(e.to, t, min(f, e.cap));
			if(d > 0)
			{
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}

//求s到t的最大流
int max_flow(int s, int t)
{
	int flow = 0;
	for(;;)
	{
		bfs(s);
		if(level[t] < 0)
			return flow;
		//memset(uesd, 0, sizeof(used));
		memset(iter, 0, sizeof(iter));
		//int f = dfs(s, t, INF);
		int f;
		//if(f == 0)
			//return flow;
		//flow += f;
		while((f = dfs(s, t, INF)) > 0)
		{
			flow += f;
		}
	}
}

