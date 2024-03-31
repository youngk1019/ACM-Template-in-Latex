//Lougu P1441 砝码称重
//现有n个砝码,重量分别为a[i],在去掉m个砝码后,问最多能称量出多少不同的重量(不包括0)
//Gosper's Hack 二进制 n位1里面选k位1的子集, 复杂度C^{k}_{n}
#include <bits/stdc++.h>
using namespace std;
signed main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int cur = (1 << (n - m)) - 1, limit = (1 << n);
    int ans = 0;
    while (cur < limit) {
        vector<bool> dp(n * 100 + 1); // 砝码最大100
        dp[0] = true;
        int x = cur, j = 0;
        while (j < n) {
            if (x & 1) {
                for (int k = n * 100; k >= a[j]; k--) {
                    dp[k] = dp[k] | dp[k - a[j]];
                }
            }
            j++, x >>= 1;
        }
        int cnt = 0;
        for (int i = 1; i <= n * 100; i++) cnt += dp[i];
        ans = max(ans, cnt);
        int lb = cur & -cur;
        int r = cur + lb;
        cur = ((r ^ cur) >> __builtin_ctz(lb) + 2) | r;
        // 或：cur = (((r ^ cur) >> 2) / lb) | r;
    }
    printf("%d\n", ans);
    return 0;
}