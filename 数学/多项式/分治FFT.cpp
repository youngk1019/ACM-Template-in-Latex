//Lougu P4721 【模板】分治 FFT
//f[0] = 1,f[i] = \sum{f[i-j]*g[j]}
#include <bits/stdc++.h>
using namespace std;
#define maxn 200010 //两个多项式长度的和，实际运行需要再开两倍
#define ck(x) (x >= mod ? x - mod : x)
#define G 3
const int mod = 998244353;
int f[maxn << 1], g[maxn << 1], a[maxn << 1], b[maxn << 1];
int pre[maxn << 1], tr[maxn << 1], n, m, lim;
int qpow(int a, int b) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1LL * ret * a % mod;
        a = 1LL * a * a % mod, b >>= 1;
    }
    return ret;
}
void init(int lim) {
    for (int i = 2; i <= lim; i <<= 1) {
        int w = qpow(G, (mod - 1) / i);
        pre[i >> 1] = 1;
        for (int j = (i >> 1) + 1; j < i; j++) pre[j] = 1LL * pre[j - 1] * w % mod;
    }
}
void dft(int *f, bool flag, int lim) {
    for (int i = 0; i < lim; i++) if (i < tr[i]) swap(f[i], f[tr[i]]);
    for (int p = 2; p <= lim; p <<= 1) {
        for (int k = 0, len = p >> 1; k < lim; k += p) {
            for (int l = k; l < k + len; l++) {
                int temp = 1LL * pre[l + len - k] * f[l + len] % mod;
                f[l + len] = ck(f[l] - temp + mod);
                f[l] = ck(f[l] + temp);
            }
        }
    }
    if (flag == false) {
        int invlim = qpow(lim, mod - 2);
        for (int i = 0; i < lim; i++) f[i] = 1LL * f[i] * invlim % mod;
        reverse(f + 1, f + lim);
    }
}
void cdq_ntt(int l, int r) {
    if (l == r) {
        if (l == 0) f[l] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    cdq_ntt(l, mid);
    memcpy(a, f + l, sizeof(int) * (mid - l + 1));
    memcpy(b, g, sizeof(int) * (r - l + 1));
    for (lim = 2; lim <= r - l + 1; lim <<= 1);
    for (int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? lim >> 1 : 0);

    memset(a + mid - l + 1, 0, sizeof(int) * (lim - mid + l));
    memset(b + r - l + 1, 0, sizeof(int) * (lim - r + l));
    dft(a, true, lim);
    dft(b, true, lim);
    for (int i = 0; i < lim; i++) a[i] = 1LL * a[i] * b[i] % mod;
    dft(a, false, lim);
    for (int i = mid + 1; i <= r; i++) {
        f[i] = ck(f[i] + a[i - l]);
    }
    cdq_ntt(mid + 1, r);
}

signed main() {
    scanf("%d", &n);
    for (lim = 1; lim <= n; lim <<= 1);
    init(lim);
    for (int i = 1; i < n; i++) scanf("%d", g + i);
    cdq_ntt(0, n - 1);
    for (int i = 0; i < n; i++) printf("%d ", f[i]);
    return 0;
}