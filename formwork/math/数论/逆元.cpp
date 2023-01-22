int extgcd(int a, int b, int & x, int & y)
{
	int d = a;
	if(b != 0)
	{
		d = extgcd(b, a % b, y, x);
		y -= (a / b) * x;
	}
	else
	{
		x = 1;
		y = 0;
	}
	return d;
}

int mod_inverse(int a, int m)
{
	int x, y;
	extgcd(a, m, x, y);
	return (m + x % m) % m;
}
