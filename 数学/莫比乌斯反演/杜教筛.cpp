//Luogu P4213 【模板】杜教筛（Sum）
//计算\sum_{i=1}^{i=n} phi[i]  \sum_{i=1}^{i=n} u[i]
//g(1)s(n) = \sum_{i=1}^{i=n}(f*g)(i) - \sum_{i=2}^{i=n}g(i)s(n/i)
//预先筛出O(n^(2/3)) 复杂度O(n^(2/3))
//注意查询位置在2^31-1 数列分块会溢出
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define maxn 10000010
int t, n;
ll sumphi[maxn];
int phi[maxn], prime[maxn], u[maxn], sumu[maxn];
bool flag[maxn];
int cnt;
unordered_map<int, int> mu;
unordered_map<int, ll> mphi;
void sieve() {
    phi[1] = 1, u[1] = 1;
    for (int i = 2; i < maxn; i++) {
        if (!flag[i]) prime[++cnt] = i, phi[i] = i - 1, u[i] = -1;
        for (int j = 1; j <= cnt && i * prime[j] < maxn; j++) {
            flag[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1), u[i * prime[j]] = -u[i];
        }
    }
    for (int i = 1; i < maxn; i++) sumphi[i] = sumphi[i - 1] + phi[i], sumu[i] = sumu[i - 1] + u[i];
}
ll calcphi(ll n) {
    if (n < maxn) return sumphi[n];
    if (mphi.count(n)) return mphi[n];
    ll ret = n * (n + 1) / 2;//n + 1会爆int
    for (ll l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ret -= (r - l + 1) * calcphi(n / l);
    }
    return mphi[n] = ret;
}
int calcu(int n) {
    if (n < maxn) return sumu[n];
    if (mu.count(n)) return mu[n];
    int ret = 1;
    for (ll l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ret -= (r - l + 1) * calcu(n / l);
    }
    return mu[n] = ret;
}
signed main() {
    sieve();
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        printf("%lld %d\n", calcphi(n), calcu(n));
    }
    return 0;
}