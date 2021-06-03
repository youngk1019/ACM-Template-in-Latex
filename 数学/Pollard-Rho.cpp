//Luogu P4718 【模板】Pollard-Rho算法
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rd(RANDOM);
uniform_int_distribution<int> dis(0, INT16_MAX);
ll qmul(ll a, ll b, ll mod) {//快速乘 (a*b)%mod O(1)版
    return (a * b - (long long) ((long double) a / mod * b) * mod + mod) % mod;
}
ll qpow(ll a, ll b, ll mod) {
    ll ret = 1;
    while (b) {
        if (b & 1) ret = qmul(ret, a, mod);
        a = qmul(a, a, mod), b >>= 1;
    }
    return ret;
}
const ll check_prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 61, 97, 2333, 4567, 24351};
bool check(ll a, ll x) {
    if (qpow(a, x - 1, x) != 1) return false;
    ll temp = x - 1;
    while (!(temp & 1)) {
        temp >>= 1;
        ll _x = qpow(a, temp, x);
        if (_x != 1 && _x != x - 1) return false;
        if (_x == x - 1) return true;
    }
    return true;
}
bool miller_rabin(ll x) {
    if (x == 2) return true;
    if (x < 2 || !(x & 1)) return false;
    for (auto &a:check_prime) {
        if (a >= x)break;
        if (!check(a, x))return false;
    }
    return true;
}
ll Pollard_Rho(ll x) {
    ll s = 0, t = 0, c = dis(rd) % (x - 1) + 1, val = 1;
    int goal = 1;
    while (true) {
        for (int step = 1; step <= goal; ++step) {
            t = (qmul(t, t, x) + c) % x;
            val = qmul(val, abs(t - s), x);
            if ((step % 127) == 0) {
                ll d = __gcd(val, x);
                if (d > 1) return d;
            }
        }
        ll d = __gcd(val, x);
        if (d > 1) return d;
        goal <<= 1, s = t, val = 1;
    }
}

void fac(ll x, ll &max_factor) {
    if (x <= max_factor || x < 2) return;
    if (miller_rabin(x)) return max_factor = max(max_factor, x), void();
    ll p = x;
    while (p >= x) p = Pollard_Rho(x);
    while ((x % p) == 0) x /= p;
    fac(x, max_factor), fac(p, max_factor);
}
int t;
ll n, max_factor;
signed main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%lld", &n);
        max_factor = 0;
        fac(n, max_factor);
        if (max_factor == n) puts("Prime");
        else printf("%lld\n", max_factor);
    }
    return 0;
}