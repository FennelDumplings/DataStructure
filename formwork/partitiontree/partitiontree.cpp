#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

struct PTNode
{
    int start, end;
    vector<int> nums, toleft;
    PTNode *left, *right;
    PTNode(int s, int e, PTNode* l=nullptr, PTNode* r=nullptr)
        :start(s),end(e),nums(vector<int>(end - start + 1)),toleft(vector<int>(end - start + 2)),left(l),right(r) {}
    ~PTNode()
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

class PartitionTree
{
public:
    PartitionTree()
    {
        root = nullptr;
        sorted = vector<int>();
    }

    ~PartitionTree()
    {
        if(root)
        {
            delete root;
            root = nullptr;
        }
    }

    void build(int start, int end, const vector<int>& nums)
    {
        sorted = nums;
        sort(sorted.begin(), sorted.end());
        root = new PTNode(start, end);
        root -> nums = nums;
        _build(root);
    }

    int query(int i, int j, int k)
    {
        if(i > j) return 0;
        return _query(root, i, j, k);
    }

    void traverse()
    {
        queue<PTNode*> q;
        q.push(root);
        vector<PTNode*> level_nodes;
        while(!q.empty())
        {
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            for(PTNode *cur: level_nodes)
            {
                if(!cur)
                {
                    cout << "[  ] ";
                    continue;
                }
                cout << "[ ";
                for(int num: (cur -> nums)) cout << num << " ";
                cout << "] ";
                q.push(cur -> left);
                q.push(cur -> right);
            }
            cout << endl;
        }
    }


private:
    PTNode *root;
    vector<int> sorted;

    int _query(PTNode* root, int i, int j, int k)
    {
        cout << "----------" << endl;
        for(int i: root -> nums) cout << i << " ";
        cout << endl;
        if(root -> start == root -> end) return (root -> nums)[0];

        int tli = 0;
        if(root -> start != i)
            tli = (root -> toleft)[i - root -> start];
        int tlj = (root -> toleft)[j - root -> start + 1];
        int tl = tlj - tli;
        cout << i << " " << j << " " << root -> start << endl;
        cout << tli << " " << tlj << " " << tl << endl;
        int new_i, new_j;
        if(tl >= k)
        {
            // 第 k 大在左子
            new_i = root -> start + tli;
            new_j = new_i + tl - 1;
            return _query(root -> left, new_i, new_j, k);
        }
        else
        {
            // 第 k 大在右子
            int mid = root -> start + (root -> end - root -> start) / 2;
            new_i = mid + 1 + i - (root -> start) - tli;
            new_j = new_i + j - i - tl;
            return _query(root -> right, new_i, new_j, k - tl);
        }
    }

    void _build(PTNode* root)
    {
        if(root -> start == root -> end)
            return;
        int mid = root -> start + (root -> end - root -> start) / 2;
        int median =  sorted[mid];
        PTNode *left = new PTNode(root -> start, mid);
        PTNode *right = new PTNode(mid + 1, root -> end);
        int n = (root -> nums).size();
        int median_to_left = mid - root -> start + 1;
        for(int i = 0; i < n; ++i)
        {
            if((root -> nums)[i] < median)
                --median_to_left;
        }
        // 出循环后 median_to_left 为去往左子树中等于中位数的个数
        int to_left = 0; // 去往左子树的个数
        int idx_left = 0, idx_right = 0;
        for(int i = 0; i < n; ++i)
        {
            int cur = (root -> nums)[i];
            if(cur < median || ((cur == median) && median_to_left > 0))
            {
                (left -> nums)[idx_left] = cur;
                ++idx_left;
                ++to_left;
                if(cur == median)
                    --median_to_left;
            }
            else
            {
                (right -> nums)[idx_right] = cur;
                ++idx_right;
            }
            (root -> toleft)[i + 1] = to_left;
        }
        _build(left);
        _build(right);
        root -> left = left;
        root -> right = right;
    }
};

int main()
{
    vector<int> nums({5, 2, 6, 1});
    PartitionTree partitiontree;
    int n = nums.size();
    partitiontree.build(0, n - 1, nums);
    partitiontree.traverse();
    while(true)
    {
        int i, j, k;
        cin >> i >> j >> k;
        int ans = partitiontree.query(i, j, k);
        cout << "--: " << ans << endl;
    }
}
