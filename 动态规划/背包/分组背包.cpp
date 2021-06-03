//P5322 [BJOI2019]排兵布阵
#include <bits/stdc++.h>
using namespace std;
#define maxn 310
int dp[maxn][maxn], sum[maxn], n, m, s, val[maxn];
vector<int> e[maxn];
void dfs(int u) {
    for (auto &v:e[u]) {
        dfs(v), sum[u] += sum[v];
        for (int i = sum[u]; i >= 1; i--) {
            for (int j = min(sum[v], i); j >= 1; j--) dp[u][i] = max(dp[u][i], dp[u][i - j] + dp[v][j]);
        }
    }
    for (int i = ++sum[u]; i >= 1; i--) dp[u][i] = dp[u][i - 1] + val[u];
}
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &s, val + i);
        e[s].push_back(i);
    }
    dfs(0);
    printf("%d\n", dp[0][m + 1]);//m+1是因为把0当做一个结点
    return 0;
}