//Luogu P4196 [CQOI2006]凸多边形 /【模板】半平面交
#include <bits/stdc++.h>
using namespace std;
#define maxn 510
#define eps 1e-10
struct vec {
    double x, y;
    vec(double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {}
};
vec operator+(const vec &A, const vec &B) { return vec(A.x + B.x, A.y + B.y); }
vec operator-(const vec &A, const vec &B) { return vec(A.x - B.x, A.y - B.y); }
vec operator*(const double &k, const vec &A) { return vec(k * A.x, k * A.y); }
vec operator*(const vec &A, const double &k) { return k * A; }
vec operator/(const vec &A, const double &k) { return vec(A.x / k, A.y / k); }
inline int sgn(double x) {
    if (fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
}
inline int cmp(double x, double y) { return sgn(x - y); }
bool operator<(const vec &A, const vec &B) { return cmp(A.x, B.x) == 0 ? cmp(A.y, B.y) < 0 : cmp(A.x, B.x) < 0; }
bool operator>(const vec &A, const vec &B) { return B < A; }
bool operator==(const vec &A, const vec &B) { return (cmp(A.x, B.x)) && (cmp(A.y, B.y)); }
bool operator!=(const vec &A, const vec &B) { return !(A == B); }
double operator*(const vec &A, const vec &B) { return A.x * B.x + A.y * B.y; }
double operator^(const vec &A, const vec &B) { return A.x * B.y - A.y * B.x; }
//double angle(const vec &A) { return atan2(A.y, A.x); }
//double angle(const vec &A, const vec &B) { return atan2(fabs(A ^ B), A * B); }
//double signed_angle(const vec &A, const vec &B) { return atan2(A ^ B, A * B); }
//vec rotate(const vec &A, const double &k) {
//    double c = cos(k), s = sin(k);
//    return vec(A.x * c - A.y * s, A.x * s + A.y * c);
//}
vec get_line_intersection(const vec &A, const vec &B, const vec &C, const vec &D) {
    return A + ((D ^ (A - C)) / (B ^ D)) * B;
}
double area(vec *p, int n) {
    //input: p[1...n] p[1] = p[n]
    double ret = p[n] ^p[1];
    for (int i = 2; i <= n; i++) {
        ret += p[i - 1] ^ p[i];
    }
    return ret / 2.0;
}
struct Line {
    vec p, v;
    double ang;
    Line() {}
    Line(vec p, vec v) : p(p), v(v) { ang = atan2(v.y, v.x); }
    Line(double a, double b, double c) { // ax + by + c = 0
        if (sgn(a) == 0) p = vec(0, -c / b), v = vec(1, 0), ang = atan2(v.y, v.x);
        else if (sgn(b) == 0) p = (-c / a, 0), v = vec(0, 1), ang = atan2(v.y, v.x);
        else p = vec(0, -c / b), v = vec(-b, a), ang = atan2(v.y, v.x);
    }
};
//vec get_point(Line &x, double a) { return x.p + x.v * a; }
bool operator<(const Line &x, const Line &y) { return x.ang < y.ang; }
// < 0 : right , = 0 : parallel , > 0 : left
double side(vec p, Line l) { return l.v ^ (p - l.p); }
vec get_line_intersection(const Line &A, const Line &B) { return get_line_intersection(A.p, A.v, B.p, B.v); }
struct half_plane {
    vec p[maxn]; // p[i] is the intersection of line q[i] and q[i+1]
    Line q[maxn];   // deque
    void half_plane_intersection(Line *L, int n, vec *ret, int &cnt) {
        //input:L[1...n] output:ret[1...cnt] ret[1] = ret[cnt]
        sort(L + 1, L + n + 1);
        int head, tail;
        q[head = tail = 0] = L[1];
        for (int i = 2; i <= n; i++) {
            while (head < tail && side(p[tail - 1], L[i]) < 0) tail--;
            while (head < tail && side(p[head], L[i]) < 0) head++;
            q[++tail] = L[i];
            if (sgn(q[tail].v ^ q[tail - 1].v) == 0) {
                tail--;
                if (side(L[i].p, q[tail]) >= 0) q[tail] = L[i];
            }
            if (head < tail) p[tail - 1] = get_line_intersection(q[tail - 1], q[tail]);
        }
        while (head < tail && side(p[tail - 1], q[head]) < 0) tail--;
        p[tail] = get_line_intersection(q[tail], q[head]);
        cnt = 0;
        for (int i = head; i <= tail; i++) ret[++cnt] = p[i];
    }
} hp;
int n, m, cnt = 1, s;
double x, y;
Line l[maxn];
vec p[maxn], ans[maxn];
signed main() {
    scanf("%d", &n);
    while (n--) {
        scanf("%d", &m);
        for (int i = cnt; i <= cnt + m - 1; i++) {
            scanf("%lf%lf", &x, &y);
            p[i] = vec(x, y);
        }
        for (int i = cnt; i < cnt + m - 1; i++) l[i] = Line(p[i], p[i + 1] - p[i]);
        l[cnt + m - 1] = Line(p[cnt + m - 1], p[cnt] - p[cnt + m - 1]);
        cnt += m;
    }
    cnt--;
    hp.half_plane_intersection(l, cnt, ans, s);
    printf("%.3lf", area(ans, s));
    return 0;
}