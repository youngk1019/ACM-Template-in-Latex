//Luogu P1742 最小圆覆盖
//random_suffle可以不需要定义小于运算符
#include <bits/stdc++.h>
using namespace std;
#define maxn 100100
struct vec {
    double x, y;
    vec(double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {}
};
vec operator+(const vec &A, const vec &B) { return vec(A.x + B.x, A.y + B.y); }
vec operator-(const vec &A, const vec &B) { return vec(A.x - B.x, A.y - B.y); }
double operator*(const vec &A, const vec &B) { return A.x * B.x + A.y * B.y; }
double length(const vec &A) { return sqrt(A * A); }
double dis(const vec &A, const vec &B) { return length(A - B); }
vec get_centre(vec a, vec b, vec c) {
    double a1 = b.x - a.x, a2 = c.x - a.x, b1 = b.y - a.y, b2 = c.y - a.y;
    double c1 = b.x * b.x - a.x * a.x + b.y * b.y - a.y * a.y;
    double c2 = c.x * c.x - a.x * a.x + c.y * c.y - a.y * a.y;
    return vec((b2 * c1 - b1 * c2) / (b2 * a1 * 2 - b1 * a2 * 2),
               (a2 * c1 - a1 * c2) / (a2 * b1 * 2 - a1 * b2 * 2));
}
pair<double, vec> solve(vec *p, int n) {
    //input:p[1...n]  return {r,{o.x,o.y}}
    random_shuffle(p + 1, p + n + 1);
    double r = 0;
    vec o = p[1];
    for (int i = 2; i <= n; i++) {
        if (dis(o, p[i]) > r) {
            o = p[i], r = 0;
            for (int j = 1; j < i; j++) {
                if (dis(o, p[j]) > r) {
                    o = vec((p[i].x + p[j].x) / 2, (p[i].y + p[j].y) / 2);
                    r = dis(o, p[j]);
                    for (int k = 1; k < j; k++) {
                        if (dis(o, p[k]) > r) {
                            o = get_centre(p[i], p[j], p[k]);
                            r = dis(p[i], o);
                        }
                    }
                }
            }
        }
    }
    return make_pair(r, o);
}
int n, m;
double x, y;
vec p[maxn];
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf", &x, &y);
        p[i] = vec(x, y);
    }
    auto u = solve(p, n);
    printf("%.10lf\n%.10lf %.10lf", u.first, u.second.x, u.second.y);
    return 0;
}