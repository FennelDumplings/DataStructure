#include <iostream>
#include <vector>
#include <string>
using namespace std;

//顺时针旋转
vector<string> rotateMat(const vector<string> &arr)
{
	vector<string> ret(arr[0].size(), string(arr.size(), ' '));
	for(int i = 0; i < arr.size(); ++i)
	{
		for(int j = 0; j < arr[0].size(); ++j)
		{
			ret[j][arr.size() - i - 1] = arr[i][j];
		}
	}
	return ret;
}

int main()
{
	vector<string> mat(5, string(7, ' '));
	mat[0] = "abcdefg";
	mat[1] = "bcdefgh";
	mat[2] = "cdefghi";
	mat[3] = "defghij";
	mat[4] = "efghijk";
	for(int i = 0; i < mat.size(); ++i)
	{
		cout << mat[i] << endl;
	}
	cout << endl;
	vector<string> mat_rot = rotateMat(mat);
	for(int i = 0; i < mat_rot.size(); ++i)
	{
		cout << mat_rot[i] << endl;
	}
}