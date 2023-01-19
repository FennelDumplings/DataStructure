#include <vector>

using namespace std;

class MaxHeap
{
public:
    MaxHeap()
    {
        data.assign(0, -1);
        _size = 0;
    }

    void build(const vector<int>& nums)
    {
        // 建堆
        data.clear();
        int n = nums.size();
        data.assign(n + 1, 0);
        data[0] = -1;
        for(int i = 0; i < n; ++i)
            data[i + 1] = nums[i];
        _size = n;
        for(int i = n; i >= 1; --i)
            push_down(i);
    }

    int top()
    {
        // 查询最大元素
        if(empty())
            return -1;
        return data[1];
    }

    int pop()
    {
        // 弹出
        if(empty())
            return -1;
        int ans = data[1];
        data[1] = data[_size--];
        push_down(1);
        return ans;
    }

    void push(int key)
    {
        // 压入
        if(_size + 1 >= (int)data.size())
            dilatation();
        data[++_size] = key;
        push_up(_size);
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

    void dilatation()
    {
        // 扩容
        vector<int> tmp_data((_size + 1) * 2 + 1);
        tmp_data[0] = 1;
        for(int i = 1; i <= _size; ++i)
            tmp_data[i] = data[i];
        data.swap(tmp_data);
    }

    void push_up(int i)
    {
        // 向上调整
        if(i > _size) return;
        while(i / 2 > 0 && data[i / 2] < data[i])
        {
            swap(data[i], data[i / 2]);
            i /= 2;
        }
    }

    void push_down(int i)
    {
        // 向下调整
        int ori = i, left = i * 2, right = i * 2 + 1;
        if(left <= _size && data[left] > data[ori])
            ori = left;
        if(right <= _size && data[right] > data[ori])
            ori = right;
        if(ori != i)
        {
            swap(data[i], data[ori]);
            push_down(ori);
        }
    }
};
