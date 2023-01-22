#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Cmp
{
    bool operator() (const vector<int>& item1, const vector<int>& item2)
    {
        return item1[1] > item2[1]; // 最小堆
    }
};

// 数组实现
vector<int> dijkstra_array(vector<vector<vector<int> > >& g, int start, int N)
{
    // 输入带权邻接表
    vector<int> d(N + 1, -1);
    d[start] = 0;
    vector<bool> visited(N + 1, false);
    visited[start] = true;

    // 先对起点进行更新
    for(vector<int> son: g[start])
        d[son[0]] = son[1];

    for(int cnt = 1; cnt <= N - 1; ++cnt)
    {
        int min_val = INT_MAX / 2, min_idx = -1;
        for(int i = 1; i <= N; ++i)
        {
            if(d[i] != -1 && !visited[i] && d[i] < min_val)
            {
                min_idx = i;
                min_val = d[i];
            }
        }
        visited[min_idx] = true;
        for(vector<int> son: g[min_idx])
        {
            if(d[son[0]] != -1)
                d[son[0]] = min(d[son[0]], min_val + son[1]);
            else
                d[son[0]] = min_val + son[1];
        }
    }
    return d;
}

// 堆实现
vector<int> dijkstra_heap(vector<vector<vector<int> > >& g, int start, int N)
{
    // 输入带权邻接表
    vector<int> d(N + 1, INT_MAX / 2);
    d[start] = 0;
    priority_queue<vector<int>, vector<vector<int> >, Cmp> pq; // 队列元素 (节点编号，到 start 的距离)
    pq.push({start, 0});
    while(!pq.empty())
    {
        vector<int> cur = pq.top();
        pq.pop();
        if(d[cur[0]] < cur[1]) continue;
        for(vector<int> son: g[cur[0]])
        {
            if(d[son[0]] <= d[cur[0]] + son[1]) continue;
            d[son[0]] = d[cur[0]] + son[1];
            pq.push({son[0], d[son[0]]});
        }
    }
    return d;
}

