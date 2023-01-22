
#include <string>
#include <vector>
#include <climits>
#include <unordered_map>
#include <iostream>
#include <queue>
#include <functional>

using namespace std;

using HFType = char;

struct HFNode
{
    HFType data;
    int weight;
    int parent, left, right;
    bool operator<(const HFNode& node) const
    {
        return this -> weight < node.weight;
    }
};

struct HFCode
{
    HFType data;
    string code;
};

using PHI = pair<HFNode, int>;

class HuffmanTree
{
public:
    HuffmanTree(){}
    ~HuffmanTree(){}

    void build(const vector<HFType>& v, const vector<int>& w)
    {
        int size = v.size();
        length = 2 * size;
        // 节点共 size * 2 - 1 个，放在 elem[1..2*size-1] 中
        elem = vector<HFNode>(length);

        // size 个叶子节点放在 elem[size..2*size-1]
        priority_queue<PHI, vector<PHI>, greater<PHI>> pq; // 小顶堆
        for(int i = size; i < length; i++)
        {
            elem[i].weight = w[i - size];
            elem[i].data = v[i - size];
            elem[i].parent = elem[i].left = elem[i].right = 0;
            pq.push(PHI(elem[i], i));
        }

        // size - 1 个非叶子节点: elem[1..size-1]
        for(int i = size - 1; i > 0; i--)
        {
            PHI node1 = pq.top();
            pq.pop();
            PHI node2 = pq.top();
            pq.pop();
            int min1 = node1.first.weight;
            int min2 = node2.first.weight;
            int y = node1.second;
            int x = node2.second;
            elem[i].weight = min1 + min2;
            elem[i].left = x;
            elem[i].right = y;
            elem[i].parent = 0;
            elem[x].parent = i;
            elem[y].parent = i;
            pq.push(PHI(elem[i], i));
        }
    }

    vector<HFCode> get_code()
    {
        int n_leaf = length / 2; // 叶节点个数
        vector<HFCode> result(n_leaf);
        int p, s;
        // [n_leaf..length - 1] 为 elem 中的 n_leaf 个叶节点
        for(int i = n_leaf; i < length; i++)
        {
            result[i - n_leaf].data = elem[i].data;
            result[i - n_leaf].code = "";
            p = elem[i].parent;
            s = i;
            while(p)
            {
                if(elem[p].left == s)
                    result[i - n_leaf].code = '0' + result[i - n_leaf].code;
                else
                    result[i - n_leaf].code = '1' + result[i - n_leaf].code;
                s = p;
                p = elem[p].parent;
            }
        }
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

    vector<HFType> decode(const string& seq)
    {
        vector<HFType> data;
        int n = seq.size();
        int iter = 0;
        while(iter < n)
        {
            int node = 1; // 根节点是 1
            while(elem[node].left != 0)
            {
                if(seq[iter] == '0')
                    node = elem[node].left;
                else
                    node = elem[node].right;
                ++iter;
            }
            data.push_back(elem[node].data);
        }
        return data;
    }

private:
    vector<HFNode> elem;
    int length;
};


int main()
{
    string data;
    cout << "数据： " << endl;
    cin >> data;
    int n = data.size();
    cout << "数据长度： " << n << endl;
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
    hftree.build(v, w);

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
}
