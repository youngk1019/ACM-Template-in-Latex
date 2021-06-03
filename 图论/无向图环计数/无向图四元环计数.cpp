//无向图四元环计数(暂无原题)
//复杂度O(m^(3/2))
#include <bits/stdc++.h>
using namespace std;
#define maxn 100010
int n, m, x, y, deg[maxn], id[maxn], cnt[maxn], rk[maxn], ans;
vector<int> e[maxn], g[maxn];
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        e[x].push_back(y), e[y].push_back(x);
    }
    for (int i = 1; i <= n; i++) deg[id[i] = i] = e[i].size();
    sort(id + 1, id + n + 1, [&](int x, int y) {
        return deg[x] < deg[y] || (deg[x] == deg[y] && x < y);
    });
    for (int i = 1; i <= n; i++)rk[id[i]] = i;
    for (int u = 1; u <= n; u++) {
        for (auto &v:e[u]) if (rk[v] > rk[u]) g[u].push_back(v);
    }
    for (int u = 1; u <= n; u++) {
        for (auto &v:e[u]) for (auto &w:g[v])if (rk[w] > rk[u]) ans += cnt[w]++;
        for (auto &v:e[u]) for (auto &w:g[v])if (rk[w] > rk[u]) cnt[w] = 0;
    }
    printf("%d\n", ans);
    return 0;
}