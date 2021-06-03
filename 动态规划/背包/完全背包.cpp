//Luogu P1616 疯狂的采药
#include <bits/stdc++.h>
using namespace std;
#define maxn 10000100
long long dp[maxn];
int n, m, w, v;
signed main() {
    scanf("%d%d", &n, &m);
    while (m--) {
        scanf("%d%d", &w, &v);
        for (int i = w; i <= n; i++) dp[i] = max(dp[i], dp[i - w] + v);
    }
    printf("%lld", dp[n]);
    return 0;
}