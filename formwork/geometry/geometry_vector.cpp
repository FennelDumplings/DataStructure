#include <vector>
#include <cmath>

using namespace std;

// 二维向量
const double PI = 2.0 * acos(0.0);
const double EPS = 1e-10;

struct Vector2
{
    double x, y;
    // 把构造函数指定 explicit，可以放置发生在 Vector2 的位置中加入实数的错误
    explicit Vector2(double x_=0, double y_=0):x(x_),y(y_){}

    // 比较两个向量
    bool operator==(const Vector2& vec) const
    {
        return fabs(x - vec.x) < EPS && fabs(y - vec.y) < EPS;
    }
    bool operator<(const Vector2& vec) const
    {
        if(abs(x - vec.x) < EPS)
            return y < vec.y;
        return x < vec.x;
    }

    // 向量的加法和减法
    Vector2 operator+(const Vector2& vec) const
    {
        return Vector2(x + vec.x, y + vec.y);
    }
    Vector2 operator-(const Vector2& vec) const
    {
        return Vector2(x - vec.x, y - vec.y);
    }

    // 向量的数乘
    Vector2 operator*(double a) const
    {
        return Vector2(x * a, y * a);
    }

    // 向量的模
    double norm() const
    {
        return hypot(x, y);
    }

    // 返回方向相同的单位向量
    // 零向量不可调用
    Vector2 normalize() const
    {
        return Vector2(x / norm(), y / norm());
    }

    // 从 x 轴正方向转到当前向量的角度
    double polar() const
    {
        // atan2 返回 (-PI, PI]，修正为 [0，2PI)
        // fmod 求两个实数相除的余数
        return fmod(atan2(y, x) + 2 * PI, 2 * PI);
    }

    // 内积
    double dot(const Vector2& vec) const
    {
        return x * vec.x + y * vec.y;
    }
    double cross(const Vector2& vec) const
    {
        return x * vec.y - y * vec.x;
    }

    // 当前向量映射到另一向量的结果
    // vec的长度需要大于0
    Vector2 project(const Vector2& vec) const
    {
        Vector2 r = vec.normalize();
        return r * r.dot(*this);
    }

    // 两个向量的夹角
    // 两个向量长度均需要大于 0
    double insersection_angle(const Vector2& vec) const
    {
        return acos(dot(vec) / norm() * vec.norm());
    }

    // 判断两个向量是否垂直
    // 两个向量长度均需要大于 0
    bool perpendicular(const Vector2& vec) const
    {
        return dot(vec) < EPS;
    }

    // 平行四边形面积
    double parallelogram_area(const Vector2& vec) const
    {
        return fabs(cross(vec));
    }

    // 三角形面积，可以扩找到多边形
    double triangle_area(const Vector2& vec) const
    {
        return fabs(cross(vec)) / 2;
    }
};

// 判定两个向量的方向
double ccw(const Vector2& a, const Vector2& b)
{
    // 正数: b 在 a 的逆时针 180 度内
    // 负数: b 在 a 的顺时针 180 度内
    // 0: 平行
    return a.cross(b);
}
double ccw(const Vector2& p, const Vector2& a, const Vector2& b)
{
    // 正数: 以 p 为基准点时，b 在 a 的逆时针 180 度内
    // 负数: 以 p 为基准点时，b 在 a 的顺时针 180 度内
    return ccw(a - p, b - p);
}

// -------------------------------------------------------

// 直线与直线相交
bool lineIntersection(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2& x)
{
    // 平行或重叠返回 false
    // (b - a) 是 (a, b) 的方向向量
    // (d - c) 是 (c, d) 的方向向量
    double det = (b - a).cross(d - c);
    if(fabs(det) < EPS)
        return false;
    x = a + (b - a) * ((c - a).cross(d - c) / det);
    return true;
}

// 线段与线段相交
bool parallelSegments(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2& x)
{
    // (a, b) , (c, d) 平行时，判断是否相接与一点
    if(b < a) swap(a, b);
    if(d < c) swap(c, d);
    // 两条线段不在同一条直线以及两条线段不重叠的情况
    if(ccw(a, b, c) != 0 || b < c || d < a) return false;
    if(a < c)
        x = c;
    else
        x = a;
    return true;
}
bool inBoundingRectangle(Vector2 x, Vector2 a, Vector2 b)
{
    // x, a, b 同线
    // 判断 x 是否在包含 (a, b) 且各边平行于 x 轴，y 轴的最小四边形内部。
    if(b < a) swap(a, b);
    return x == a || x == b || (a < x && x < b);
}
bool segmentIntersection(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2& x)
{
    // 将 (a, b) , (c, d) 的交点返回 x
    // 多个交点返回 x 最小的，x 相同的情况下返回 y 最小的
    // 不相交返回 false
    if(!lineIntersection(a, b, c, d, x))
    {
        // 两条线段平行
        return parallelSegments(a, b, c, d, x);
    }
    // 两条直线有交点 x
    // 仅当两条线段都包含 x 时返回真
    return inBoundingRectangle(x, a, b) && inBoundingRectangle(x, c, d);
}

// 仅判断两条线段是否相交，不需要交点
bool segmentIntersection(Vector2 a, Vector2 b, Vector2 c, Vector2 d)
{
    double ab = ccw(a, b, c) * ccw(a, b, d);
    double cd = ccw(c, d, a) * ccw(c, d, b);
    // 两条线段在同一直线上或者端点相互重叠
    if(ab == 0 && cd == 0)
    {
        if(b < a) swap(a, b);
        if(d < c) swap(c, d);
        return !(b < c || d < a);
    }
    return ab <= 0 && cd <= 0;
}

// 点和线的距离
Vector2 perpendicularFoot(Vector2 p, Vector2 a, Vector2 b)
{
    // p 到 (a, b) 的垂足
    return a + (p - a).project(b - a);
}
double pointToTline(Vector2 p, Vector2 a, Vector2 b)
{
    // p 到直线 (a, b) 的距离
    return (p - perpendicularFoot(p, a, b)).norm();
}

// 简单多边形 p 的面积
double area(const vector<Vector2>& p)
{
    double ans = 0.0;
    int n = p.size();
    for(int i = 0; i < n; ++i)
        ans += p[i].cross(p[(i + 1) % n]);
    return fabs(ans) / 2.0;
}

// 点 q 是否包含在多边形 p 内部
// q 在多边形边上没有处理
bool isInside(const vector<Vector2>& p, Vector2 q)
{
    int crosses = 0;
    int n = p.size();
    for(int i = 0; i < n; ++i)
    {
        int j = (i + 1) % n;
        // p[i], p[j] 能否纵向分割射线
        if((p[i].y > q.y) != (p[j].y > q.y))
        {
            // 交点的横坐标
            double X = (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y) + p[i].x;
            if(q.x < X)
                ++crosses;
        }
    }
    return crosses % 2 == 1;
}

// 判定对多边形 p 和 q 是否相交(相连或重叠)
// 只有一个点的重叠也是重叠
bool polygonIntersects(const vector<Vector2>& p, const vector<Vector2>& q)
{
    int n = p.size(), m = q.size();
    // 一个多边形的点在另一个多边形的内部
    if(isInside(p, q[0]) || isInside(q, p[0]))
        return true;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
        {
            if(segmentIntersection(p[i], p[(i + 1) % n], q[i], q[(i + 1) % n]))
                return true;
        }
    return false;
}


struct Line
{
    // line: a+pb, a 是点, b 是方向向量
    Vector2 a;
    Vector2 b;
    double deg; // 极角
    Line(Vector2 a, Vector2 b):a(a),b(b)
    {
        deg = b.polar();
    }
    bool operator<(const Line& l) const
    {
        // 方向向量的极角序
        return deg < l.deg;
    }
};


// 返回点 P 以点 O 为圆心逆时针旋转 alpha 后所在的位置
Vector2 rotate(Vector2 O, double alpha, Vector2 P)
{
    Vector2 new_P;
    Vector2 OP = P - O;
    new_P.x = OP.x * cos(alpha) - OP.y * sin(alpha) + O.x;
    new_P.y = OP.y * cos(alpha) + OP.x * sin(alpha) + O.y;
    return new_P;
}

