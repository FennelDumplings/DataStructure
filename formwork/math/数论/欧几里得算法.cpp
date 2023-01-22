#include <iostream>
using namespace std;

int gcd(int p, int q)
{
	if(q == 0)
		return p;
	return gcd(q, p % q);
}

int lcm(int p, int q)
{
	return p * q / gcd(p, q);
}

int main()
{
	int a, b;
	cin >> a >> b;
	cout << "gcd: " << gcd(a, b) << endl;
	cout << "lcm: " << lcm(a, b) << endl;
}