//Luogu P1048 [NOIP2005 普及组] 采药
#include <bits/stdc++.h>
using namespace std;
#define maxn 1010
int dp[maxn], n, m, w, v;
signed main() {
    scanf("%d%d", &n, &m);
    while (m--) {
        scanf("%d%d", &w, &v);
        for (int i = n; i >= w; i--) dp[i] = max(dp[i], dp[i - w] + v);
    }
    printf("%d", dp[n]);
    return 0;
}