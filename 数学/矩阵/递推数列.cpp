//P7112 CF1182E Product Oriented Recurrence
//求 f[x] = c^{2x-6}*f[x-1]*f[x-2]*f[x-3]
//－g[n]－－－－ 1 1 1 1 1 －g[n-1]
//－g[n-1]－－－ 1 0 0 0 0 －g[n-2]
//{ g[n-2] } = {0 1 0 0 0}{ g[n-3] }
//－2n-6－－－－ 0 0 0 1 1 －2(n-1)-6
//－2 －－－－－ 0 0 0 0 1 －2
//
//－h[n] －－－－ 1 1 1 － h[n-1]
//{ h[n-1] } = { 1 0 0 }{ h[n-2] }
//－h[n-2] －－－ 0 1 0 － h[n-3]
//注意质数模数p = mod - 1
//矩阵乘法循环节不为p
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
const int p = 1e9 + 6;
struct matrix {
    int a[6][6];
    matrix() { memset(a, 0, sizeof(a)); }
    matrix operator*(const matrix &x) {
        matrix ret;
        for (int i = 1; i <= 5; i++) {
            for (int j = 1; j <= 5; j++) {
                for (int k = 1; k <= 5; k++) ret.a[i][j] = (ret.a[i][j] + 1LL * a[i][k] * x.a[k][j] % p) % p;
            }
        }
        return ret;
    }
} a, b;
matrix qpow(matrix a, long long b) {
    matrix ret;
    for (int i = 1; i <= 5; i++) ret.a[i][i] = 1;
    while (b) {
        if (b & 1)ret = ret * a;
        a = a * a, b >>= 1;
    }
    return ret;
}
int qpow(int a, int b) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1LL * a * ret % mod;
        a = 1LL * a * a % mod, b >>= 1;
    }
    return ret;
}
long long n;
int f1, f2, f3, c, x1, x2, x3, x4;
signed main() {
    scanf("%lld%d%d%d%d", &n, &f1, &f2, &f3, &c);
    a.a[1][1] = a.a[1][2] = a.a[1][3] = a.a[2][1] = a.a[3][2] = 1;
    b.a[1][1] = b.a[1][2] = b.a[1][3] = b.a[1][4] = b.a[1][5] = b.a[2][1] = b.a[3][2] = b.a[4][4] = b.a[4][5] = b.a[5][5] = 1;
    a = qpow(a, n - 3), b = qpow(b, n - 3);
    x1 = 2LL * b.a[1][5] % p;
    x2 = a.a[1][3];
    x3 = a.a[1][2];
    x4 = a.a[1][1];
    printf("%lld", 1LL * qpow(c, x1) * qpow(f1, x2) % mod * qpow(f2, x3) % mod * qpow(f3, x4) % mod);
    return 0;
}