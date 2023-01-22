#include <iostream>
#include <vector>
#include <climits>
#include <cmath>

using namespace std;


// 分块查找表
class Block
{
public:
    Block(){}

    void build(const vector<int>& arr)
    {
        nums = arr;
        n = nums.size();
        block_size = floor(sqrt(n)); // 8 -> 2, 9 -> 3, 10 -> 3, 11 -> 3, ..., 15 -> 3, 16 -> 4
        bn = n / block_size + 1; // 最后一个桶的元素个数可能为 [0, block_size - 1]
        lazy = vector<int>(bn, 0);
        maxx = vector<int>(bn, 0);
        has_lazy = vector<bool>(bn, false);
        for(int i = 0; i < n; ++i)
        {
            int bucket_id = i / block_size;
            maxx[bucket_id] = max(maxx[bucket_id], nums[i]);
        }
    }

    void point_update(int idx, int x)
    {
        // 先将对应块的标记 `lazy[i]` 下传，再暴力更新被修改块的状态。时间复杂度 O(\sqrt(N))
        int bucket_id = idx / block_size;
        if(has_lazy[bucket_id])
        {
            for(int i = bucket_id * block_size; i < min((bucket_id + 1) * block_size, n); ++i)
                nums[i] = lazy[bucket_id];
            has_lazy[bucket_id] = false;
        }
        nums[idx] = x;
        maxx[bucket_id] = max(maxx[bucket_id], x);
    }

    void range_update(int l, int r, int x)
    {
        int bucket_l = l / block_size, bucket_r = r / block_size;
        // 左半桶
        if(has_lazy[bucket_l])
        {
            for(int i = bucket_l * block_size; i < min((bucket_l + 1) * block_size, n); ++i)
                nums[i] = lazy[bucket_l];
            has_lazy[bucket_l] = false;
        }
        for(int i = l; i <= min((bucket_l + 1) * block_size - 1, r); ++i)
            nums[i] = x;
        maxx[bucket_l] = max(maxx[bucket_l], x);
        // 右半桶
        if(bucket_l != bucket_r)
        {
            if(has_lazy[bucket_r])
            {
                for(int i = bucket_r * block_size; i < min((bucket_r + 1) * block_size, n); ++i)
                    nums[i] = lazy[bucket_r];
                has_lazy[bucket_r] = false;
            }
            for(int i = bucket_r * block_size; i <= r; ++i)
                nums[i] = x;
            maxx[bucket_r] = max(maxx[bucket_r], x);
        }
        // 中间的桶
        for(int bucket_id = bucket_l + 1; bucket_id < bucket_r; ++bucket_id)
        {
            lazy[bucket_id] = x;
            has_lazy[bucket_id] = true;
            maxx[bucket_id] = x;
        }
    }

    int range_query(int l, int r)
    {
        // 对于中间跨过的整块，直接利用块保存的信息统计答案，两端剩余部分任然可以暴力扫描统计。
        int bucket_l = l / block_size, bucket_r = r / block_size;
        int result = nums[l];

        // 左半桶
        if(has_lazy[bucket_l])
            result = maxx[bucket_l];
        else
            for(int i = l; i <= min((bucket_l + 1) * block_size - 1, r); ++i)
                result = max(result, nums[i]);
        // 右半桶
        if(bucket_l != bucket_r)
        {
            if(has_lazy[bucket_r])
                result = max(result, maxx[bucket_r]);
            else
                for(int i = bucket_r * block_size; i <= r; ++i)
                    result = max(result, nums[i]);
        }
        // 中间的桶
        for(int bucket_id = bucket_l + 1; bucket_id < bucket_r; ++bucket_id)
            result = max(result, maxx[bucket_id]);
        return result;
    }

    vector<int> nums;
    vector<int> maxx;
    vector<int> lazy;
    vector<bool> has_lazy;
    int block_size, bn, n;
};

// ---------------------------------------------------------------------

// 线段树 RMQ 数组写法
// 区间赋值，区间查询
class SeqSegmentTree
{
public:
    SeqSegmentTree()
    {
        st_vec = vector<int>();
        lazy = vector<int>();
        n = -1;
    }

    void build(const vector<int>& nums)
    {
        if(nums.empty()) return;
        n = nums.size();
        st_vec.resize(n * 4);
        lazy.resize(n * 4);
        _build(1, 0, n - 1, nums);
    }

    void range_update(int i, int j, int v)
    {
        // [i, j] 范围内改为 v
        _range_update(1, 0, n - 1, i, j, v);
    }

    int range_query(int i, int j)
    {
        return _range_query(1, 0, n - 1, i, j);
    }

private:
    int _range_query(int node, int nodeLeft, int nodeRight, int start, int end)
    {
        if(nodeLeft == start && nodeRight == end)
            return st_vec[node];
        int nodeMid = (nodeLeft + nodeRight) / 2;
        int left_son = node * 2;
        int right_son = node * 2 + 1;
        push_down(node);
        if(end <= nodeMid)
            return _range_query(left_son, nodeLeft, nodeMid, start, end);
        else if(nodeMid < start)
            return _range_query(right_son, nodeMid + 1, nodeRight, start, end);
        else
        {
            return max(_range_query(left_son, nodeLeft, nodeMid, start, nodeMid),
                    _range_query(right_son, nodeMid + 1, nodeRight, nodeMid + 1, end));
        }
    }

    void _range_update(int node, int nodeLeft, int nodeRight, int start, int end, int v)
    {
        if(nodeLeft == start && nodeRight == end)
        {
            lazy[node] = v;
            st_vec[node] = v;
            return;
        }
        if(nodeLeft == nodeRight) return;
        int nodeMid = (nodeLeft + nodeRight) / 2;
        int left_son = node * 2;
        int right_son = node * 2 + 1;
        push_down(node);
        if(end <= nodeMid)
            _range_update(left_son, nodeLeft, nodeMid, start, end, v);
        else if(nodeMid < start)
            _range_update(right_son, nodeMid + 1, nodeRight, start, end, v);
        else
        {
            _range_update(left_son, nodeLeft, nodeMid, start, nodeMid, v);
            _range_update(right_son, nodeMid + 1, nodeRight, nodeMid + 1, end, v);
        }
        push_up(node);
    }

    // 懒标记下传
    void push_down(int node)
    {
        if(lazy[node])
        {
            // 节点 node 有 lazy 标记
            int left_son = node * 2;
            int right_son = node * 2 + 1;
            // 如果 lazy = v 的含义是区间内的值都加 v，则是如下写法
            lazy[left_son] = lazy[node]; // 向左子节点传递
            lazy[right_son] = lazy[node]; // 向右子节点传递
            st_vec[left_son] = lazy[node];
            st_vec[right_son] = lazy[node];
            // 如果 lazy = v 的含义是区间内的值都改为 v，则将以上的 += 改为 =
            lazy[node] = 0;
        }
    }

    // 查询结果上传
    void push_up(int node)
    {
        int left_son = node * 2;
        int right_son = node * 2 + 1;
        st_vec[node] = max(st_vec[left_son], st_vec[right_son]);
    }

    void _build(int node, int nodeLeft, int nodeRight, const vector<int>& nums)
    {
        if(nodeLeft == nodeRight)
        {
            st_vec[node] = nums[nodeLeft];
            return;
        }
        int nodeMid = (nodeLeft + nodeRight) / 2;
        int left_son = node * 2;
        int right_son = node * 2 + 1;
        _build(left_son, nodeLeft, nodeMid, nums);
        _build(right_son, nodeMid + 1, nodeRight, nums);
        st_vec[node] = max(st_vec[left_son], st_vec[right_son]);
    }

    vector<int> st_vec; // 节点值表示区间最大值
    vector<int> lazy;
    int n;
};

// ---------------------------------------------------------------------

// 线段树 RMQ 链式写法
// 区间赋值，区间查询
struct STNode
{
    int nodeLeft, nodeRight;
    int maxx;
    STNode *left, *right;
    int lazy;
    STNode(int l, int r, int x, STNode* left=nullptr, STNode* right=nullptr)
        :nodeLeft(l),nodeRight(r),maxx(x),left(left),right(right),lazy(0){}
    ~STNode()
    {
        if(left)
        {
            delete left;
            left = nullptr;
        }
        if(right)
        {
            delete right;
            right = nullptr;
        }
    }
};

class SegmentTree
{
public:
    SegmentTree()
    {
        root = nullptr;
    }

    ~SegmentTree()
    {
        if(root)
        {
            delete root;
            root = nullptr;
        }
    }

    void range_update(int i, int j, int v)
    {
        // cout << "range_update(" << i << "," << j << "," << v << ")" << endl;
        _range_update(root, i, j, v);
    }

    int range_query(int i, int j)
    {
        // cout << "range_query(" << i << "," << j << ")" << endl;
        return _range_query(root, i, j);
    }

    void build(const vector<int>&arr)
    {
        if(arr.empty()) return;
        int n = arr.size();
        root = _build(0, n - 1, arr);
    }

    void traverse()
    {
        cout << "==================" << endl;
        _traverse(root);
        cout << "==================" << endl;
    }

private:
    STNode *root;

    void _traverse(STNode* node)
    {
        // cout << "Range: [";
        // cout << node -> nodeLeft << " , " << node -> nodeRight << "]" << endl;
        // cout << "Max: " << node -> maxx << endl;
        if(node -> nodeLeft != node -> nodeRight)
        {
            _traverse(node -> left);
            _traverse(node -> right);
        }
    }

    // 懒标记下传
    void push_down(STNode* node)
    {
        if(node -> lazy)
        {
            node -> left -> lazy = node -> lazy;
            node -> right -> lazy = node -> lazy;
            node -> left -> maxx = node -> lazy;
            node -> right -> maxx = node -> lazy;
            node -> lazy = 0;
        }
    }

    // 子区间结果上传
    void push_up(STNode* node)
    {
        node -> maxx = max(node -> left -> maxx, node -> right -> maxx);
    }

    int _range_query(STNode* node, int start, int end)
    {
        int nodeLeft = node -> nodeLeft;
        int nodeRight = node -> nodeRight;
        if(nodeLeft == start && nodeRight == end)
            return node -> maxx;
        int nodeMid = (nodeLeft + nodeRight) / 2;
        // 要根据子树结果计算当前节点结果时，懒标记下传
        push_down(node);
        if(end <= nodeMid)
            return _range_query(node -> left, start, end);
        else if(nodeMid < start)
            return _range_query(node -> right, start, end);
        else
        {
            return max(_range_query(node -> left, start, nodeMid),
                    _range_query(node -> right, nodeMid + 1, end));
        }
    }

    void _range_update(STNode* node, int start, int end, int v)
    {
        int nodeLeft = node -> nodeLeft;
        int nodeRight = node -> nodeRight;
        // cout << "_range_update(" << nodeLeft << "," << nodeRight << "," << v << "," << start << "," << end << ")" << endl;
        if(nodeLeft == start && nodeRight == end)
        {
            node -> lazy = v;
            node -> maxx = v;
            return;
        }
        int nodeMid = (nodeLeft + nodeRight) / 2;
        if(nodeLeft == nodeRight) return;
        // cout << nodeLeft << " " << nodeRight << endl;
        // 下传懒标记
        push_down(node);
        if(end <= nodeMid)
        {
            // cout << "end <= nodeMid" << endl;
            _range_update(node -> left, start, end, v);
        }
        else if(nodeMid < start)
        {
            // cout << "nodeMid < start" << endl;
            _range_update(node -> right, start, end, v);
        }
        else
        {
            // cout << "start < nodeMid < end " << endl;
            _range_update(node -> left, start, nodeMid, v);
            _range_update(node -> right, nodeMid + 1, end, v);
        }
        push_up(node);
    }

    STNode* _build(int nodeLeft, int nodeRight, const vector<int>& arr)
    {
        if(nodeLeft == nodeRight)
            return new STNode(nodeLeft, nodeRight, arr[nodeLeft]);
        int nodeMid = (nodeLeft + nodeRight) / 2;
        STNode *left_son = _build(nodeLeft, nodeMid, arr);
        STNode *right_son = _build(nodeMid + 1, nodeRight, arr);
        int maxx = max(left_son -> maxx, right_son -> maxx);
        return new STNode(nodeLeft, nodeRight, maxx, left_son, right_son);
    }
};

// RMQ 树状数组
// 只有单点修改，没有区间修改
class BIT_RMQ
{
public:
    BIT_RMQ():vec(1,0),a(1,0){}
    BIT_RMQ(int n):vec(n + 1, 0),a(n,0){}

    void update(int idx, int x)
    {
        // vec[idx] 管的是 [idx-lowbit[idx] + 1..idx] 这个区间
        // a[idx -  1] 改为 x
        // vec[idx]
        a[idx - 1] = x;
        int n = a.size();
        for(int i = idx; i <= n; i += _lowbit(i))
        {
            vec[i] = x;
            for(int j = 1; j < _lowbit(i); j <<= 1)
            {
                // j < _lowbit(i) <= j - i < _lowbit(i) - i <= i - j > i - _lowbit(i)
                // i = 8，即改 vec[8]
                // 要看 vec[7] = i - 1
                //      vec[6] = i - 2
                //      vec[4] = i - 4
                vec[i] = max(vec[i], vec[i - j]);
            }
        }
    }

    int query(int l, int r)
    {
        // 直接看 vec[r] 不行
        // vec[r] 对应 [r - lowbit[r] + 1, r]
        int ans = a[r - 1];
        while(true)
        {
            ans = max(ans, a[r - 1]);
            if(l == r)
                break;
            --r;
            for(; r - _lowbit(r) >= l; r -= _lowbit(r))
                ans = max(ans, vec[r]);
        }
        return ans;
    }

    void view()
    {
        int n = a.size();
        for(int i = 0; i < n; ++i)
            cout << a[i] << " ";
        cout << endl;
        for(int i = 1; i <= n; ++i)
            cout << vec[i] << " ";
        cout << endl;
    }

private:
    vector<int> vec;
    vector<int> a;

    int _lowbit(int x)
    {
        return x & (-x);
    }
};

// 测试
void test_bit()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; ++i)
        cin >> arr[i];
    cout << "数据: " << endl;
    for(int i = 0; i < n; ++i)
        cout << i << "  " << arr[i] << endl;
    BIT_RMQ rmq(n);
    for(int i = 0; i < n; ++i)
        rmq.update(i + 1, arr[i]);
    rmq.view();
    while(true)
    {
        char op;
        cin >> op;
        if(op == 'c')
        {
            int idx, x;
            cin >> idx >> x;
            cout << "修改单点: [" << idx << ": " << x << "]" << endl;
            rmq.update(idx + 1, x);
        }
        else
        {
            int start, end;
            cin >> start >> end;
            cout << "查询区间: [" << start << ", " << end << "], 最大值：";
            cout << rmq.query(start + 1, end + 1) << endl;
        }
    }
}

void test_block()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; ++i)
        cin >> arr[i];
    cout << "数据: " << endl;
    for(int i = 0; i < n; ++i)
        cout << i << "  " << arr[i] << endl;
    Block rmq;
    rmq.build(arr);
    while(true)
    {
        char op;
        cin >> op;
        if(op == 'c')
        {
            int s, e, x;
            cin >> s >> e >> x;
            cout << "修改区间: [" << s << ", " << e << ", " << x << "]" << endl;
            rmq.range_update(s, e, x);
            for(int i = 0; i < n; ++i)
                cout << i << "  " << rmq.nums[i] << endl;
        }
        else if(op == 'a')
        {
            int idx, x;
            cin >> idx >> x;
            cout << "修改单点: [" << idx << ", " << x << "]" << endl;
            rmq.point_update(idx, x);
            for(int i = 0; i < n; ++i)
                cout << i << "  " << rmq.nums[i] << endl;
        }
        else
        {
            int start, end;
            cin >> start >> end;
            cout << "查询区间: [" << start << ", " << end << "], 最大值：";
            cout << rmq.range_query(start, end) << endl;
        }
    }
}


int main()
{
    // test_block();
    test_bit();
};
