

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 10000;

struct edge
{
	int to, cost;
};
typedef pair<int, int> P;//优先级队列所存内容

const int N = 10;
vector<edge> G[N];//图结构, 临接表
int dist[N];//最短

void dijkstra(int s)
{
	priority_queue<P, vector<P>, greater<P> > que;
	fill(dist, dist + N, INF);
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
			edge e = G[v][i];
			if(dist[e.to] > d[v] + e.cost)
			{
				dist[e.to] = d[v] + e.cost;
				que.push(P(dist[e.to], e.to));
			}
		}
	}
}