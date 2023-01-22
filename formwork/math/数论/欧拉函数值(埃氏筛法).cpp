int euler_phi(int n)
{
	int res = n;
	for(int i = 2; i * i <= n; ++i)
	{
		if(n % i == 0)
		{
			res = res / i * (i - 1);//euler定义
			for(; n % i == 0; n /= i);
		}
	}
	if(n != 1)
		res = res / n * (n - 1);
	return res;
}

const int n = 10;
int euler[n];

void euler_phi2()
{
	for(int i = 0; i < n; ++i)
		euler[i] = i;
	for(int i = 2; i < n; ++i)
	{
		if(euler[i] == i)
		{
			for(int j = i; j < n; j += i)
				euler[j] = euler[j] / i * (i - 1);
		}
	}
}