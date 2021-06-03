//Luogu P1495 【模板】中国剩余定理(CRT)/曹冲养猪
//任意i,j (a[i],a[j]) = 1
//M = \orod_{i=1}^{i=n}a[i] M[i] = M/a[i] M[i]t[i] ≡ 1 (mod m[i]) ans = \sum{b[i]M[i]t[i]}
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define maxn 20
int n, m[maxn], a[maxn], b[maxn];
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) return x = 1, y = 0, a;
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
ll crt() {
    ll t, x, y, ans = 0, mx = 1;
    for (int i = 1; i <= n; i++)mx *= a[i];
    for (int i = 1; i <= n; i++) {
        t = mx / a[i];
        exgcd(t, a[i], x, y);
        ans = ((ans + t * x % mx * b[i] % mx) + mx) % mx;
    }
    return ans;
}
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d", a + i, b + i);
    printf("%lld", crt());
    return 0;
}