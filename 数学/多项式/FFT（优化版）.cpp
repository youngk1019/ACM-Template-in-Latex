//Lougu P3803 【模板】多项式乘法(FFT)
//三次变两次优化
//预处理效果不明显，很可能负优化
#include <bits/stdc++.h>
using namespace std;
#define maxn 2000100 //两个多项式长度的和，实际运行需要再开两倍
const double Pi = 4 * atan2(1.0, 1.0);
struct cp {
    double x, y;
    cp(double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {}
    cp operator+(cp const &a) const { return cp(x + a.x, y + a.y); }
    cp operator-(cp const &a) const { return cp(x - a.x, y - a.y); }
    cp operator*(cp const &a) const { return cp(a.x * x - a.y * y, x * a.y + y * a.x); }
} f[maxn << 1], pre[maxn << 1];
int tr[maxn << 1], n, m, lim;
void init(int lim) {
    for (int i = 2; i <= lim; i <<= 1) {
        cp w(cos(2 * Pi / i), sin(2 * Pi / i));
        pre[i >> 1] = cp(1, 0);
        for (int j = (i >> 1) + 1; j < i; j++) pre[j] = pre[j - 1] * w;
    }
}
void dft(cp *f, bool flag, int lim) {
    for (int i = 0; i < lim; i++) if (i < tr[i]) swap(f[i], f[tr[i]]);
    for (int p = 2; p <= lim; p <<= 1) {
        for (int k = 0, len = p >> 1; k < lim; k += p) {
            for (int l = k; l < k + len; l++) {
                cp temp = pre[l + len - k] * f[l + len];
                f[l + len] = f[l] - temp;
                f[l] = f[l] + temp;
            }
        }
    }
    if (flag == false) {
        for (int i = 0; i < lim; i++) f[i].y /= lim;//注意这里是除y
        reverse(f + 1, f + lim);
    }
}
void fft() {
    for (n += m, lim = 1; lim <= n; lim <<= 1);
    for (int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? lim >> 1 : 0);
    init(lim);
    dft(f, true, lim);
    for (int i = 0; i < lim; i++) f[i] = f[i] * f[i];
    dft(f, false, lim);
}
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; i++) scanf("%lf", &f[i].x);
    for (int i = 0; i <= m; i++) scanf("%lf", &f[i].y);;
    fft();
    for (int i = 0; i <= n; i++) printf("%d ", (int) (f[i].y / 2 + 0.49));
    return 0;
}