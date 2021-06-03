//Lougu P4783 【模板】矩阵求逆
#include <bits/stdc++.h>
using namespace std;
#define maxn 510
const int mod = 1e9 + 7;
int n, a[maxn][maxn], is[maxn], js[maxn];
int qpow(int a, int b) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1LL * a * ret % mod;
        a = 1LL * a * a % mod, b >>= 1;
    }
    return ret;
}
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) scanf("%d", &a[i][j]);
    }
    for (int k = 1; k <= n; k++) {
        is[k] = js[k] = k;
        for (int i = k; i <= n; i++) {
            for (int j = k; j <= n; j++) {
                if (a[i][j]) is[k] = i, js[k] = j;
            }
        }
        for (int j = 1; j <= n; j++) swap(a[k][j], a[is[k]][j]);
        for (int i = 1; i <= n; i++) swap(a[i][k], a[i][js[k]]);
        if (a[k][k] == 0) return puts("No Solution"), 0;
        a[k][k] = qpow(a[k][k], mod - 2);
        for (int j = 1; j <= n; j++) {
            if (j != k)a[k][j] = 1LL * a[k][j] * a[k][k] % mod;
        }
        for (int i = 1; i <= n; i++) {
            if (i != k) {
                for (int j = 1; j <= n; j++) {
                    if (j != k) a[i][j] = ((a[i][j] - 1LL * a[i][k] * a[k][j] % mod) % mod + mod) % mod;
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            if (i != k) a[i][k] = (-1LL * a[i][k] * a[k][k] % mod + mod) % mod;
        }
    }
    for (int k = n; k >= 1; k--) {
        for (int j = 1; j <= n; j++) swap(a[js[k]][j], a[k][j]);
        for (int i = 1; i <= n; i++) swap(a[i][is[k]], a[i][k]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) printf("%d ", a[i][j]);
        puts("");
    }
    return 0;
}