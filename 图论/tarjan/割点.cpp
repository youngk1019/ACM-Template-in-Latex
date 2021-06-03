//Luogu P3388 【模板】割点（割顶）
//dfn[u]表示顶点u第几个被（首次）访问,low[u]表示顶点u及其子树中的点，通过非父子边（回边），能够回溯到的最早的点（dfn最小）的dfn值（但不能通过连接u与其父节点的边）
#include <bits/stdc++.h>
using namespace std;
#define maxn 20100
#define maxm 200100
int cnt, head[maxn], to[maxm], nxt[maxm];
int depth, top, s[maxn], dfn[maxn], low[maxn];
int n, m, x, y, ans;
bool iscut[maxn];
void add(int u, int v) { to[++cnt] = v, nxt[cnt] = head[u], head[u] = cnt; }
void tarjan(int u, int fa) {
    int ch = 0;
    dfn[u] = low[u] = ++depth, s[++top] = u;
    for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i]) {
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]), ch++;
            if (low[v] >= dfn[u] && u != fa) iscut[u] = true;
        } else if (v != fa) low[u] = min(low[u], dfn[v]);
    }
    if (ch >= 2 && u == fa) iscut[u] = true;
}
signed main() {
    scanf("%d%d", &n, &m);
    while (m--) {
        scanf("%d%d", &x, &y);
        add(x, y), add(y, x);
    }
    for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i, i);
    for (int i = 1; i <= n; i++) if (iscut[i]) ans++;
    printf("%d\n", ans);
    for (int i = 1; i <= n; i++) if (iscut[i]) printf("%d ",i);
    return 0;
}