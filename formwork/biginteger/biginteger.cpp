#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>
#include <climits>

using namespace std;

using ll = long long;

struct BigInteger
{
    static const int BASE = 10;
    static const int WIDTH = 1;
    // s 保存大整数各个数位
    // 原数 1234 => s=[4,3,2,1]
    // 进制数为 BASE
    // s[i] 中保存的位数
    vector<int> s;

    // 基本功能
    void show()
    {
        for(int i: s) cout << i << " ";
        cout << endl;
    }

    // 去掉大数的前导0
    void clean()
    {
        while(!s.empty() && s.back() == 0)
            s.pop_back();
    }

    BigInteger(ll num = 0) // 构造函数
    {
        *this = num;
    }

    BigInteger operator=(ll num) // 赋值运算符
    {
        s.clear();
        do
        {
            s.push_back(num % BASE);
            num /= BASE;
        }while(num > 0);
        return *this;
    }

    BigInteger operator=(const string& str) // 赋值运算符
    {
        s.clear();
        int len = (str.length() - 1) / WIDTH + 1;
        int x;
        for(int i = 0; i < len; ++i)
        {
            int end = str.length() - i * WIDTH;
            int start = max(0, end - WIDTH);
            sscanf(str.substr(start, end - start).c_str(), "%d", &x);
            s.push_back(x);
        }
        return *this;
    }

    // 加减乘
    BigInteger operator+(const BigInteger& b) const;
    BigInteger operator-(const BigInteger& b) const;
    BigInteger operator*(const BigInteger& b) const;
    BigInteger operator+=(const BigInteger& b)    // +=运算符
    {
        *this = *this + b;
        return *this;
    }
    BigInteger operator-=(const BigInteger& b)    // -=运算符
    {
        *this = *this - b;
        return *this;
    }
    BigInteger operator*=(const BigInteger& b)    // *=运算符
    {
        *this = *this * b;
        return *this;
    }

    // 大数对小数除法和取模
    BigInteger operator/(const ll& b) const
    {
        // 大数除小数
        BigInteger c;
        c.s.clear();
        c.s.assign((int)s.size(), 0);
        int carry = 0; // 高位未除尽的部分
        for(int i = (int)s.size() - 1; i >= 0; --i)
        {
            c.s[i] = (s[i] + carry * BASE) / b;
            carry = s[i] + carry * BASE - c.s[i] * b;
        }
        c.clean();
        return c;
    }
    BigInteger operator%(const ll& b) const
    {
        long long ans = 0, lena = s.size();
        for(int i = lena - 1; i >= 0; --i)
        {
            ans = (ans * BASE + s[i]) % b;
        }
        return ans;
    }
    BigInteger operator/=(const long long& b) // /=运算符
    {
        *this = *this / b;
        return *this;
    }
    BigInteger operator%=(const ll& b) // %=运算符
    {
        *this = *this % b;
        return *this;
    }

    // 大数对大数除法和取模
    BigInteger operator/(const BigInteger& b) const;
    BigInteger operator%(const BigInteger& b) const;
    BigInteger operator/=(const BigInteger& b)  // /=运算符
    {
        *this = *this / b;
        return *this;
    }
    BigInteger operator %= (const BigInteger& b)    // %=运算符
    {
        *this = *this % b;
        return *this;
    }

    // 比较
    bool operator < (const BigInteger& b) const    // <运算符
    {
        if(s.size()!=b.s.size()) return s.size()<b.s.size();
        for(int i=s.size()-1;i>=0;i--)
            if(s[i]!=b.s[i]) return s[i]<b.s[i];
        return false;
    }
    bool operator > (const BigInteger& b) const    // >运算符
    {
        return b < *this;
    }
    bool operator <= (const BigInteger& b) const   // <=运算符
    {
        return !(b < *this);
    }
    bool operator >= (const BigInteger& b) const   // >=运算符
    {
        return !(*this < b);
    }
    bool operator != (const BigInteger& b) const   // !=运算符
    {
        return b < *this || *this < b;
    }
    bool operator == (const BigInteger& b) const   // ==运算符
    {
        return !(b < *this) && !(*this < b);
    }
};

ostream& operator<<(ostream& out, const BigInteger& x)
{
    out << x.s.back();
    for(int i = x.s.size() - 2; i >= 0; --i)
    {
        string tmp = to_string(x.s[i]);
        string buf(BigInteger::WIDTH - tmp.size(), 0);
        buf += tmp;
        for(int j = 0; j < (int)buf.size(); ++j)
            out << buf[j];
    }
    return out;
}

istream& operator>>(istream& in, BigInteger& x)
{
    string s;
    if(!(in >> s))
        return in;
    x = s;
    return in;
}


BigInteger BigInteger::operator+(const BigInteger& b) const
{
    BigInteger c;
    c.s.clear();
    int iter = 0;
    int carry = 0;
    while(iter < (int)s.size() || iter < (int)b.s.size() || carry != 0)
    {
        int x = carry;
        if(iter < (int)s.size())
            x += s[iter];
        if(iter < (int)b.s.size())
            x += b.s[iter];
        c.s.push_back(x % BASE);
        carry = x / BASE;
        ++iter;
    }
    return c;
}

BigInteger BigInteger::operator-(const BigInteger& b) const
{
    // 大数减小数
    BigInteger c;
    c.s.clear();
    int iter = 0;
    int carry = 0;
    while(iter < (int)s.size() || iter < (int)b.s.size() || carry != 0)
    {
        int x = carry;
        carry = 0;
        if(iter < (int)s.size())
            x += s[iter];
        if(iter < (int)b.s.size())
            x -= b.s[iter];
        if(x < 0)
        {
            x += BASE;
            carry = -1;
        }
        c.s.push_back(x);
        ++iter;
    }
    c.clean();
    return c;
}

BigInteger BigInteger::operator*(const BigInteger& b) const
{
    BigInteger c;
    int lena = s.size(), lenb = b.s.size(), lenc = lena + lenb;
    c.s.clear();
    c.s.assign(lenc, 0);
    for(int i = 0; i < lena; ++i)
    {
        for(int j = 0; j < lenb; ++j)
        {
            c.s[i + j] += s[i] * b.s[j];
        }
    }
    for(int i = 0; i < lenc - 1; ++i)
    {
        c.s[i + 1] += c.s[i] / BASE;
        c.s[i] %= BASE;
    }
    c.clean();
    return c;
}

BigInteger BigInteger::operator/(const BigInteger& b) const
{
    BigInteger c;
    c.s.clear();
    c.s.assign((int)s.size(), 0);
    BigInteger carry;
    carry = 0; // 高位未除尽的部分
    for(int i = (int)s.size() - 1; i >= 0; --i)
    {
        carry = carry * BASE + s[i];
        int j = 0;
        // 求 b * j <= carry 的最大 j
        while(j < BASE)
        {
            if(carry < b * (j + 1))
                break;
            ++j;
        }
        c.s[i] = j;
        carry = carry - b * j;
    }
    c.clean();
    return c;
}

BigInteger BigInteger::operator%(const BigInteger& b) const
{
    BigInteger carry = 0;
    for(int i = (int)s.size() - 1; i >= 0; --i)
    {
        carry = carry * BASE + s[i];
        int j = 0;
        while(j < BASE)
        {
            if(carry < b * (j + 1))
                break;
            ++j;
        }
        carry = carry - b * j;
    }
    return carry;
}


int main()
{
    BigInteger b1, b2;
    cin >> b1 >> b2;
    b1.show();
    b2.show();
    cout << "+ " << b1 + b2 << endl;
    cout << "- " << b1 - b2 << endl;
    cout << "* " << b1 * b2 << endl;
    cout << "/ " << b1 / b2 << endl;
    cout << "% " << b1 % b2 << endl;
}
