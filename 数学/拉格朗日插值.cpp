//Luogu P4781 【模板】拉格朗日插值
#include <bits/stdc++.h>
#define maxn 2010
const int mod = 998244353;
int n, k, x[maxn], y[maxn], ans;
int qpow(int a, int b) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1LL * a * ret % mod;
        a = 1LL * a * a % mod, b >>= 1;
    }
    return ret;
}
signed main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d%d", x + i, y + i);
    for (int i = 1; i <= n; i++) {
        int u = 1;
        for (int j = 1; j <= n; j++) if (i ^ j) u = 1LL * u * (x[i] + mod - x[j]) % mod;
        u = qpow(u, mod - 2);
        for (int j = 1; j <= n; j++) if (i ^ j) u = 1LL * u * (k + mod - x[j]) % mod;
        ans = (ans + 1LL * u * y[i] % mod) % mod;
    }
    printf("%d", ans);
    return 0;
}