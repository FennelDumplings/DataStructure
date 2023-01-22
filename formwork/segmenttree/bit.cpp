#include <vector>

using namespace std;

class BIT {
public:
    BIT():sums(1, 0){}
    BIT(int n):sums(n + 1, 0){}

    void update(int index, int delta)
    {
        int n = sums.size();
        while(index < n)
        {
            sums[index] += delta;
            index += _lowbit(index);
        }
    }

    int query(int i)
    {
        int sum = 0;
        while(i > 0)
        {
            sum += sums[i];
            i -= _lowbit(i);
        }
        return sum;
    }

private:
    vector<int> sums;

    int _lowbit(int x)
    {
        return x & (-x);
    }
};
