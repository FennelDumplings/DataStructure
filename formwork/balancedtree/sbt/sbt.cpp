
struct SBTNode
{
    int data;
    SBTNode *left;
    SBTNode *right;
    int size;
    SBTNode():left(nullptr),right(nullptr){}
    SBTNode(const int& x, SBTNode* p=nullptr, SBTNode* q=nullptr, int s=1):data(x),left(p),right(q),size(s){}
    ~SBTNode()
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

class SizeBalancedTree
{
public:
    SizeBalancedTree():root(nullptr){}
    ~SizeBalancedTree()
    {
        if(root)
        {
            delete root;
            root = nullptr;
        }
    }

    bool find(const int& x) const
    {
        return find(x, root);
    }

    void insert(const int& x)
    {
        insert(x, root);
    }

    void remove(const int& x)
    {
        int v = remove(x, root);
        if(x != v)
            insert(v, root);
    }

    int lessthan(const int& x) const
    {
        return lessthan(x, root);
    }

private:
    SBTNode *root;

    int lessthan(const int& x, SBTNode* t) const;
    void insert(const int& x, SBTNode*& t);
    int remove(const int& x, SBTNode*& t);
    SBTNode* find(const int& x, SBTNode* t) const;
    void maintain(SBTNode*& t);
    void maintain(SBTNode*& t, bool flag);

    void left_rotate(SBTNode*& t)
    {
        // 调用方保证 t -> right 存在
        SBTNode *tmp = t -> right;
        t -> right = tmp -> left;
        tmp -> left = t;
        tmp -> size = t -> size;
        t -> size = 1;
        if(t -> right)
            t -> size += t -> right -> size;
        if(t -> left)
            t -> size += t -> left -> size;
        t = tmp;
    }

    void right_rotate(SBTNode*& t)
    {
        // 调用方保证 t -> left 存在
        SBTNode *tmp = t -> left;
        t -> left = tmp -> right;
        tmp -> right = t;
        tmp -> size = t -> size;
        t -> size = 1;
        if(t -> right)
            t -> size += t -> right -> size;
        if(t -> left)
            t -> size += t -> left -> size;
        t = tmp;
    }
};

void SizeBalancedTree::maintain(SBTNode*& t)
{
    if((t -> left && t -> left -> left) && (!t -> right || t -> left -> left -> size > t -> right -> size))
    {
        right_rotate(t);
        maintain(t -> right);
        maintain(t);
        return;
    }
    if((t -> left && t -> left -> right) && (!t -> right || t -> left -> right -> size > t -> right -> size))
    {
        left_rotate(t -> left);
        right_rotate(t);
        maintain(t -> left);
        maintain(t -> right);
        maintain(t);
        return;
    }
    if((t -> right && t -> right -> right) && (!t -> left || t -> right -> right -> size > t -> left -> size))
    {
        left_rotate(t);
        maintain(t -> left);
        maintain(t);
        return;
    }
    if((t -> right && t -> right -> left) && (!t -> left || t -> right -> left -> size > t -> left -> size))
    {
        right_rotate(t -> right);
        left_rotate(t);
        maintain(t -> left);
        maintain(t -> right);
        maintain(t);
    }
}

void SizeBalancedTree::maintain(SBTNode*& t, bool flag)
{
    if(!flag)
    {
        if((t -> left && t -> left -> left) && (!t -> right || t -> left -> left -> size > t -> right -> size))
        {
            right_rotate(t);
        }
        else
        {
            if((t -> left && t -> left -> right) && (!t -> right || t -> left -> right -> size > t -> right -> size))
            {
                left_rotate(t -> left);
                right_rotate(t);
            }
            else
                return;
        }
    }
    else
    {
        if((t -> right && t -> right -> right) && (!t -> left || t -> right -> right -> size > t -> left -> size))
        {
            left_rotate(t);
        }
        else
        {
            if((t -> right && t -> right -> left) && (!t -> left || t -> right -> left -> size > t -> left -> size))
            {
                right_rotate(t -> right);
                left_rotate(t);
            }
            else
                return;
        }
    }
    maintain(t -> left, false);
    maintain(t -> right, true);
    maintain(t, false);
    maintain(t, true);
}

int SizeBalancedTree::lessthan(const int& x, SBTNode* t) const
{
    if(t -> data >= x)
    {
        if(!t -> left)
            return 0;
        return lessthan(x, t -> left);
    }
    // t -> data < x
    int ans = 1;
    if(t -> left)
        ans += t -> left -> size;
    if(t -> right)
        ans += lessthan(x, t -> right);
    return ans;
}

SBTNode* SizeBalancedTree::find(const int& x, SBTNode* t) const
{
    if(t == nullptr) return nullptr;
    else if(t -> data > x) return find(x, t -> left);
    else if(t -> data < x) return find(x, t -> right);
    else return t;
}

void SizeBalancedTree::insert(const int& x, SBTNode*& t)
{
    if(t == nullptr)
    {
        t = new SBTNode(x, nullptr, nullptr, 1);
        return;
    }
    ++(t -> size);
    if(t -> data > x)
        insert(x, t -> left);
    else
        insert(x, t -> right);
    // maintain(t);
    maintain(t, x >= t -> data);
}

int SizeBalancedTree::remove(const int& x, SBTNode*& t)
{
    --(t -> size);
    int deleted;
    if(x == t -> data || (x < t -> data && !t -> left) || (x > t -> data && !t -> right))
    {
        deleted = t -> data;
        if(!t -> left || !t -> right)
        {
            if(!t -> left && !t -> right)
            {
                delete t;
                t = nullptr;
            }
            else
            {
                SBTNode *tmp = t;
                if(tmp -> left)
                {
                    // tmp -> left = nullptr; 必须加上
                    // 否则 tmp 被 delete 时，tmp -> left 也一并被 delete
                    t = tmp -> left;
                    tmp -> left = nullptr;
                }
                else
                {
                    t = tmp -> right;
                    tmp -> right = nullptr;
                }
                delete tmp;
                tmp = nullptr;
            }
        }
        else
        {
            // t -> left 一定均比 deleted + 1 小
            t -> data = remove(deleted + 1, t -> left);
        }
    }
    else
    {
        if(x < t -> data)
            deleted = remove(x, t -> left);
        else
            deleted = remove(x, t -> right);
    }
    if(t)
        maintain(t);
    return deleted;
}

