#include <cstring>
#include <cmath>
using namespace std;

int n;
bool isPrime[n + 1];

void eratosthenes()
{
	memset(isPrime, 1, sizeof(isPrime));
	isPrime[0] = isPrime[1] = false;
	int sqrtn = int(sqrt(n));
	for(int i = 2; i <= sqrtn; ++i)
	{
		//如果此数值尚未删除
		if(isPrime[i])
		{
			//i的倍数j, 设置isPrime[j] = false
			//小于i*i的倍数已经被删除
			for(int j = i * i; j <= n; j += i)
				isPrime[j] = false;
		}
	}
}