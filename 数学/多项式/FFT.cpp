//Lougu P3803 【模板】多项式乘法(FFT)
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
} f[maxn << 1], g[maxn << 1];
int tr[maxn << 1], n, m, lim;
void dft(cp *f, int flag, int lim) {
    for (int i = 0; i < lim; i++) if (i < tr[i]) swap(f[i], f[tr[i]]);
    for (int p = 2; p <= lim; p <<= 1) {
        int len = p >> 1;
        cp tg(cos(2 * Pi / p), flag * sin(2 * Pi / p));
        for (int k = 0; k < lim; k += p) {
            cp buf(1.0, 0.0);
            for (int l = k; l < k + len; l++) {
                cp temp = buf * f[len + l];
                f[l + len] = f[l] - temp;
                f[l] = f[l] + temp;
                buf = buf * tg;
            }
        }
    }
    if (flag == -1) for (int i = 0; i < lim; i++) f[i].x /= lim;
}
void fft() {
    for (n += m, lim = 1; lim <= n; lim <<= 1);
    for (int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? lim >> 1 : 0);
    dft(f, 1, lim);
    dft(g, 1, lim);
    for (int i = 0; i < lim; i++) f[i] = f[i] * g[i];
    dft(f, -1, lim);
}
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; i++) scanf("%lf", &f[i].x);
    for (int i = 0; i <= m; i++) scanf("%lf", &g[i].x);;
    fft();
    for (int i = 0; i <= n; i++) printf("%d ", (int) (f[i].x + 0.49));
    return 0;
}