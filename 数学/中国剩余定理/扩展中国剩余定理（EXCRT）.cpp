//Luogu P4777 【模板】扩展中国剩余定理（EXCRT）
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define maxn 100100
int n;
ll a[maxn], b[maxn];
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) return x = 1, y = 0, a;
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
ll qmul(ll a, ll b, ll mod) {
    ll ret = 0;
    a %= mod;
    while (b) {
        if (b & 1) ret = (ret + a) % mod;
        b >>= 1, a = (a << 1) % mod;
    }
    return ret;
}
ll excrt() {
    ll ans = b[1], x, y, m = a[1], bb, d;
    for (int i = 2; i <= n; i++) {
        bb = ((b[i] - ans) % a[i] + a[i]) % a[i];
        d = exgcd(m, a[i], x, y);
        x = qmul(x, bb / d, a[i]);
        ans += m * x, m *= a[i] / d;
        ans = (ans % m + m) % m;
    }
    return ans;
}
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld%lld", a + i, b + i);
    printf("%lld", excrt());
    return 0;
}