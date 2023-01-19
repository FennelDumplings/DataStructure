#include <vector>

using namespace std;

class MinMaxHeap
{
public:
    MinMaxHeap()
    {
        data.assign(0, -1);
        _size = 0;
    }

    int size()
    {
        // 元素个数
        return _size;
    }

    bool empty()
    {
        // 判断空
        return _size == 0;
    }

private:
    vector<int> data; // 容纳 keys 的容器
    int _size; // 元素个数

};
