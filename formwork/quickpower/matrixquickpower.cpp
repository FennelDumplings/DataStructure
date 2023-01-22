
#include <cstring>
#include <iostream>

using namespace std;

using ll = long long;
const int M = 2;

struct Ma{
    int a[M][M];
    Ma()
    {
        memset(a, 0, sizeof(a));
    }

    void init() // 复位为单位阵
    {
        a[0][0] = a[1][1] = 1;
        a[0][1] = a[1][1] = 0;
    }

    Ma operator*(const Ma& B) const
    {
        Ma ans;
        for(int i = 0; i < M; ++i)
            for(int j = 0; j < M; ++j)
                for(int k = 0; k < M; ++k)
                    ans.a[i][j] += a[i][k] * B.a[k][j];
        return ans;
    }

    Ma operator^(int n) const
    {
        Ma ans;
        ans.init();
        Ma A = *this; // 拷贝一个出来用于自乘
        while(n)
        {
            if(n & 1)
                ans = ans * A;
            A = A * A;
            n >>= 1;
        }
        return ans;
    }

    void show()
    {
        cout << "matrix" << endl;
        for(int i = 0; i < M; ++i)
        {
            for(int j = 0; j < M; ++j)
                cout << a[i][j] << " ";
            cout << endl;
        }
    }
};

int main()
{
    Ma A;
    A.a[0][0] = 0;
    A.a[0][1] = A.a[1][0] = A.a[1][1] = 1;
    A.show();

    Ma F;
    F.a[0][0] = F.a[1][0] = 1;
    F.a[0][1] = F.a[1][1] = 0;
    F.show();

    int n = 8;
    Ma ans = (A ^ n) * F;
    ans.show();
    return 0;
}
