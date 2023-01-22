#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

void discretization(const vector<vector<int> >& a, vector<int>& x, vector<int>& y)
{
    unordered_set<int> set_x, set_y;
    for(const vector<int> aa: a)
    {
        int i = aa[0], j = aa[1];
        for(int k = i - 1; k <= i + 1; ++k)
        {
            if(set_x.find(k) == set_x.end())
            {
                x.push_back(k);
                set_x.insert(k);
            }
        }
        for(int k = j - 1; k <= j + 1; ++k)
        {
            if(set_y.find(k) == set_y.end())
            {
                y.push_back(k);
                set_y.insert(k);
            }
        }
    }
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    y.erase(unique(y.begin(), y.end()), y.end());
}

int _find(int v, const vector<int>& x)
{
    return lower_bound(x.begin(), x.end(), v) - x.begin();
}
