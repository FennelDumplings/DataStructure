//a += b * (10 ^ k)
void addTo(vector<int> &a, const vector<int> &b, int k);

//a -= b; 已知a >= b
void subFrom(vector<int> &a, const vector<int> &b);

/////////////////////////////////////////////////////////
void normalize(vector<int> &num)//处理进位
{
	num.push_back(0);
	//处理进位
	for(int i = 0; i < num.size(); ++i)
	{
		if(num[i] < 0)
		{
			int borrow = (abs(num[i]) + 9) / 10;
			num[i + 1] -= borrow;
			num[i] += borrow * 10;
		}
		else
		{
			num[i + 1] += num[i] / 10;
			num[i] %= 10;
		}
	}
	while(num.size() > 1 && num.back() == 0)
		num.pop_back();
}

vector<int> multiply(const vector<int> &a, const vector<int> &b) 
{
	vector<int> c(a.size() + b.size() + 1, 0);
	for(int i = 0; i < a.size(); ++i)
	{
		for(int j = 0; j < b.size(); ++j)
		{
			c[i + j] = a[i] * a[j];
		}
	}
	normailze(c);
	return c;
} 

vector<int> karatsuba(const vector<int> &a, const vector<int> &b)
{
	int an = a.size(), bn = b.size();
	//a位数小于b时，两数互换
	if(an < bn)
		return karatsuba(b, a);
	//初始部分
	if(an == 0 || bn == 0)
		return vector<int>();
	if(an <= 50)
		return multiply(a, b);

	int half = an / 2;
	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
	vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());

	vector<int> z2 = karatsuba(a1, b1);
	vector<int> z0 = karatsuba(a0, b0);
	addTo(a0, a1, 0);
	addTo(b0, b1, 0);
	vector<int> z1 = karatsuba(a0, b0);
	subFrom(z1, z0);
	subFrom(z1, z2);

	//ret = z0 + z1 + 10^half + z2 * 10^(half*2)
	vector<int> ret;
	addTo(ret, z0, 0);
	addTo(ret, z1, half);
	addTo(ret, z2, half + half);
	return ret;
}