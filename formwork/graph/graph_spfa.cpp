#include <vector>
#include <queue>
#include <list>

using namespace std;

vector<int> spfa(vector<vector<vector<int> > >& g, int start, int N)
{
    vector<int> d(N + 1, -1);
    d[start] = 0;
    queue<int, list<int> > q;
    q.push(start);

    int n = 0; // 记录松弛次数
    while(!q.empty())
    {
        int cur = q.front();
        q.pop();
        for(vector<int> &son: g[cur])
        {
            if(d[son[0]] == -1 || d[son[0]] > d[cur] + son[1])
            {
                // 当最短距离发生变化且不在队列中时，将该节点加入队列
                ++n;
                // 若 n >= N 则有负环
                d[son[0]] = d[cur] + son[1];
                q.push(son[0]);
            }
        }
    }
    return d;
}
