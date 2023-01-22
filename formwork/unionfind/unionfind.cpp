#include <vector>
using namespace std;

class UnionFindSet {
public:
    UnionFindSet(int n)
    {
        _item_size = n;
        _set_size = n;
        _father = vector<int>(_item_size, -1);
        _rank = vector<int>(_item_size, 0);
        for(int i = 0; i < _item_size; ++i)
            _father[i] = i;
    }

    ~UnionFindSet(){}

    bool same(int x, int y)
    {
        return _find(x) == _find(y);
    }

    void merge(int x, int y)
    {
        x = _find(x);
        y = _find(y);
        if(x == y) return;

        // 此时 x, y 是所在树的根
        if(_rank[x] < _rank[y])
            _father[x] = y;
        else
        {
            _father[y] = x;
            if(_rank[x] == _rank[y])
                ++_rank[x];
        }

        --_set_size;
    }

    int item_size()
    {
        return _item_size;
    }

    int set_size()
    {
        return _set_size;
    }

private:
    vector<int> _father;
    vector<int> _rank;
    int _item_size;
    int _set_size;

    int _find(int x)
    {
        if(_father[x] == x)
            return x;
        else
            return _father[x] = _find(_father[x]); // 路径压缩
            // return _find(_father[x]);
    }
};
