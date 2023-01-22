#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// 区间查询 > x 的数
struct MTNode
{
    int start, end;
    vector<int> data;
    MTNode *left, *right;
    MTNode(int s, int e, const vector<int>& nums, MTNode* l=nullptr, MTNode* r=nullptr)
        :start(s),end(e),data(nums),left(l),right(r) {}
    ~MTNode()
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

class MergeTree
{
public:
    MergeTree()
    {
        root = nullptr;
    }

    ~MergeTree()
    {
        if(root)
        {
            delete root;
            root = nullptr;
        }
    }

    void build(int start, int end, const vector<int>& nums)
    {
        root = _build(start, end, nums);
    }

    int query(int i, int j, int k)
    {
        if(i > j) return 0;
        int result = 0;
        _query(root, i, j, k, result);
        return result;
    }

private:
    MTNode *root;

    void _query(MTNode* root, int i, int j, int k, int& result)
    {
        if(root -> start == i && root -> end == j)
        {
            auto pos = upper_bound((root -> data).begin(), (root -> data).end(), k);
            result += (root -> data).end() - pos;
            return;
        }
        int mid = root -> start + (root -> end - root -> start) / 2;
        if(j <= mid)
        {
            _query(root -> left, i, j, k, result);
            return;
        }
        if(i > mid)
        {
            _query(root -> right, i, j, k, result);
            return;
        }
        _query(root -> left, i, mid, k, result);
        _query(root -> right, mid + 1, j, k, result);
    }

    MTNode* _build(int start, int end, const vector<int>& nums)
    {
        if(start == end)
        {
            return new MTNode(start, end, vector<int>({nums[start]}));
        }
        int mid = start + (end - start) / 2;
        MTNode *left = _build(start, mid, nums);
        MTNode *right = _build(mid + 1, end, nums);
        vector<int> merged((left -> data).size() + (right -> data).size());
        merge((left -> data).begin(), (left -> data).end(), (right -> data).begin(), (right -> data).end(), merged.begin());
        MTNode *cur = new MTNode(start, end, merged, left, right);
        return cur;
    }
};

int main()
{
    vector<int> nums(20);
    for(int i = 0; i < (int)nums.size(); ++i) nums[i] = i;
    for(int num: nums) cout << num << " ";
    cout << endl;
    random_shuffle(nums.begin(), nums.end());
    for(int num: nums) cout << num << " ";
    cout << endl;
    MergeTree mergetree;
    mergetree.build(0, (int)nums.size() - 1, nums);
    while(true)
    {
        int i, j, k;
        cin >> i >> j >> k;
        cout << mergetree.query(i, j, k) << endl;
    }
}
