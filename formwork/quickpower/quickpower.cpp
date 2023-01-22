
#include <vector>

using namespace std;

int quickpower(int a, int n)
{
    // a==0&&n==0特判
    int ans = 1; // n = 0 时候不进循环
    while(n)
    {
        if(n & 1) ans *= a;
        a *= a;
        n >>= 1;
    }
    return ans;
}

using ll = long long;
int quickpower2(int a, int n, int m) // 处理不了n是负数
{
    int ans = 1;
    while(n)
    {
        if(n & 1) ans = ((ll)ans * a) % m;
        a = (ll)a * a % m;
        n >>= 1;
    }
    return ans;
}
