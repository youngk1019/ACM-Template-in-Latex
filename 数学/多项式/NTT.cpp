//Lougu P3803 【模板】多项式乘法(FFT)
#include <bits/stdc++.h>
using namespace std;
#define maxn 2000100 //两个多项式长度的和，实际运行需要再开两倍
#define ck(x) (x >= mod ? x - mod : x)
#define G 3
#define invG 332748118
const int mod = 998244353;
int f[maxn << 1], g[maxn << 1];
int tr[maxn << 1], n, m, lim;
int qpow(int a, int b) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1LL * ret * a % mod;
        a = 1LL * a * a % mod, b >>= 1;
    }
    return ret;
}
void dft(int *f, bool flag, int lim) {
    for (int i = 0; i < lim; i++) if (i < tr[i]) swap(f[i], f[tr[i]]);
    for (int p = 2; p <= lim; p <<= 1) {
        int len = p >> 1, tg = qpow(flag ? G : invG, (mod - 1) / p);
        for (int k = 0; k < lim; k += p) {
            for (int l = k, buf = 1; l < k + len; l++) {
                int temp = 1LL * buf * f[len + l] % mod;
                f[l + len] = ck(f[l] - temp + mod);
                f[l] = ck(f[l] + temp);
                buf = 1LL * buf * tg % mod;
            }
        }
    }
    if (flag == false) {
        int invlim = qpow(lim, mod - 2);
        for (int i = 0; i < lim; i++) f[i] = 1LL * f[i] * invlim % mod;
    }
}
void ntt() {
    for (n += m, lim = 1; lim <= n; lim <<= 1);
    for (int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? lim >> 1 : 0);
    dft(f, true, lim);
    dft(g, true, lim);
    for (int i = 0; i < lim; i++) f[i] = 1LL * f[i] * g[i] % mod;
    dft(f, false, lim);
}
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; i++) scanf("%d", f + i);
    for (int i = 0; i <= m; i++) scanf("%d", g + i);;
    ntt();
    for (int i = 0; i <= n; i++) printf("%d ", f[i]);
    return 0;
}