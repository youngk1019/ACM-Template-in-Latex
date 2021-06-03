//Luogu P4720 【模板】扩展卢卡斯
//计算C_{n}^{m} mod p ,p 不一定为质数
//复杂度O(plogp)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll qpow(ll a, ll b, ll mod) {
    ll ret = 1;
    a %= mod;
    while (b) {
        if (b & 1) ret = ret * a % mod;
        a = a * a % mod, b >>= 1;
    }
    return ret;
}
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) return x = 1, y = 0, a;
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
ll fac(ll n, ll pi, ll pk) {
    if (!n)return 1;
    ll ret = 1, lim = n % pk;
    for (ll i = 2; i <= pk; ++i) if (i % pi) ret = ret * i % pk;
    ret = qpow(ret, n / pk, pk);
    for (ll i = 2; i <= lim; ++i) if (i % pi) ret = ret * i % pk;
    return ret * fac(n / pi, pi, pk) % pk;
}
ll inv(ll n, ll mod) {
    ll x, y;
    exgcd(n, mod, x, y);
    return (x + mod) % mod;
}
ll CRT(ll b, ll mod, ll p) { return b * inv(p / mod, mod) % p * (p / mod) % p; }
ll C(ll n, ll m, ll pi, ll pk) {
    ll up = fac(n, pi, pk), d1 = fac(m, pi, pk), d2 = fac(n - m, pi, pk), k = 0;
    for (ll i = n; i; i /= pi) k += i / pi;
    for (ll i = m; i; i /= pi) k -= i / pi;
    for (ll i = n - m; i; i /= pi) k -= i / pi;
    return up * inv(d1, pk) % pk * inv(d2, pk) % pk * qpow(pi, k, pk) % pk;
}
ll exlucas(ll n, ll m, ll p) {
    ll ret = 0, tmp = p, pk;
    int lim = ceil(sqrt(p));
    for (int i = 2; i <= lim; ++i) {
        if (tmp % i == 0) {
            pk = 1;
            while (tmp % i == 0) pk *= i, tmp /= i;
            ret = (ret + CRT(C(n, m, i, pk), pk, p)) % p;
        }
    }
    if (tmp > 1) ret = (ret + CRT(C(n, m, tmp, tmp), tmp, p)) % p;
    return ret;
}
ll n, m, p;
signed main() {
    scanf("%lld%lld%lld", &n, &m, &p);
    printf("%lld\n", exlucas(n, m, p));
    return 0;
}