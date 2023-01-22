#include <cmath>
using namespace std;

bool isPrime(int n)
{
	if(n <= 1)
		return false;
	if(n == 2)
		return true;
	if(n % 2 == 0)
		return false;
	int sqrtn = int(sqrt(n));
	for(int div = 3; div <= sqrtn; div += 2)
	{
		if(n % div == 0)
			return false;
	}
	return true;
}