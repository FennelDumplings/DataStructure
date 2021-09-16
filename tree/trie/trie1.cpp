#include <vector>

using namespace std;

/*
 * 子节点用 vector 实现
 */

const int ALPHABETS = 26;

struct TrieNode
{
    bool terminal;
    vector<TrieNode*> children;
    TrieNode()
    {
        terminal = false;
        children = vector<TrieNode*>(ALPHABETS, nullptr);
    }
    ~TrieNode(){}
};

class Trie
{
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
            TrieNode *&nxt = ;
            if(!(iter -> children)[ch - 'a'])
                (iter -> children)[ch - 'a'] = new TrieNode();
            iter = (iter -> children)[ch - 'a'];
        }
        iter -> terminal = true;
    }

    bool search(string word)
    {
        const TrieNode* iter = find(word);
        return iter && iter -> terminal;
    }

    bool startsWith(string prefix)
    {
        return find(prefix) != nullptr;
    }

private:
    TrieNode *root;

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

    const TrieNode* find(const string& prefix) const
    {
        const TrieNode* iter = root;
        for(const char c: prefix)
        {
            iter = (iter -> children)[c - 'a'];
            if(iter == nullptr) break;
        }
        return iter;
    }
};
