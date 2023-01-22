#include <vector>

using namespace std;

// 线段树模板写法, 不带插入删除
struct STNode {
    int start;
    int end;
    int sum;
    STNode *left;
    STNode *right;
    STNode(){}
    STNode(int start, int end, int sum)
        :start(start),end(end),sum(sum),left(nullptr),right(nullptr){}
    STNode(int start, int end, int sum, STNode *left, STNode *right)
        :start(start),end(end),sum(sum),left(left),right(right){}
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

class SegmentTree {
public:
    SegmentTree(){
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

    void build(int start, int end, const vector<int>& vals)
    {
        if(end >= start)
            root = _build(start, end, vals);
    }

    void point_update(int index, int val)
    {
        _point_update(root, index, val);
    }

    int range_query(int i, int j)
    {
        return _range_query(root, i, j);
    }

private:
    STNode *root;

    STNode* _build(int start, int end, const vector<int>& vals)
    {
        if(start == end)
            return new STNode(start, end, vals[start]);
        int mid = start + (end - start) / 2;
        STNode *left = _build(start, mid, vals);
        STNode *right = _build(mid + 1, end, vals);
        return new STNode(start, end, left -> sum + right -> sum, left, right);
    }

    void _point_update(STNode *root, int index, int val)
    {
        if(root -> start == root -> end && root -> end == index)
        {
            root -> sum = val;
            return;
        }
        int mid = root -> start + (root -> end - root -> start) / 2;
        if(index <= mid) // 更新位置在左子树
        {
            _point_update(root -> left, index, val);
        }
        else
        {
            _point_update(root -> right, index, val);
        }
        root -> sum = root -> left -> sum + root -> right -> sum;
    }

    int _range_query(STNode *root, int i, int j)
    {
        if(root -> start == i && root -> end == j)
            return root -> sum;
        int mid = root -> start + (root -> end - root -> start) / 2;
        if(j <= mid) // 查询的区间在左子树
            return _range_query(root -> left, i, j);
        else if(i > mid) // 查询的区间在右子树
            return _range_query(root -> right, i, j);
        else
            return _range_query(root -> left, i, mid) + _range_query(root -> right, mid + 1, j);
    }
};

