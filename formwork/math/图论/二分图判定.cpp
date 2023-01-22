/*
n顶点的图，　顶点染色，相邻不同，能否最多两中颜色
无重边或自环
*/

#include <vector>
#include <iostream>
using namespace std;

const int n = 4;
vector<int> G[n];
int color[n];//定点颜色信息, 1或-1

bool dfs(int v, int c)
{
	color[v] = c;//定点v染色成c
	for(int i = 0; i < G[v].size(); ++i)
	{
		if(color[G[v][i]] == c)//相邻点同色
			return false;
		if(color[G[v][i]] == 0 && !dfs(G[v][i], -c))//相邻点未被染色
			return false;
	}
	return true;
}

int main(int argc, char const *argv[])
{
	G[0].push_back(1);
	G[0].push_back(3);
	G[1].push_back(0);
	G[1].push_back(2);
	G[2].push_back(1);
	G[2].push_back(3);
	G[3].push_back(2);
	G[3].push_back(0);
	for(int i = 0; i < n; ++i)
	{
		if(color[i] == 0)
		{
			if(!dfs(i, 1)) 
			{
				cout << "no" << endl;
				return 0;
			}
		}
	}
	cout << "Yes" << endl;
	return 0;
}