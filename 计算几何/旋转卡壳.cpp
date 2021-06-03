//Luogu P1452 [USACO03FALL]Beauty Contest G /【模板】旋转卡壳
//题目需要保留不开根号的值，除了强改为long long外还修改了length和cmp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define maxn 50100
#define double ll
struct vec {
    double x, y;
    vec(double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {}
};
vec operator+(const vec &A, const vec &B) { return vec(A.x + B.x, A.y + B.y); }
vec operator-(const vec &A, const vec &B) { return vec(A.x - B.x, A.y - B.y); }
vec operator*(const double &k, const vec &A) { return vec(k * A.x, k * A.y); }
vec operator*(const vec &A, const double &k) { return k * A; }
vec operator/(const vec &A, const double &k) { return vec(A.x / k, A.y / k); }
bool operator<(const vec &A, const vec &B) { return A.x == B.x ? A.y < B.y : A.x < B.x; }
bool operator>(const vec &A, const vec &B) { return B < A; }
bool operator==(const vec &A, const vec &B) { return A.x == B.x && A.y == B.y; }
bool operator!=(const vec &A, const vec &B) { return !(A == B); }
double operator*(const vec &A, const vec &B) { return A.x * B.x + A.y * B.y; }
double operator^(const vec &A, const vec &B) { return A.x * B.y - A.y * B.x; }
double length(const vec &A) { return A * A; }
double area(const vec &A, const vec &B, const vec &C) { return fabs(((B - A) ^ (C - A)) / 2); }
double dis(const vec &A, const vec &B) { return length(A - B); }
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
double get_mx(vec *p, int n) {
    //input:s[1...n] s[1] = s[n]
    double ret = 0;
    int j = 3;
    for (int i = 1; i < n; i++) {
        while (area(p[i], p[i + 1], p[j]) < area(p[i], p[i + 1], p[j + 1])) {
            j = j == n ? 1 : j + 1;
        }
        ret = max(ret, max(dis(p[i], p[j]), dis(p[i + 1], p[j])));
    }
    return ret;
}
int n, m;
double x, y;
vec p[maxn], s[maxn];
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", &x, &y);
        p[i] = vec(x, y);
    }
    convex_2(p, s, n, m);
    printf("%lld", get_mx(s, m));
    return 0;
}