#include <cstdio>  
#include <cstring>  
#include <queue>  
#include <algorithm>  
#define MAXN 1010  
#define MAXM 100000  
using namespace std;  
struct Edge  
{  
    int from, to, next;  
};  
Edge edge[MAXM];  
int head[MAXN], edgenum;  
int vs[MAXN<<1];//第i次DFS访问节点的编号  
int depth[MAXN<<1];//第i次DFS访问节点的深度  
int id[MAXN];//id[i] 记录在vs数组里面 i节点第一次出现的下标  
int dfs_clock;//时间戳  
int N, M;//点数 边数  
int dp[MAXN<<1][20];//dp[i][j]存储depth数组  以下标i开始的，长度为2^j的区间里 最小值所对应的下标  
void init()  
{  
    edgenum = 0;  
    memset(head, -1, sizeof(head));  
}  
void addEdge(int u, int v)  
{  
    Edge E = {u, v, head[u]};  
    edge[edgenum] = E;  
    head[u] = edgenum++;  
}  
void getMap()  
{  
    int a, b;  
    while(M--)  
        scanf("%d%d", &a, &b),  
        addEdge(a, b), addEdge(b, a);  
}  
void DFS(int u, int fa, int d)//当前遍历点以及它的父节点  遍历点深度  
{  
    id[u] = dfs_clock;  
    vs[dfs_clock] = u;  
    depth[dfs_clock++] = d;  
    for(int i = head[u]; i != -1; i = edge[i].next)  
    {  
        int v = edge[i].to;  
        if(v == fa) continue;  
        DFS(v, u, d+1);  
        vs[dfs_clock] = u;//类似 回溯  
        depth[dfs_clock++] = d;  
    }  
}  
void find_depth()  
{  
    dfs_clock = 1;  
    memset(vs, 0, sizeof(vs));  
    memset(id, 0, sizeof(id));  
    memset(depth, 0, sizeof(depth));  
    DFS(1, -1, 0);//遍历  
}  
void input()  
{  
    printf("下标:  ");  
    for(int i = 1; i < dfs_clock; i++)  
        printf("%d  ", i);  
    printf("\n");  
    printf("vs:    ");  
    for(int i = 1; i < dfs_clock; i++)  
        printf("%d  ", vs[i]);  
    printf("\n");  
    printf("depth: ");  
    for(int i = 1; i < dfs_clock; i++)  
        printf("%d  ", depth[i]);  
    printf("\n");  
    printf("下标:  ");  
    for(int i = 1; i <= N; i++)  
        printf("%d  ", i);  
    printf("\n");  
    printf("id:    ");  
    for(int i = 1; i <= N; i++)  
        printf("%d  ", id[i]);  
    printf("\n");  
}  
int main()  
{  
    while(scanf("%d%d", &N, &M) != EOF)  
    {  
        init();  
        getMap();  
        find_depth();//DFS遍历整个树 求出所需要的信息  
        input();//输出查找信息  
    }  
    return 0;  
}  