/*
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAX_V = 10000;
int V;
typedef pair<int, int> P; //first为最短距离, second为顶点编号
struct edge
{//终点，　容量，　费用，　反向边
	int to, cap, cost, rev;
};

vector<edge> G[MAX_V];//邻接表
int h[MAX_V];//顶点的势
int dist[MAX_V];//最短距离
int prevv[MAX_V], preve[MAX_V];//最短路中的前驱结点和对应的边

void add_edge(int from, int to, int cap, int cost)
{
	G[from].push_back((edge){to, cap, cost, G[to].size()});
	G[to].push_back((edge){from, 0, -cost, G[from].size() - 1});
}

//求s->t的流量为f的最小费用流
//若无流量为f的流，返回-1
int min_cost_flow(int s, int t, int f)
{
	int res = 0;
	fill(h, h + V, 0);//初始化h
	while(f > 0)
	{
		//用dijkstra更新h
		priority_queue<P, vector<P>, greater<P> > que;
		fill(dist, dist + V, INF);
		dist[s] = 0;
		que.push(P(0, s));
		while(!que.empty())
		{
			P p = que.top();
			que.pop();
			int v = p.second;
			if(dist[v] < p.first)
				continue;
			for(int i = 0; i < G[v].size(); ++i)
			{
				edge &e = G[v][i];
				if(e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to])
				{
					dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
					prevv[e.to] = v;
					preve[e.to] = i;
					que.push(P(dist[e.to], e.to));
				}
			}
		}
		if(dist[t] == INF)//不能再増广
		{
			return -1;
		}
		for(int v = 0; v < V; ++v)
		{
			h[v] += dist[v];
		}
		//沿s->t的最短路尽量増广
		int d = f;
		for(int v = t; v != s; v = prevv[v])
		{
			d = min(d, G[prevv[v]][preve[v]].cap);
		}
		f -= d;
		res += d * h[t];
		for(int v = t; v != s; v = prevv[v])
		{
			edge &e = G[prevv[v]][preve[v]];
			e.cap -= d;
			G[v][e.rev].cap += d;
		}
	}
	return res;
}


