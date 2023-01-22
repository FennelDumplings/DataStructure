

//minFactor[i] = i 的最小素因子(素数为本身)
int minFactor[MAX_N];

void eratosthenes2()
{
	minFactor[0] = minFactor[1] = -1;
	for(int i = 2; i <= n; ++i)
	{
		minFactor[i] = i;//全设为素数
	}
	int sqrtn = int(sqrt(n));
	for(int i = 2; i <= sqrtn; ++i)
	{
		if(minFactor[i] == i)
		{
			for(int j = i * i; j <= n; j += i)
			{
				if(minFactor[j] = j)
					minFactor[j] = i;
			}
		}
	}
}

vector<int> factor(int n)//对n因子分解
{
	vector<int> ret;
	while(n > 1)
	{
		ret.push_back(minFactor[n]);
		n /= minFactor[n];
	}
	return ret;
}