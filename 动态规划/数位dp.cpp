//Luogu P4127 [AHOI2009]同类分布
//求出[a,b]中各位数字之和能整除原数的数的个数
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll dp[20][200][200];
int len, a[20];
ll dfs(int pos, int sum, int k, bool lim, int mod) {
    if (pos == 0) return (sum == 0) && (k == mod);
    if (~dp[pos][sum][k] && !lim) return dp[pos][sum][k];
    int mx = lim ? a[pos] : 9;
    ll ret = 0;
    for (int i = 0; i <= mx; i++) ret += dfs(pos - 1, (sum * 10 + i) % mod, k + i, lim && (i == a[pos]), mod);
    return lim ? ret : dp[pos][sum][k] = ret;
}
ll part(ll x) {
    len = 0;
    while (x) a[++len] = x % 10, x /= 10;
    ll ret = 0;
    for (int i = 1; i <= len * 9; i++) {
        memset(dp, -1, sizeof(dp));
        ret += dfs(len, 0, 0, true, i);
    }
    return ret;
}
ll l, r;
signed main() {
    scanf("%lld%lld", &l, &r);
    printf("%lld", part(r) - part(l - 1));
    return 0;
}