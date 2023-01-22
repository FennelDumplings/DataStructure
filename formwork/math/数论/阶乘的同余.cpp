
int fact[MAX_P];//预处理n! mod p表   O(p)

//分解n! 返回a mod p
int mod_fact(int n, int p, int &e)
{
	e = 0;
	if(n == 0)
		return 1;
	//计算p的倍数部分
	int res = mod_fact(n / p, p, e);
	e += n / p;

	if(n / p % 2 != 0)
		return res * (p - fact[n % p]) % p;
	return res * fact[n % p] % p;
}