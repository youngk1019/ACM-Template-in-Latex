//Lougu P4717 【模板】快速莫比乌斯/沃尔什变换 (FMT/FWT)
#include <bits/stdc++.h>
using namespace std;
#define maxn 1 << 17
const int mod = 998244353;
int m, n, f[maxn], g[maxn], a[maxn], b[maxn];
int qpow(int a, int b) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1LL * ret * a % mod;
        a = 1LL * a * a % mod, b >>= 1;
    }
    return ret;
}
void _or(int *f, int x) {
    for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1) {
        for (int i = 0; i < n; i += o) {
            for (int j = 0; j < k; j++) {
                f[i + j + k] = (f[i + j + k] + 1LL * f[i + j] * x % mod) % mod;
            }
        }
    }
}
void _and(int *f, int x) {
    for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1) {
        for (int i = 0; i < n; i += o) {
            for (int j = 0; j < k; j++) {
                f[i + j] = (f[i + j] + 1LL * f[i + j + k] * x % mod) % mod;
            }
        }
    }
}
void _xor(int *f, int x) {
    for (int o = 2, k = 1; o <= n; o <<= 1, k <<= 1) {
        for (int i = 0; i < n; i += o) {
            for (int j = 0; j < k; j++) {
                f[i + j] = (f[i + j] + f[i + j + k]) % mod;
                f[i + j + k] = ((f[i + j] - f[i + j + k] - f[i + j + k]) % mod + mod) % mod;
                f[i + j] = 1LL * x * f[i + j] % mod, f[i + j + k] = 1LL * x * f[i + j + k] % mod;
            }
        }
    }
}
void fwt(void (*fun)(int *, int), int p) {
    memcpy(f, a, sizeof(int) * n);
    memcpy(g, b, sizeof(int) * n);
    fun(f, 1);
    fun(g, 1);
    for (int i = 0; i < n; i++) f[i] = 1LL * f[i] * g[i] % mod;
    fun(f, p);
    for (int i = 0; i < n; i++)printf("%d ", f[i]);
    puts("");
}
signed main() {
    scanf("%d", &m);
    n = 1 << m;
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    for (int i = 0; i < n; i++) scanf("%d", b + i);
    fwt(_or, mod - 1);
    fwt(_and, mod - 1);
    fwt(_xor, qpow(2, mod - 2));
    return 0;
}