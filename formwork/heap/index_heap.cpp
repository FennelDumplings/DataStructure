
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class IndexMaxHeap
{
public:
    IndexMaxHeap()
    {
        _size = 0;
    }

    void build(const vector<int>& nums)
    {
        data.clear();
        indexes.clear();
        mapping.clear();
        int n = nums.size();
        data.assign(n + 1, -1);
        indexes.assign(n + 1, -1);
        mapping.assign(n + 1, -1);
        for(int i = 1; i <= n; ++i)
        {
            data[i] = nums[i - 1];
            indexes[i] = i;
            mapping[i] = i;
        }
        _size = n;
        for(int i = n; i >= 1; --i)
            push_down(i);
    }

    int top()
    {
        if(empty())
            return -1;
        return data[indexes[1]];
    }

    int pop()
    {
        if(empty())
            return -1;
        int ans = data[indexes[1]];
        _remove(1);
        return ans;
    }

    void push(int idx, const int key)
    {
        ++idx;
        // 覆盖 data[idx] 的数据, idx 同时也是 key 的索引
        // mapping[idx] := key 在堆中的逻辑位置，即 indexes 中的位置
        if(idx >= (int)data.size())
            dilatation();
        ++_size;
        data[idx] = key;
        mapping[idx] = _size;
        indexes[_size] = idx;
        push_up(_size);
    }

    void remove(int idx)
    {
        ++idx;
        cout << "remove: " << idx << " " << mapping[idx] << " " << data[indexes[mapping[idx]]] << endl;
        if(mapping[idx] < 0)
            return;
        int i = mapping[idx];
        _remove(i);
    }

    void change(int idx, const int new_key)
    {
        ++idx;
        if(mapping[idx] < 0)
            return;
        if(data[idx] == new_key)
            return;
        data[idx] = new_key;
        int i = mapping[idx];
        push_up(i);
        push_down(i);
    }

    int size()
    {
        return _size;
    }

    bool empty()
    {
        return _size == 0;
    }

    void show()
    {
        for(int i: data)
            cout << i << " ";
        cout << endl;
        for(int i: indexes)
            cout << i << " ";
        cout << endl;
        for(int i: mapping)
            cout << i << " ";
        cout << endl;
        //cout << "   ";
        //for(int i = 1; i <= _size; ++i)
        //    cout << indexes[i] << " ";
        //cout << endl;
        //cout << "   ";
        //for(int i = 1; i <= _size; ++i)
        //    cout << data[indexes[i]] << " ";
        //cout << endl;

        cout << " ----------- " << endl;
    }

private:
    vector<int> data; // keys
    vector<int> indexes;
    int _size;
    vector<int> mapping; // id -> idxs

    void dilatation()
    {
        int new_capacity = (int)data.size() * 2 + 1;
        vector<int> tmp_data(new_capacity, -1);
        vector<int> tmp_indexes(new_capacity, -1);
        vector<int> tmp_mapping(new_capacity, -1);
        for(int i = 0; i < (int)data.size(); ++i)
        {
            tmp_data[i] = data[i];
            tmp_indexes[i] = indexes[i];
            tmp_mapping[i] = mapping[i];
        }
        data.swap(tmp_data);
        indexes.swap(tmp_indexes);
        mapping.swap(tmp_mapping);
    }

    void _remove(int i)
    {
        if(i > _size)
            return;
        if(i == _size)
        {
            cout << "置 -2: " << indexes[_size] << endl;
            mapping[indexes[_size]] = -2;
            --_size;
            return;
        }
        int idx_i = indexes[i];
        int idx_j = indexes[_size];
        cout << "置 -2: " << idx_i << endl;
        swap(mapping[idx_i], mapping[idx_j]);
        mapping[idx_i] = -2;
        indexes[i] = indexes[_size--];
        push_up(i);
        push_down(i);
    }

    void push_up(int i)
    {
        if(i > _size) return;
        while(i / 2 > 0 && data[indexes[i / 2]] < data[indexes[i]])
        {
            swap(mapping[indexes[i]], mapping[indexes[i / 2]]);
            swap(indexes[i], indexes[i / 2]);
            i /= 2;
        }
    }

    void push_down(int i)
    {
        int ori = i, left = i * 2, right = i * 2 + 1;
        if(left <= _size && data[indexes[left]] > data[indexes[ori]])
            ori = left;
        if(right <= _size && data[indexes[right]] > data[indexes[ori]])
            ori = right;
        if(ori != i)
        {
            swap(mapping[indexes[i]], mapping[indexes[ori]]);
            swap(indexes[i], indexes[ori]);
            push_down(ori);
        }
    }
};

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if(nums.empty()) return vector<int>();
        int n = nums.size();
        if(n <= k)
        {
            int mx = nums[0];
            for(int i = 1; i < n; ++i)
                mx = max(mx, nums[i]);
            return vector<int>({mx});
        }
        // 滑动 n - k 次
        // 0..k-1
        IndexMaxHeap heap;
        heap.build(vector<int>(nums.begin(), nums.begin() + k));
        vector<int> result;
        result.push_back(heap.top());
        heap.show();
        for(int i = k; i < n; ++i)
        {
            // heap.change(i % k, nums[i]);
            heap.remove(i - k);
            heap.push(i, nums[i]);
            heap.show();
            result.push_back(heap.top());
        }
        return result;
    }
};
