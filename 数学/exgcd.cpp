//Luogu P5656 【模板】二元一次不定方程 (exgcd)
//若该方程无整数解，输出 -1。
//若该方程有整数解，且有正整数解，则输出其正整数解的数量，所有正整数解中 x的最小值，所有正整数解中 y的最小值，所有正整数解中 x的最大值，以及所有正整数解中 y的最大值。
//若方程有整数解，但没有正整数解，你需要输出所有整数解中 x的最小正整数值，y的最小正整数值。
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll x, y, mxx, mnx, mxy, mny, sum;
int a, b, c, d, t;
int exgcd(int a, int b, ll &x, ll &y) {
    if (!b) return x = 1, y = 0, a;
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
signed main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%lld%lld%lld", &a, &b, &c);
        d = exgcd(a, b, x, y);
        if (c % d) {
            puts("-1");
            continue;
        }
        a /= d, b /= d, c /= d;
        x *= c, y *= c;
        mnx = (x % b + b) % b;
        if (!mnx) mnx = b;
        mny = (y % a + a) % a;
        if (!mny) mny = a;
        mxx = (c - b * mny) / a;
        mxy = (c - a * mnx) / b;
        sum = (mxx - mnx) / b + 1;
        if (sum > 0) printf("%lld %lld %lld %lld %lld\n", sum, mnx, mny, mxx, mxy);
        else printf("%lld %lld\n", mnx, mny);
    }
    return 0;
}