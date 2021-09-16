struct TrieNode
{
    bool terminate;
    vector<TrieNode*> children;
    TrieNode()
    {
        terminate = false;
        children = vector<TrieNode*>(ALPHABETS, nullptr);
    }
    ~TrieNode(){}
};

class Trie
{
private:
    void delete_sub_tree(TrieNode* node)
    {
        for(TrieNode *child: node -> children)
        {
            if(child)
                delete_sub_tree(child);
            delete child;
            child = nullptr;
        }
    }

public:
    Trie()
    {
        root = new TrieNode();
    }

    ~Trie()
    {
        if(root)
            delete_sub_tree(root);
        delete root;
        root = nullptr;
    }

    void insert(const string& word)
    {
        TrieNode *iter = root;
        for(const char& ch: word)
        {
            TrieNode *&nxt = (iter -> children)[ch - 'a'];
            if(!nxt)
                nxt = new TrieNode();
            iter = nxt;
        }
        iter -> terminate = true;
    }

private:
    TrieNode *root;
};

