//AtCoder ARC100E Or Plus Max
//给a[0...2^n-1], 求对于k (1 <= k <= 2^n - 1), 最大化A[i] + A[j]满足(0 <= i < j <= 2^n - 1 同时 (i or j) <= k)
//子集枚举 复杂度O(3^n) 枚举子集的时候不会枚举0
#include <bits/stdc++.h>
using namespace std;
signed main() {
    int n;
    scanf("%d", &n);
    vector<int> a(1 << n), mx(1 << n), dp(1 << n);
    for (int i = 0; i < (1 << n); i++) {
        cin >> a[i];
        mx[i] = a[0]; //枚举子集的时候不会枚举0 所以要先处理
    }
    for (int i = 0; i < (1 << n); i++) {
        for (int j = i; j; j = (j - 1) & i) {
            dp[i] = max(dp[i], a[j] + mx[i]);
            mx[i] = max(mx[i], a[j]);
        }
    }
    for (int i = 1; i < (1 << n); i++) {
        dp[i] = max(dp[i - 1], dp[i]);
        printf("%d\n", dp[i]);
    }
    return 0;
}