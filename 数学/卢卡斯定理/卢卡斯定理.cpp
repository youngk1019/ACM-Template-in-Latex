//Luogu P3807 【模板】卢卡斯定理
//计算C_{n}^{m} mod p ,p 为质数
//复杂度预处理O(p) + 查询O(logp)
#include<bits/stdc++.h>
using namespace std;
#define maxn 100100
int t, n, m, p, f[maxn], invf[maxn];
int c(int n, int m, int p) {
    if (n > m) return 0;
    return 1LL * f[m] * invf[n] % p * invf[m - n] % p;
}
int lucas(int n, int m, int p) {
    if (!n) return 1;
    return 1LL * c(n % p, m % p, p) * lucas(n / p, m / p, p) % p;
}
signed main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &n, &m, &p);
        invf[0] = invf[1] = f[0] = f[1] = 1;
        for (int i = 2; i < p; i++) f[i] = 1LL * f[i - 1] * i % p;
        for (int i = 2; i < p; i++) invf[i] = 1LL * (p - p / i) * invf[p % i] % p;
        for (int i = 2; i < p; i++) invf[i] = 1LL * invf[i - 1] * invf[i] % p;
        printf("%d\n", lucas(n, n + m, p));
    }
    return 0;
}