ll mod_pow(ll x, ll n, ll mod)
{
	ll res = 1;
	while(n > 0)
	{
		if(n & 1)
			res = res * x % mod;//二进制最低位为１，乘以x^(2^i)
		x = x * x % mod;//将x平方
		n >>= 1;
	}
	return res;
}