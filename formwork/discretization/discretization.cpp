#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int find(int v, const vector<int>& aa) // 从 nums 的值找到对应的离散化之后的值
{
    return lower_bound(aa.begin(), aa.end(), v) - aa.begin() + 1;
}

vector<int> discretization(const vector<int>& a)
{
    int n = a.size();
    vector<int> aa = a;
    sort(aa.begin(), aa.end());
    aa.erase(unique(aa.begin(), aa.end()), aa.end());
    vector<int> result((int)a.size());
    for(int i = 0; i < n; ++i)
        result[i] = find(a[i], aa);
    return result;
}

int main()
{
    vector<int> a({-7, 0, 4, (int)1e6 + 7, 9, 4, (int)-1e3 + 7});
    vector<int> aa = discretization(a);

    for ( int i = 0; i < (int)a.size(); i++)
    {
        cout << aa[i] << " ";
    }

    return 0;
}
