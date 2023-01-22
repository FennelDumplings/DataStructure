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

//传入字符串S和对应的后缀数组，计算高度数组
void construct_lcp(string S, vector<int> &sa, vector<int> &lcp)
{
	int n = S.length();
	for(int i = 0; i <=n; ++i)
	{
		rankm[sa[i]] = i;
	}
	int h = 0;
	lcp[0] = 0;
	for(int i = 0; i < n; ++i)
	{
		//计算字符串中从位置i开始的后缀及其在后缀数组中的前一个后缀的LCP
		int j = sa[rankm[i] - 1];
		//将h减去首字母的１长度，　在保持前缀相同的情况下不断增加
		if(h > 0)
			--h;
		for(; j + h < n && i + h < n; ++h)
		{
			if(S[j + h] != S[i + h])
				break;
		}
		lcp[rankm[i] - 1] = h;
	}
}

int main()
{
	string s = "aljdfhkjhfasgla";
	int sl = s.length();
	string t = "mcbhkjhfkjf";
	cout << s << endl;
	cout << t << endl;
	string S = s + '$' + t;
	vector<int> sa_S(S.length() + 1, 0);
	vector<int> lcp(S.length() + 1, 0);
	construct_sa(S, sa_S);
	construct_lcp(S, sa_S, lcp);
	int ans = 0;
	for(int i = 0; i < S.length(); ++i)
	{
		if((sa_S[i] < sl) != (sa_S[i + 1] < sl))
		{
			ans = max(ans, lcp[i]);
		}
	}
	cout << ans << endl;
}