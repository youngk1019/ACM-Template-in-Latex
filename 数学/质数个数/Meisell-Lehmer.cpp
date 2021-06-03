//hdu 5901 Count primes
//Meisell-Lehmer 复杂度O(n^(2/3))
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define maxn 1000010
int prime[maxn], cnt, sum[maxn];
bool flag[maxn];
const int M = 7;
const int PM = 2 * 3 * 5 * 7 * 11 * 13 * 17;
int phi[PM + 1][M + 1], sz[M + 1];
void sieve() {
    for (int i = 2; i < maxn; i++) {
        sum[i] = sum[i - 1];
        if (!flag[i]) prime[++cnt] = i, sum[i]++;
        for (int j = 1; j <= cnt && i * prime[j] < maxn; j++) {
            flag[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
        }
    }
    sz[0] = 1;
    for (int i = 0; i <= PM; ++i) phi[i][0] = i;
    for (int i = 1; i <= M; ++i) {
        sz[i] = prime[i] * sz[i - 1];
        for (int j = 1; j <= PM; ++j) phi[j][i] = phi[j][i - 1] - phi[j / prime[i]][i - 1];
    }
}
int sqrt2(ll x) {
    ll r = (ll) sqrt(x - 0.1);
    while (r * r <= x) ++r;
    return r - 1;
}
int sqrt3(ll x) {
    ll r = (ll) cbrt(x - 0.1);
    while (r * r * r <= x) ++r;
    return r - 1;
}
ll getphi(ll x, int s) {
    if (s == 0) return x;
    if (s <= M) return phi[x % sz[s]][s] + (x / sz[s]) * phi[sz[s]][s];
    if (x <= prime[s] * prime[s]) return sum[x] - s + 1;
    if (x <= prime[s] * prime[s] * prime[s] && x < maxn) {
        int s2x = sum[sqrt2(x)];
        ll ans = sum[x] - (s2x + s - 2) * (s2x - s + 1) / 2;
        for (int i = s + 1; i <= s2x; ++i) ans += sum[x / prime[i]];
        return ans;
    }
    return getphi(x, s - 1) - getphi(x / prime[s], s - 1);
}
ll getpi(ll x) {
    if (x < maxn) return sum[x];
    ll ans = getphi(x, sum[sqrt3(x)]) + sum[sqrt3(x)] - 1;
    for (int i = sum[sqrt3(x)] + 1, ed = sum[sqrt2(x)]; i <= ed; ++i) ans -= getpi(x / prime[i]) - i + 1;
    return ans;
}
ll calc(ll x) {
    if (x < maxn) return sum[x];
    int a = (int) calc(sqrt2(sqrt2(x)));
    int b = (int) calc(sqrt2(x));
    int c = (int) calc(sqrt3(x));
    ll sum = getphi(x, a) + 1LL * (b + a - 2) * (b - a + 1) / 2;
    for (int i = a + 1; i <= b; i++) {
        ll w = x / prime[i];
        sum -= calc(w);
        if (i > c) continue;
        ll lim = calc(sqrt2(w));
        for (int j = i; j <= lim; j++) sum -= calc(w / prime[j]) - (j - 1);
    }
    return sum;
}
ll n;
int main() {
    sieve();
    while (~scanf("%lld", &n)) printf("%lld\n", calc(n));
    return 0;
}