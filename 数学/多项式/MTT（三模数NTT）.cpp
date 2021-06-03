//Lougu P4245 【模板】任意模数多项式乘法
//104857601  = 25*2^22 + 1  g = 3
//167772161  = 5*2^25 + 1   g = 3
//469762049  = 7*2^26 +1    g = 3
//998244353  = 119*2^23 + 1 g = 3
//1004535809 = 479*2^21 + 1 g = 3
//2013265921 = 15*2^27 + 1  g = 31
//2281701377 = 17*2^27 + 1  g = 3
//3221225473 = 3*2^30 + 1   g = 5
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define maxn 200010
#define G 3
int tr[maxn << 1], n, m, lim, mod, x;
int qpow(int a, int b, const int mod) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1LL * ret * a % mod;
        a = 1LL * a * a % mod, b >>= 1;
    }
    return ret;
}
const int mod1 = 998244353, mod2 = 1004535809, mod3 = 469762049;
const ll mod12 = 1LL * mod1 * mod2;
const int inv1 = qpow(mod1, mod2 - 2, mod2), inv2 = qpow(1LL * mod1 * mod2 % mod3, mod3 - 2, mod3);
struct node {
    int a, b, c;
    node() {}
    node(int x) : a(x), b(x), c(x) {}
    node(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {}
    node operator+(const node &x) const {
        return node((a + x.a) % mod1, (b + x.b) % mod2, (c + x.c) % mod3);
    }
    node operator-(const node &x) const {
        return node((a - x.a + mod1) % mod1, (b - x.b + mod2) % mod2, (c - x.c + mod3) % mod3);
    }
    node operator*(const node &x) const {
        return node(1LL * a * x.a % mod1, 1LL * b * x.b % mod2, 1LL * c * x.c % mod3);
    }
    int crt() {
        ll x = 1LL * (b - a + mod2) % mod2 * inv1 % mod2 * mod1 + a;
        return (1LL * (c - x % mod3 + mod3) % mod3 * inv2 % mod3 * (mod12 % mod) % mod + x) % mod;
    }
};
node f[maxn << 1], g[maxn << 1], pre[maxn << 1];
void init(int lim) {
    for (int i = 2; i <= lim; i <<= 1) {
        node w(qpow(G, (mod1 - 1) / i, mod1), qpow(G, (mod2 - 1) / i, mod2), qpow(G, (mod3 - 1) / i, mod3));
        pre[i >> 1] = node(1);
        for (int j = (i >> 1) + 1; j < i; j++) pre[j] = pre[j - 1] * w;
    }
}
void dft(node *f, bool flag, int lim) {
    for (int i = 0; i < lim; i++) if (i < tr[i]) swap(f[i], f[tr[i]]);
    for (int p = 2; p <= lim; p <<= 1) {
        for (int k = 0, len = p >> 1; k < lim; k += p) {
            for (int l = k; l < k + len; l++) {
                node temp = pre[l + len - k] * f[l + len];
                f[l + len] = f[l] - temp;
                f[l] = f[l] + temp;
            }
        }
    }
    if (flag == false) {
        node invlim(qpow(lim, mod1 - 2, mod1), qpow(lim, mod2 - 2, mod2), qpow(lim, mod3 - 2, mod3));
        for (int i = 0; i < lim; i++) f[i] = f[i] * invlim;
        reverse(f + 1, f + lim);
    }
}
void mtt() {
    for (n += m, lim = 1; lim <= n; lim <<= 1);
    for (int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? lim >> 1 : 0);
    init(lim);
    dft(f, true, lim);
    dft(g, true, lim);
    for (int i = 0; i < lim; i++) f[i] = f[i] * g[i];
    dft(f, false, lim);
}
signed main() {
    scanf("%d%d%d", &n, &m, &mod);
    for (int i = 0; i <= n; i++) scanf("%d", &x), f[i] = node(x);
    for (int i = 0; i <= m; i++) scanf("%d", &x), g[i] = node(x);
    mtt();
    for (int i = 0; i <= n; i++) printf("%d ", f[i].crt());
    return 0;
}