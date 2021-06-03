//Luogu P2742 [USACO5.1]圈奶牛Fencing the Cows /【模板】二维凸包
#include <bits/stdc++.h>
using namespace std;
#define maxn 100100
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
double length(const vec &A) { return sqrt(A * A); }
double dis(const vec &A, const vec &B) { return length(A - B); }
// < 0 : right , = 0 : parallel , > 0 : left
double side(const vec &A, const vec &B, const vec &P) { return (B - A) ^ (P - B); }
void convex_2(vec *p, vec *s, int n, int &top) {
    //input:p[1...n] output:s[1...top] s[1] = s[top]
    sort(p + 1, p + n + 1);
    top = 0;
    s[++top] = p[1];
    for (int i = 2; i <= n; i++) {
        while (top > 1 && side(s[top - 1], s[top], p[i]) <= 0) top--;
        s[++top] = p[i];
    }
    int up = top;
    for (int i = n - 1; i >= 1; i--) {
        while (top > up && side(s[top - 1], s[top], p[i]) <= 0) top--;
        s[++top] = p[i];
    }
}
double girth(vec *p, int n) {
    //input: p[1...n] p[1] = p[n]
    double ret = 0.0;
    for (int i = 2; i <= n; i++) ret += dis(p[i - 1], p[i]);
    return ret;
}
int n, m;
double x, y;
vec p[maxn], s[maxn];
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf", &x, &y);
        p[i] = vec(x, y);
    }
    convex_2(p, s, n, m);
    printf("%.2lf", girth(s, m));
    return 0;
}