#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int n, k;

const int MAX_N = 10005;

int rankm[MAX_N + 1];
int tmp[MAX_N + 1];

//比较rank[i], rank[i + k]和rank[j], rank[j + k]
bool compare_sa(int i, int j)
{
	if(rankm[i] != rankm[j])
		return rankm[i] < rankm[j];
	else
	{
		int ri = i + k <= n ? rankm[i + k] : -1;
		int rj = j + k <= n ? rankm[j + k] : -1;
		return ri < rj;
	}
}

//计算S的后缀数组
void construct_sa(string S, vector<int> &sa)
{
	n = S.length();
	//初始长度为１,rank直接取字符的编码
	for(int i = 0; i <= n; ++i)
	{
		sa[i] = i;
		rankm[i] = i < n ? S[i] : -1;
	}
	//利用对长度为k的排序结果对长度2k的排序
	for(k = 1; k <= n; k *= 2)
	{
		sort(sa.begin(), sa.end(), compare_sa);

		//先在tmp中临时存储新计算的rank, 再转存回rank中
		tmp[sa[0]] = 0;
		for(int i = 1; i <= n; ++i)
		{
			tmp[sa[i]] = tmp[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
		}
		for(int i = 0; i <= n; ++i)
		{
			rankm[i] = tmp[i];
		}
	}
}

bool contain(string S, vector<int> &sa, string T)
{
	int a = 0;
	int b = S.length();
	while(b - a > 1)
	{
		int c = (a + b) / 2;
		if(S.compare(sa[c], T.length(), T) < 0)
			a = c;
		else
			b = c;
	}
	return S.compare(sa[b], T.length(), T) == 0;
}

int main()
{
	string str = "alkjdfhlifihwahglzmcbsmdfkjhjkafdjkgfglyiqlghjcbvmnzkjshejual";
	string ss = "mcbsmdfjhghk";
	vector<int> sa_str(str.length() + 1, 0);
	construct_sa(str, sa_str);
	bool flg = contain(str, sa_str, ss);
	cout << "czx" << endl;
	if(flg)
		cout << true << endl;
	else
		cout << false << endl;
}