
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class RMQ
{
public:
    RMQ(){}

    void init(const vector<int>& arr)
    {
        int n = arr.size();
        // 2 ^ m <= n
        // log2(2^m) <= log2(n)
        // m <= log2(n)
        int m = log2(n);
        dp.assign(n + 1, vector<int>(m + 1, 0));
        for(int i = 1; i <= n; ++i)
            dp[i][0] = arr[i]; //初始化
        for(int j = 1; (1 << j) <= n; ++j)
            for(int i = 1; i + (1 << j) - 1 <= n; ++i)
                dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
    }

    int query(int l, int r)
    {
        int k = log2(r - l + 1);
        return min(dp[l][k], dp[r - (1 << k) + 1][k]);
    }
private:
    vector<vector<int>> dp;
};

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; ++i)
        cin >> arr[i];
    cout << "数据: " << endl;
    for(int i = 0; i < n; ++i)
        cout << i << "  " << arr[i] << endl;
    RMQ rmq;
    rmq.init(arr);
    while(true)
    {
        int start, end;
        cin >> start >> end;
        cout << "查询区间: [" << start << ", " << end << "], 最小值：";
        cout << rmq.query(start, end) << endl;
    }
};
