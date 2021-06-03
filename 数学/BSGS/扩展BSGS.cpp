//Luogu P4195 【模板】扩展BSGS
//计算一个最小的 l，满足 a^l ≡ b (mod p) p 不一定为质数
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
int exbsgs(int a, int b, int p) {
    a %= p, b %= p;
    if (!b && !a) return 1;
    if (!a) return -1;
    if (!b) {
        int ret = 0, d = __gcd(a, p);
        while (d != 1) {
            ret++, p /= d, d = __gcd(a, p);
            if (p == 1) return ret;
        }
        return -1;
    }
    unordered_map<int, int> mp;
    int ret = 0, d = __gcd(a, p), c = 1;
    while (d != 1) {
        if (b % d) return -1;
        p /= d, b /= d, c = 1LL * a / d * c % p;
        ret++, d = __gcd(a, p);
        if (c == b) return ret;
    }
    int m = ceil(sqrt(p));
    for (int i = 0, t = b; i <= m; i++) mp[t] = i, t = 1LL * t * a % p;
    for (int i = 1, j = qpow(a, m, p), t = 1LL * j * c % p; i <= m; i++) {
        if (mp.count(t)) return i * m - mp[t] + ret;
        t = 1LL * t * j % p;
    }
    return -1;
}
int a, b, p, ans;
signed main() {
    while (true) {
        scanf("%d%d%d", &a, &p, &b);
        if (!a && !b && !p)break;
        ans = exbsgs(a, b, p);
        if (ans == -1) puts("No Solution");
        else printf("%d\n", ans);
    }
    return 0;
}