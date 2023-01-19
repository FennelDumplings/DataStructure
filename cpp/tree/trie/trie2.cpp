#include <unordered_map>

using namespace std;

/*
 * 子节点用 unordered_map 实现
 */

struct TrieNode
{
    bool terminal;
    unordered_map<char, TrieNode*> children;
    TrieNode()
    {
        terminal = false;
        children = unordered_map<char, TrieNode*>();
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
            if((iter -> children).count(ch) == 0)
                (iter -> children)[ch] = new TrieNode();
            iter = (iter -> children)[ch];
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
        auto it = (node -> children).begin();
        while(it != (node -> children).end())
        {
            TrieNode *child = it -> second;
            if(child)
                delete_sub_tree(child);
            delete child;
            child = nullptr;
            ++it;
        }
    }

    const TrieNode* find(const string& prefix) const
    {
        TrieNode* iter = root;
        for(const char c: prefix)
        {
            if((iter -> children).count(c) == 0)
                return nullptr;
            iter = (iter -> children)[c];
        }
        return iter;
    }
};

