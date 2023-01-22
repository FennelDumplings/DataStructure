// 01背包
// 完全背包
// 多重背包
// 混合背包
// 二维背包
// 分组背包
// 背包问题求方案数
// 背包问题返回最优方案
// 有依赖的背包问题(树形)

/********************************************************/

#include <vector>
#include <cstring>
#include <climits>
#include <iostream>

using namespace std;

// 1. 01背包
/*
 * dp[i][j] := 只看前 i 个物品, 总体积 j 下的最大价值
 * 答案 max dp[n][0~v]
 * 转移：
 * dp[i][j] = dp[i - 1][j]   不选 i
 *          = dp[i - 1][j - v[i]] + w[i]  选 i
 *          = max(以上两种情况的较大值)
 * 初始化：dp[0][0] = 0
 */

int pack01()
{
    int N = 1000;
    int V = 1000;
    vector<int> v(N, 0);
    vector<int> w(N, 0);
    vector<vector<int> > dp(N + 1, vector<int>(V + 1, 0));
    for(int i = 1; i <= N; ++i)
        for(int j = 0; j <= V; ++j)
        {
            dp[i][j] = dp[i - 1][j];
            if(j >= v[i - 1])
                dp[i][j] = max(dp[i][j], dp[i - 1][j - v[i - 1]] + w[i - 1]);
        }
    int result = 0;
    for(int j = 0; j <= V; ++j)
        result = max(result, dp[N][j]);
    return result;
}

// 优化1，dp[i] 只与 dp[i - 1] 有关
int pack01_optim()
{
    int N = 1000;
    int V = 1000;
    vector<int> v(N, 0);
    vector<int> w(N, 0);
    vector<int> dp(V + 1, 0);
    for(int i = 1; i <= N; ++i)
        for(int j = V; j >= v[i - 1]; --j)
            dp[j] = max(dp[j], dp[j - v[i - 1]] + w[i - 1]);
    int result = 0;
    // for(int j = 0; j <= V; ++j)
    //     result = max(result, dp[j]);
    result = dp[V]; // 整个 dp 初始化为 0 的时候，dp[V] 就是答案
    return result;
}


// 2.完全背包
/*
 * dp[i] := 总体积 i 下的最大价值
 * 答案 max dp[0~v]
 * 转移：
 * dp[i][j] = dp[i - 1][j]   不选 i
 *          = dp[i - 1][j - v[i]] + w[i]  选 i
 *          = max(以上两种情况的较大值)
 * 初始化：dp[0][0] = 0
 */
int pack_complete()
{
    int N = 1000;
    int V = 1000;
    vector<int> v(N, 0);
    vector<int> w(N, 0);
    vector<int> dp(V + 1, 0);
    for(int i = 1; i <= N; ++i)
        for(int j = v[i - 1]; j <= V; ++j)
            dp[j] = max(dp[j], dp[j - v[i - 1]] + w[i - 1]);
    int result = dp[V]; // 整个 dp 初始化为 0 的时候，dp[V] 就是答案
    return result;
}


// 3. 多重背包
// 与 01 背包非常类似，只是状态转移时候
// dp[j] = max(dp[j], dp[j - v[i - 1]] + w[i - 1]); max 中分别代表第 i 个物品选和不选
// 改为
// dp[j] = max(dp[j], dp[j - v[i - 1]] + w[i - 1],
//                    dp[j - 2 * v[i - 1]] + 2 * w[i - 1],
//                    ...);
//                    max 中分别代表第 i 个物品从选 0 个一直到选 si 个
int pack_multiple()
{
    int N = 1000;
    int V = 1000;
    vector<int> v(N, 0);
    vector<int> w(N, 0);
    vector<int> s(N, 0);
    vector<int> dp(V + 1, 0);
    for(int i = 1; i <= N; ++i)
        for(int j = V; j >= 0; ++j)
            for(int k = 0; k <= s[i - 1] && k * v[i - 1] <= j; ++k)
                dp[j] = max(dp[j], dp[j - k * v[i - 1]] + k * w[i - 1]);
    int result = dp[V];
    return result;
}

// 多重背包的二进制优化，细节见笔记
// 对物品 i ，拆分变成完全背包
// s 拆分为 s - 1, s - 2, s - 4, s - 8,... 直至减为负数，最后剩下的数字放在最后
// 拆分为 log(s) 份
int pack_multiple_optim1()
{
    int N = 1000;
    int V = 1000;
    vector<int> v(N, 0);
    vector<int> w(N, 0);
    vector<int> s(N, 0);
    vector<int> dp(V + 1, 0);

    for(int i = 0; i < N; ++i)
    {
        int ss = s[i];
        ss -= 1;
        for(int k = 2; k <= ss; k *= 2)
        {
            ss -= k;
            v.push_back(v[i] * k);
            w.push_back(w[i] * k);
        }
        if(ss > 0)
        {
            v.push_back(v[i] * ss);
            w.push_back(w[i] * ss);
        }
    }

    N = v.size();
    for(int i = 1; i <= N; ++i)
        for(int j = V; j >= v[i - 1]; --j)
            dp[j] = max(dp[j], dp[j - v[i - 1]] + w[i - 1]);

    int result = dp[V];
    return result;
}

// 多重背包单调队列优化，细节见笔记
int pack_multiple_optim2()
{
    int N = 1000;
    int V = 1000;
    vector<int> v(N, 0);
    vector<int> w(N, 0);
    vector<int> s(N, 0);
    vector<int> dp(V + 1, 0);
    vector<int> dp_pre(V + 1, 0);
    vector<int> monotone_queue(V + 1, 0);

    for(int i = 1; i <= N; ++i)
    {
        dp_pre.clear();
        dp_pre = dp;
        int vv = v[i - 1];
        int ss = s[i - 1];
        int ww = w[i - 1];
        for(int j = 0; j < vv; ++j)
        {
            int head = 0, tail = -1;
            for(int k = j; k <= V; k += vv) // 枚举余数
            {
                if(head <= tail && k - ss * vv > monotone_queue[head])
                    ++head;

                while(head <= tail && dp_pre[monotone_queue[tail]] - (monotone_queue[tail] - j) / vv * ww <= dp_pre[k] - (k - j) / vv * ww)
                    --tail;

                if(head <= tail)
                    dp[k] = max(dp[k], dp_pre[monotone_queue[head]] + (k - monotone_queue[head]) / vv * ww);

                monotone_queue[++tail] = k;
            }
        }
    }

    int result = dp[V];
    return result;
}


// 4. 混合背包
struct Thing
{
    int kind;
    int v, w;
};

int pack_mix()
{
    int N = 1000;
    int V = 1000;
    vector<int> v(N, 0);
    vector<int> w(N, 0);
    vector<int> s(N, 0);
    vector<Thing> things;

    vector<int> dp(V + 1, 0);

    for(int i = 0; i < N; ++i)
    {
        int ss = s[i], vv = v[i], ww = w[i];
        if(ss < 0) things.push_back({-1, vv, ww});
        else if(ss == 0) things.push_back({0, vv, ww});
        else
        {
            for(int k = 1; k <= ss; k *= 2)
            {
                ss -= k;
                things.push_back({-1, vv * k, ww * k});
            }
            if(ss > 0)
                things.push_back({-1, vv * ss, ww * ss});
        }
    }

    for(auto thing: things)
    {
        if(thing.kind < 0)
        {
            for(int j = V; j >= thing.v; --j)
                dp[j] = max(dp[j], dp[j - thing.v] + thing.w);
        }
        else
        {
            for(int j = thing.v; j <= V; ++j)
                dp[j] = max(dp[j], dp[j - thing.v] + thing.w);
        }
    }

    int result = dp[V];
    return result;
}


// 5. 二维费用背包问题
int pack01_d2()
{
    int N = 1000;
    int V = 1000;
    int M = 1000;
    vector<int> v(N, 0);
    vector<int> w(N, 0);
    vector<int> m(N, 0);
    vector<vector<int> > dp(V + 1, vector<int>(M + 1, 0));
    for(int i = 1; i <= N; ++i)
        for(int j = V; j >= v[i - 1]; --j)
            for(int k = M; k >= m[i - 1]; --k)
                dp[j][k] = max(dp[j][k], dp[j - v[i - 1]][k - m[i - 1]] + w[i - 1]);
    int result = dp[V][M]; // 整个 dp 初始化为 0 的时候，dp[V] 就是答案
    return result;
}


// 6. 分组背包
int pack01_group()
{
    int N = 1000;
    int V = 1000;
    vector<vector<int> > v(N, vector<int>());
    vector<vector<int> > w(N, vector<int>());

    vector<int> dp(V + 1, 0);
    for(int i = 1; i <= N; ++i)
    {
        int s = v[i - 1].size(); // 组内元素个数
        for(int j = V; j >= 0; --j)
            for(int k = 0; k < s; ++k)
                if(j >= v[i - 1][k])
                    dp[j] = max(dp[j], dp[j - v[i - 1][k]] + w[i - 1][k]);
    }
    int result = dp[V]; // 整个 dp 初始化为 0 的时候，dp[V] 就是答案
    return result;
}


// 7. 有依赖的背包问题
// 邻接表建树
void dfs(int x, int V, vector<vector<int> >& dp, vector<vector<int> >& g, vector<int>& v, vector<int>& w)
{
    for(int i = v[x]; i <= V; i++)
        dp[x][i] = w[x];//点x必须选，所以初始化f[x][v[x] ~ m]= w[x]
    for(int i = 0;i < (int)g[x].size(); i++)
    {
        int y = g[x][i];
        dfs(y, V, dp, g, v, w);
        for(int j = V; j >= v[x]; j--)//j的范围为v[x]~V, 小于v[x]无法选择以x为子树的物品
            for(int k = 0; k <= j - v[x]; k++)//分给子树y的空间不能大于j-v[x],不然都无法选根物品x
                dp[x][j] = max(dp[x][j], dp[x][j-k] + dp[y][k]);
    }
}

int main()
{
    int N,V;
    cin >> N >> V;
    vector<int> v(N + 1, 0);
    vector<int> w(N + 1, 0);

    // dp[x][v]表达选择以x为子树的物品，在容量不超过v时所获得的最大价值
    vector<vector<int> > dp(N + 1, vector<int>(V + 1, 0));
    vector<vector<int> > g(N + 1, vector<int>());

    int root;
    for(int i = 1; i <= N; i++)
    {
        int fa;
        cin >> v[i] >> w[i] >> fa;
        if(fa == -1)
            root = i;
        else
            g[fa].push_back(i);
    }

    dfs(root, V, dp, g, v, w);

    cout << dp[root][V];
    return 0;
}


// 8. 背包问题求方案数
int pack01_scheme_cnt()
{
    int N = 1000;
    int V = 1000;
    int mod = 1e9 + 7;
    vector<int> v(N, 0);
    vector<int> w(N, 0);
    vector<int> dp(V + 1, INT_MIN);
    vector<int> g(V + 1, 0);
    g[0] = 1, dp[0] = 0;
    for(int i = 1; i <= N; ++i)
        for(int j = V; j >= v[i - 1]; --j)
        {
            int s = 0;
            int t = max(dp[j], dp[j - v[i - 1]] + w[i - 1]);
            if(dp[j] == t) s += g[j];
            if(dp[j - v[i - 1]] + w[i - 1] == t) s += g[j - v[i - 1]];
            if(s >= mod) s -= mod;
            dp[j] = t;
            g[j] = s;
        }

    int maxw = 0;
    for(int i = 0; i <= V; ++i)
        maxw = max(maxw, dp[i]);

    int result = 0;
    for(int i = 0; i <= V; ++i)
        if(maxw == dp[i])
        {
            result += g[i];
            if(result > mod) result -= mod;
        }

    return result;
}


// 9. 背包问题输出具体方案
// 输出字典序最小的方案
vector<int> pack01_scheme()
{
    int N = 1000;
    int V = 1000;
    vector<int> v(N, 0);
    vector<int> w(N, 0);
    vector<vector<int> > dp(N + 1, vector<int>(V + 1, 0));

    for(int i = N; i >= 1; --i)
        for(int j = 0; j <= V; ++j)
        {
            dp[i - 1][j] = dp[i][j];
            if(j >= v[i - 1])
                dp[i - 1][j] = max(dp[i - 1][j], dp[i][j - v[i - 1]] + w[i - 1]);
        }
    // 以上 dp 枚举在 01 背包求最大价值上通过

    vector<int> result;
    int vol = V;
    for(int i = 1; i <= N; ++i)
    {
        if(vol - v[i - 1] >= 0 && dp[i - 1][vol] == dp[i][vol - v[i - 1]] + w[i - 1])
        {
            cout << i << " ";
            vol -= v[i - 1];
        }
    }
    return result;
}

