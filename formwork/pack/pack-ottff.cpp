/*
 * ottff 视频
 * 01 背包
 * 完全背包
 * 多重背包
 */

#include <cstring>
#include <algorithm>

using namespace std;

const int MV = 5005;
const int M = 5005;
int dp[MV];
int V;

void init()
{
    memset(dp, 0, sizeof(dp));
    // memset(dp, 1, sizeof(dp));
    // dp[0] = 0;
}

int v[M], w[M];

void zero_one_pack(int vi, int wi)
{
    for(int i = V; i >= vi; --i)
    {
        // if(dp[i - vi] != -1)
        dp[i] = max(dp[i], dp[i - vi] + wi);
    }
}

void complete_pack(int vi, int wi)
{
    for(int i = vi; i <= V; ++i)
        dp[i] = max(dp[i], dp[i - vi] + wi);
}

void multiple_pack(int vi, int wi, int ci)
{
    if(V / vi <= ci)
    {
        complete_pack(vi, wi);
        return;
    }
    for(int i = 1; i <= ci; i <<= 1)
    {
        ci -= i;
        zero_one_pack(vi * i, wi * i);
    }
    zero_one_pack(vi * ci, wi * ci);
}

int solve(int n)
{
    for(int i = 0; i < n; ++i)
        zero_one_pack(v[i], w[i]);
    return dp[V];
}
