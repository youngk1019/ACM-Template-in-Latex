//codeforces CF1187E Tree Painting
#include <bits/stdc++.h>
using namespace std;
#define maxn 200100
int n, x, y, size[maxn];
long long dp[maxn];
vector<int> e[maxn];
long long dfs1(int u, int fa) {
    long long ret = 0;
    size[u] = 1;
    for (auto &v:e[u]) {
        if (v == fa)continue;
        ret += dfs1(v, u), size[u] += size[v];
    }
    return ret + size[u];
}
void dfs2(int u, int fa) {
    for (auto &v:e[u]) {
        if (v == fa)continue;
        dp[v] = dp[u] + n - 2 * size[v];
        dfs2(v, u);
    }
}
signed main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        e[x].push_back(y), e[y].push_back(x);
    }
    dp[1] = dfs1(1, 0);
    dfs2(1, 0);
    printf("%lld", *max_element(dp + 1, dp + n + 1));
    return 0;
}