//AtCoder ARC100E Or Plus Max
//给a[0...2^n-1], 求对于k (1 <= k <= 2^n - 1), 最大化A[i] + A[j]满足(0 <= i < j <= 2^n - 1 同时 (i or j) <= k)
//高维前缀和 复杂度O(n*2^n)
#include <bits/stdc++.h>
using namespace std;
signed main() {
    int n;
    scanf("%d", &n);
    vector<pair<int, int>> mx(1 << n); //维护最大值和次大值
    for (int i = 0; i < (1 << n); i++) {
        cin >> mx[i].first;
    }
    for (int i = 0; i < n; i++) { // 从第0维到第n-1维，所以先枚举维度
        for (int j = 0; j < (1 << n); j++) {
            if (j & (1 << i)) {
                auto &now = mx[j], &from = mx[j ^ (1 << i)];
                if (from.first > now.first) {
                    now.second = max(now.first, from.second);
                    now.first = from.first;
                } else {
                    now.second = max(now.second, from.first);
                }
            }
        }
    }
    int ans = 0;
    for (int i = 1; i < (1 << n); i++) {
        ans = max(ans, mx[i].first + mx[i].second);
        printf("%d\n", ans);
    }
    return 0;
}