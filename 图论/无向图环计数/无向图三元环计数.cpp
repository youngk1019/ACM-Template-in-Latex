//Luogu P1989 无向图三元环计数
//复杂度O(m^(3/2))
#include <bits/stdc++.h>
using namespace std;
#define maxn 100010
#define maxm 200010
int n, m, x[maxm], y[maxm], deg[maxn], vis[maxn], ans;
vector<int> e[maxn];
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", x + i, y + i);
        deg[x[i]]++, deg[y[i]]++;
    }
    for (int i = 1; i <= m; i++) {
        if ((deg[x[i]] > deg[y[i]]) || (deg[x[i]] == deg[y[i]] && x[i] > y[i]))e[y[i]].push_back(x[i]);
        else e[x[i]].push_back(y[i]);
    }
    for (int u = 1; u <= n; u++) {
        for (auto &v:e[u]) vis[v] = u;
        for (auto &v:e[u]) {
            for (auto &w:e[v]) ans += (vis[w] == u);
        }
    }
    printf("%d\n", ans);
    return 0;
}