//CF gym101981 D Country Meow
//随机情况下O(n)
#include <bits/stdc++.h>
using namespace std;
#define eps 1e-5
#define maxn 110
struct node {
    double x, y, z;
    node() {}
    node(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
} a[maxn];
int n;
inline double dist(node p1, node p2) {//距离的平方
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) + (p1.z - p2.z) * (p1.z - p2.z);
}
inline double dot(node p1, node p2) {
    return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
}
void ball(node *p, node &o, double &r, int &cnt) {
    static node q[3];
    static double m[3][3], sol[3], L[3], det;
    o.x = o.y = o.z = r = 0;
    switch (cnt) {
        case 1:
            o = p[0];
            break;
        case 2:
            o.x = (p[0].x + p[1].x) / 2;
            o.y = (p[0].y + p[1].y) / 2;
            o.z = (p[0].z + p[1].z) / 2;
            r = dist(o, p[0]);
            break;
        case 3:
            for (int i = 0; i < 2; ++i) {
                q[i].x = p[i + 1].x - p[0].x;
                q[i].y = p[i + 1].y - p[0].y;
                q[i].z = p[i + 1].z - p[0].z;
            }
            for (int i = 0; i < 2; ++i)
                for (int j = 0; j < 2; ++j)
                    m[i][j] = dot(q[i], q[j]) * 2;
            for (int i = 0; i < 2; ++i)sol[i] = dot(q[i], q[i]);
            if (fabs(det = m[0][0] * m[1][1] - m[0][1] * m[1][0]) < eps)return;
            L[0] = (sol[0] * m[1][1] - sol[1] * m[0][1]) / det;
            L[1] = (sol[1] * m[0][0] - sol[0] * m[1][0]) / det;
            o.x = p[0].x + q[0].x * L[0] + q[1].x * L[1];
            o.y = p[0].y + q[0].y * L[0] + q[1].y * L[1];
            o.z = p[0].z + q[0].z * L[0] + q[1].z * L[1];
            r = dist(o, p[0]);
            break;
        case 4:
            for (int i = 0; i < 3; ++i) {
                q[i].x = p[i + 1].x - p[0].x;
                q[i].y = p[i + 1].y - p[0].y;
                q[i].z = p[i + 1].z - p[0].z;
                sol[i] = dot(q[i], q[i]);
            }
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    m[i][j] = dot(q[i], q[j]) * 2;
            det = m[0][0] * m[1][1] * m[2][2]
                  + m[0][1] * m[1][2] * m[2][0]
                  + m[0][2] * m[2][1] * m[1][0]
                  - m[0][2] * m[1][1] * m[2][0]
                  - m[0][1] * m[1][0] * m[2][2]
                  - m[0][0] * m[1][2] * m[2][1];
            if (fabs(det) < eps) return;
            for (int j = 0; j < 3; ++j) {
                for (int i = 0; i < 3; ++i) m[i][j] = sol[i];
                L[j] = (m[0][0] * m[1][1] * m[2][2]
                        + m[0][1] * m[1][2] * m[2][0]
                        + m[0][2] * m[2][1] * m[1][0]
                        - m[0][2] * m[1][1] * m[2][0]
                        - m[0][1] * m[1][0] * m[2][2]
                        - m[0][0] * m[1][2] * m[2][1]) / det;
                for (int i = 0; i < 3; ++i) m[i][j] = dot(q[i], q[j]) * 2;
            }
            o = p[0];
            for (int i = 0; i < 3; ++i) {
                o.x += q[i].x * L[i];
                o.y += q[i].y * L[i];
                o.z += q[i].z * L[i];
            }
            r = dist(o, p[0]);
    }
}
void minball(node *p, node *outer, int n, node &o, double &r, int &cnt) {
    ball(outer, o, r, cnt);
    if (cnt < 4) {
        for (int i = 0; i < n; ++i) {
            if (dist(o, p[i]) - r > eps) {
                outer[cnt] = p[i];
                cnt++;
                minball(p, outer, i, o, r, cnt);
                cnt--;
                if (i > 0) {
                    node Tt = p[i];
                    memmove(&p[1], &p[0], sizeof(node) * i);
                    p[0] = Tt;
                }
            }
        }
    }
}
void smallest_ball(node *p, node *outer, int n, node &o, double &r, int &cnt) {
    r = -1;
    for (int i = 0; i < n; ++i) {
        if (dist(o, p[i]) - r > eps) {
            cnt = 1;
            outer[0] = p[i];
            minball(p, outer, i, o, r, cnt);
        }
    }
}
double solve(node *p, int n) {//注意p[0..n-1]
    node o, outer[4];
    double r;//半径的平方
    int cnt = 0;
    random_shuffle(p , p + n);
    smallest_ball(p, outer, n, o, r, cnt);
    return sqrt(r);
}
signed main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%lf%lf%lf", &a[i].x, &a[i].y, &a[i].z);
    printf("%.15lf", solve(a, n));
    return 0;
}