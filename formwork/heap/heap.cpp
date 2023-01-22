#include <vector>
#include <iostream>

using namespace std;

class MaxIndexHeap {
public:
    MaxIndexHeap() {
        heap = vector<int>(1, 0); // 数据数组 heap 从 1 开始
    }

    bool empty() {
        return _size() == 0;
    }

    int size() {
        return _size();
    }

    void push(int x) {
        heap.push_back(x);
        int size = _size();
        _push_up(size);
    }

    int top() {
        return heap[1];
    }

    void pop()
    {
        int size = _size();
        heap[1] = heap[size];
        heap.pop_back();
        _push_down(1);
    }

private:
    vector<int> heap;

    int _size() {
        return heap.size() - 1;
    }

    // 堆的元素下标从1开始
    void _push_down(int u)
    {
        int size = _size();
        int t = u, left = u * 2, right = u * 2 + 1;
        if(left <= size && heap[left] > heap[t]) t = left;
        if(right <= size && heap[right] > heap[t]) t = right;
        if(t != u)
        {
            swap(heap[u], heap[t]);
            _push_down(t);
        }
    }

    void _push_up(int u)
    {
        int size = _size();
        if(u > size) return;
        while(u / 2 && heap[u / 2] < heap[u])
        {
            swap(heap[u / 2], heap[u]);
            u /= 2;
        }
    }
};

int main()
{
    int M;
    cin >> M;
    MaxHeap maxheap;
    for(int i = 0; i < M; ++i)
    {
        int x;
        cin >> x;
        maxheap.push(x);
    }
    cout << "size: " << maxheap.size() << endl;
    while(!maxheap.empty())
    {
        cout << maxheap.top() << " ";
        maxheap.pop();
    }
    cout << endl;
}
