
const int INF;
const int V, E;
struct edge
{
	int from, to, cost;
}

edge es[E];
int d[v];

bool find_neg_loop()
{
	memset(d, 0, sizeof(d));
	for(int i = 0; i < v; ++i)
	{
		for(int j = 0; j < E; ++j)
		{
			edge e = es[j];
			if(d[e.to] > d[e.from] + e.cost)
			{
				d[e.to] = d[e.from] + e.cost;
				if(i == V - 1)
					return true;
			}
		}
	}
	return false;
}

void shortest_path(int s)
{
	for(int i = 0; i < V; ++i)
	{
		d[i] = INF;
	}
	d[s] = 0;
	while(true)
	{
		bool update = false;
		for(int i = 0; i < E; ++i)
		{
			edge e = es[i];
			if(d[e.from] != INF && d[e.to] > d[e.from] + e.cost)
			{
				d[e.to] = d[e.from] + e.cost;
				update = true;
			}
		}
		if(!update)
			break;
	}
	//可报告负循环
	
}