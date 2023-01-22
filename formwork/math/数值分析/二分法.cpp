#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

double f(double);

double bisection(double lo, double hi)
{
	if(f(lo) > 0)
		swap(lo, hi);
	//循环不变式 f(lo) <= 0 <= f(hi)
	//while(fabs(hi - lo) > 2e-7)
	for(int i = 0; i < 100; ++i)
	{
		double mid = (lo + hi) / 2;
		double fmid = f(mid);
		if(fmid < 0)
			lo = mid;
		else
			hi = mid;
	}
	return (lo + hi) / 2
}