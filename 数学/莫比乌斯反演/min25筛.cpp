//Luogu P5325 【模板】Min_25筛
//复杂度O(n^(1-e)) O(n^(3/4)/logn)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define maxn 100010//sqrt(n)
const int mod = 1e9 + 7, inv2 = 500000004, inv3 = 166666668;
ll n;
int prime[maxn], cnt, gp1[maxn], gp2[maxn];
bool flag[maxn];
ll w[maxn << 1], sw;
int g1[maxn << 1], g2[maxn << 1], id1[maxn], id2[maxn];
int S(ll x, int y) {
    if (prime[y] >= x)return 0;
    int p = x < maxn ? id1[x] : id2[n / x];
    int ret = ((g2[p] - g1[p] - (gp2[y] - gp1[y])) % mod + mod) % mod;//总体前缀和x - 质数位置前缀和y
    for (int i = y + 1; i <= cnt && 1LL * prime[i] * prime[i] <= x; ++i) {
        ll pr = prime[i];
        for (int e = 1; pr <= x; ++e, pr *= prime[i]) {
            int o = pr % mod;
            ret = (ret + 1LL * o * (o - 1) % mod * (S(x / pr, i) + (e != 1))) % mod;//前面是o*(o-1)为函数值 后面是p^(e+1)的函数值
        }
    }
    return ret;
}
void sieve() {
    for (int i = 2; i < maxn; ++i) {
        if (!flag[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt && i * prime[j] < maxn; ++j) {
            flag[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
        }
    }
    for (int i = 1; i <= cnt; ++i)
        gp1[i] = (gp1[i - 1] + prime[i]) % mod, gp2[i] = (gp2[i - 1] + 1LL * prime[i] * prime[i]) % mod;//递推时用的质数处F前缀和
}
int calc(ll n) {
    for (ll l = 1, r; l <= n; l = r + 1) {//预处理(n/i) 计算g的j=0边界，边界就是F的前缀和，由于质数处F(p)是多项式所以可以快速算
        r = n / (n / l);
        w[++sw] = n / l;
        g1[sw] = w[sw] % mod;
        g2[sw] = (1LL * g1[sw] * (g1[sw] + 1) % mod * (g1[sw] * 2 + 1) % mod * inv3 % mod - 1) % mod;//1..w[sw]平方和
        g1[sw] = (1LL * g1[sw] * (g1[sw] + 1) % mod * inv2 - 1) % mod;//1..w[sw]等差数列和
        if (n / l < maxn) id1[n / l] = sw;
        else id2[l] = sw;
    }
    //j从1到|P|递推g
    for (int i = 1; i <= cnt; ++i) {
        ll sqrp = 1LL * prime[i] * prime[i];
        for (int j = 1; j <= sw && sqrp <= w[j]; ++j) {
            ll p = w[j] / prime[i];
            p = (p < maxn ? id1[p] : id2[n / p]);//定位p的坐标
            g1[j] = (g1[j] - 1LL * prime[i] * (g1[p] - gp1[i - 1] + mod) % mod + mod) % mod;
            g2[j] = (g2[j] - 1LL * prime[i] * prime[i] % mod * (g2[p] - gp2[i - 1] + mod) % mod + mod) % mod;
        }
    }
    return (S(n, 0) + 1) % mod;
}
signed main() {
    scanf("%lld", &n);
    sieve();
    printf("%d\n", calc(n));
    return 0;
}