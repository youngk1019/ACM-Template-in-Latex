//Luogu P3846 [TJOI2007] 可爱的质数/【模板】BSGS
//计算一个最小的 l，满足 a^l ≡ b (mod p) p 为质数
#include<bits/stdc++.h>
using namespace std;
int qpow(int a, int b, int mod) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1LL * ret * a % mod;
        a = 1LL * a * a % mod, b >>= 1;
    }
    return ret;
}
int bsgs(int a, int b, int p) {
    if (!(a % p) && b) return -1;
    unordered_map<int, int> mp;
    int m = ceil(sqrt(p));
    for (int i = 0, t = b; i < m; i++) mp[t] = i, t = 1LL * t * a % p;
    for (int i = 1, j = qpow(a, m, p), t = j; i <= m; i++) {
        if (mp.count(t)) return i * m - mp[t];
        t = 1LL * t * j % p;
    }
    return -1;
}
int a, b, p, ans;
signed main() {
    scanf("%d%d%d", &p, &a, &b);
    ans = bsgs(a, b, p);
    if (ans == -1) puts("no solution");
    else printf("%d\n", ans);
    return 0;
}