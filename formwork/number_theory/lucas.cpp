
// Lucas 定理实现 C(n,m) % p 的代码：
using ll = long long;
ll exp_mod(ll a, ll b, ll p)
{
    //快速幂取模
    ll res = 1;
    while(b != 0)
    {
        if(b & 1) res = (res * a) % p;
        a = (a * a) % p;
        b >>= 1;
    }
    return res;
}

ll Comb(ll a, ll b, ll p)
{
    //求组合数C(a,b) % p
    if(a < b)   return 0;
    if(a == b)  return 1;
    if(b > a - b)   b = a - b;

    ll ans = 1, ca = 1, cb = 1;
    for(ll i = 0; i < b; ++i)
    {
        ca = (ca * (a - i)) % p;
        cb = (cb * (b - i)) % p;
    }
    ans = (ca * exp_mod(cb, p - 2, p)) % p;
    return ans;
}

ll Lucas(ll n, ll m, ll p)
{
    //Lucas定理求C(n,m)%p
    ll ans = 1;

    while(n && m && ans)
    {
        ans = (ans * Comb(n % p, m % p, p)) % p;
        n /= p;
        m /= p;
    }
    return ans;
}
