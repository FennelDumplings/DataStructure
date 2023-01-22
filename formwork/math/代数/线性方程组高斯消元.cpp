#include <vector>
#include <algorithm>
using namespace std;

const double EP = 1E-8;
typedef vector<double> vec;
typedef vector<vec> mat;

//解Ax=b
//A是方阵
//无解或无穷解时，反长为0的数组
vec gauss_jordan(const mat &A, const vec &b)
{
	int n = A.size();
	mat B(n, vec(n + 1));
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			B[i][j] = A[i][j];
		}
	}
	for(int i = 0; i < n; ++i)
	{
		B[i][n] = b[i];
	}

	for (int i = 0; i < n; ++i)
	{
		//把正在处理的未知数系数的绝对值最大的式子换到第i行
		int povit = i;
		for (int j = i; j < n; ++j)
		{
			if(abs(B[j][i]) > abs(B[povit][i]))
				povit = j;
		}
		swap(B[i], B[povit]);

		//无解或有多解
		if(abs(B[i][i]) < EP)
			return vec();

		//把正处理的系数变为1
		for(int j = i + 1; j <= n; ++j)
		{	
			B[i][j] /= B[i][i];
		}
		for(int j = 0; j < n; ++j)
		{
			if(i != j)
			{
				//从第j个式子消去第i个未知数
				for(int k = i + 1; k <= n; ++k)
				{
					B[j][k] -= B[j][i] * B[i][k];
				}
			}
		}
	}
	vec x(n);
	//存存在右边的b就是答案
	for(int i = 0; i < n; ++i)
	{
		x[i] = B[i][n];
	}
	return x;
}