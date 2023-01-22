

struct BSTNode
{
    int data;
    BSTNode *left;
    BSTNode *right;
    BSTNode():left(nullptr),right(nullptr){}
    BSTNode(const int &x, BSTNode *p=nullptr, BSTNode *q=nullptr):data(x),left(p),right(q){}
    ~BSTNode()
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


class BinarySearchTree
{
public:
    BinarySearchTree():root(nullptr){}
    ~BinarySearchTree()
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
        remove(x, root);
    }

private:
    BSTNode *root;

    void insert(const int& x, BSTNode*& t);
    void remove(const int& x, BSTNode*& t);
    BSTNode* find(const int& x, BSTNode* t) const;
};


void BinarySearchTree::insert(const int& x, BSTNode*& t)
{
    if(t == nullptr)
        t = new BSTNode(x, nullptr, nullptr);
    else if(t -> data > x)
        insert(x, t -> left);
    else
        insert(x, t -> right);
}

void BinarySearchTree::remove(const int& x, BSTNode*& t)
{
    if(t == nullptr) return;
    if(x < t -> data)
        remove(x, t -> left);
    if(x > t -> data)
        remove(x, t -> right);
    if(x == t -> data)
    {
        if(t -> left != nullptr && t -> right != nullptr)
        {
            BSTNode *tmp = t -> right;
            while(tmp -> left != nullptr)
                tmp = tmp -> left;
            t -> data = tmp -> data;
            remove(t -> data, t -> right);
        }
        else
        {
            BSTNode *oldNode = t;
            t = (t -> left != nullptr) ? t -> left : t -> right;
            delete oldNode;
        }
    }
}


BSTNode* BinarySearchTree::find(const int& x, BSTNode* t) const
{
    if(t == nullptr) return nullptr;
    else if(t -> data > x) return find(x, t -> left);
    else if(t -> data < x) return find(x, t -> right);
    else return t;
}
