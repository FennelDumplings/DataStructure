
#include <string>
#include <vector>
#include <climits>
#include <unordered_map>
#include <iostream>
#include <queue>
#include <functional>

using namespace std;

using HFType = char;
const HFType PLACEHOLDER = '#';

struct HFNode
{
    HFType data;
    int weight;
    HFNode *parent;
    vector<HFNode*> children;
    HFNode(int k, const HFType& v, int w)
    {
        children = vector<HFNode*>(k, nullptr);
        data = v;
        weight = w;
    }
};

struct HFCode
{
    HFType data;
    string code;
};

struct HeapCmp
{
    bool operator()(HFNode*& node1, HFNode*& node2) const
    {
        return node1 -> weight > node2 -> weight;
    }
};

class HuffmanTree
{
private:
    void delete_sub_tree(HFNode* node)
    {
        if(!node) return;
        for(HFNode *child: node -> children)
            if(child)
                delete_sub_tree(child);
        delete node;
        node = nullptr;
    }

public:
    HuffmanTree(){}
    ~HuffmanTree()
    {
        delete_sub_tree(root);
    }

    void build(const vector<HFType>& v, const vector<int>& w, int K)
    {
        this -> n = v.size();
        this -> k = K;
        // n 个叶子节点
        priority_queue<HFNode*, vector<HFNode*>, HeapCmp> pq; // 小顶堆
        for(int i = 0; i < n; ++i)
        {
            HFNode *node = new HFNode(k, v[i], w[i]);
            pq.push(node);
        }
        // 如果有必要，加 m 个虚节点
        if((n - 1) % (k - 1) != 0)
        {
            int m = k - ((n - 1) % (k - 1)) - 1;
            for(int i = 0; i < m; ++i)
            {
                HFNode *node = new HFNode(k, PLACEHOLDER, 0);
                pq.push(node);
            }
        }

        while((int)pq.size() > 1)
        {
            HFNode *fa = new HFNode(k, PLACEHOLDER, 0);
            for(int j = 0; j < k; ++j)
            {
                HFNode *node = pq.top();
                pq.pop();
                fa -> weight += node -> weight;
                (fa -> children)[j] = node;
                node -> parent = fa;
            }
            pq.push(fa);
        }
        root = pq.top();
    }

private:
    void dfs(HFNode *node, vector<HFCode>& hfcodes, string& code)
    {
        if(!(node -> children)[0])
        {
            hfcodes.push_back(HFCode());
            hfcodes.back().data = node -> data;
            hfcodes.back().code = code;
            return;
        }
        for(int i = 0; i < k; ++i)
        {
            HFNode *child = (node -> children)[i];
            if(child)
            {
                code += '0' + i;
                dfs(child, hfcodes, code);
                code.pop_back();
            }
        }
    }

public:
    vector<HFCode> get_code()
    {
        vector<HFCode> result;
        string code;
        dfs(root, result, code);
        return result;
    }

    string encode(const vector<HFType>& data)
    {
        vector<HFCode> hfcode = get_code();
        string result;
        for(const HFType &item: data)
        {
            for(const HFCode &code_info: hfcode)
                if(code_info.data == item)
                    result += code_info.code;
        }
        return result;
    }

private:
    HFType _decode(HFNode* node, const string& seq, int& iter)
    {
        while((node -> children)[0])
        {
            node = (node -> children)[seq[iter] - '0'];
            ++iter;
        }
        return node -> data;
    }

public:
    vector<HFType> decode(const string& seq)
    {
        vector<HFType> result;
        int n_seq = seq.size();
        int iter = 0;
        while(iter < n_seq)
        {
            HFNode *node = root;
            HFType data = _decode(node, seq, iter);
            result.push_back(data);
        }
        return result;
    }

private:
    HFNode *root;
    int k; // 字符集大小
    int n; // 叶节点个数
};


int main()
{
    string data;
    cout << "数据： " << endl;
    cin >> data;
    int n = data.size();
    cout << "数据长度： " << n << endl;
    cout << "字符集长度： ";
    int k;
    cin >> k;
    // 统计字符和频率
    unordered_map<int, int> mapping;
    for(const char& ch: data)
        ++mapping[ch];
    vector<char> v;
    vector<int> w;
    for(const auto &item: mapping)
    {
        v.push_back(item.first);
        w.push_back(item.second);
    }
    int m = v.size();
    cout << "字符数： " << m << endl;
    cout << "(字符，频率)： " << endl;
    for(int i = 0; i < m; ++i)
        cout << v[i] << " " << w[i] << endl;
    HuffmanTree hftree;
    hftree.build(v, w, k);

    cout << "build done" << endl;

    vector<HFCode> result = hftree.get_code();
    cout << endl;
    cout << "编码结果： " << endl;
    for(int i = 0; i < (int)result.size(); ++i)
    {
        HFCode cur = result[i];
        cout << cur.data << " : " << cur.code << endl;
    }

    cout << "原数据的编码序列: " << endl;
    string seq = hftree.encode(vector<HFType>(data.begin(), data.end()));
    cout << seq << endl;
    cout << "解码结果: " << endl;
    vector<HFType> d_seq = hftree.decode(seq);
    cout << string(d_seq.begin(), d_seq.end()) << endl;
    while(true)
    {
        string s;
        cin >> s;
        cout << "---" << endl;
        string seq = hftree.encode(vector<HFType>(s.begin(), s.end()));
        cout << seq << endl;
        cout << "===" << endl;
        vector<HFType> d_seq = hftree.decode(seq);
        cout << string(d_seq.begin(), d_seq.end()) << endl;
    }
}
