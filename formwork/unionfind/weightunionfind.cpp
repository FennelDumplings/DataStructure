
#include <vector>

using namespace std;

class WeightUnionFindSet
{
public:
    WeightUnionFindSet(int N)
    {
        _father = vector<int>(N, -1);
        _rank = vector<int>(N, 1);
        _weight = vector<double>(N, 1.0); // a / a = 1.0
        for(int i = 0; i < N; ++i)
            _father[i] = i;
    }

    bool same(int x, int y)
    {
        return _find(x) == _find(y);
    }

    double get_weight(int x)
    {
        _find(x);
        return _weight[x];
    }

    void merge(int x, int y, double w)
    {
        int rootx = _find(x);
        int rooty = _find(y);
        if(rootx == rooty) return;
        if(_rank[rootx] < _rank[rooty])
        {
            _father[rootx] = rooty;
            // 四边形法则
            _weight[rootx] = _weight[y] * w / _weight[x];
        }
        else
        {
            _father[rooty] = rootx;
            // 四边形法则
            _weight[rooty] = _weight[x] * (1 / w) / _weight[y];
        }
        if(_rank[rootx] == _rank[rooty])
            ++_rank[rootx];
    }



private:
    vector<int> _father;
    vector<int> _rank;
    vector<double> _weight;

    int _find(int x)
    {
        if(_father[x] == x)
            return x;
        int new_fa = _find(_father[x]);; // 路径压缩前的父节点
        // 回溯更新权
        _weight[x] *= _weight[_father[x]];
        _father[x] = new_fa;
        return _father[x];
    }
};
