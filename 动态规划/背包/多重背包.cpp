//Luogu P1776 宝物筛选
//单调队列优化O(n*m)
#include <bits/stdc++.h>
using namespace std;
#define maxn 40010
long long dp[maxn], ans, q[maxn];
int n, m, w, v, c, cnt, head, tail, num[maxn];
signed main() {
    scanf("%d%d", &m, &n);//物品个数，容积
    while (m--) {
        scanf("%d%d%d", &v, &w, &c);//价值，重量，个数
        if (w == 0) {
            ans += v * c;
            continue;
        }
        c = min(c, n / w);
        for (int j = 0; j < w; j++) {
            head = 1, tail = 0, cnt = (n - j) / w;
            for (int k = 0; k <= cnt; k++) {
                while (head <= tail && dp[j + k * w] - k * v >= q[tail])tail--;
                q[++tail] = dp[j + k * w] - k * v, num[tail] = k;
                while (head <= tail && num[head] + c < k) head++;
                dp[j + k * w] = max(dp[j + k * w], q[head] + k * v);
            }
        }
    }
    printf("%lld", dp[n] + ans);
    return 0;
}