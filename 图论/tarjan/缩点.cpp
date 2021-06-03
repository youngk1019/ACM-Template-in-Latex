//Luogu P3387 【模板】缩点
//tarjan求强连通分量染色+缩点+拓扑排序dp
#include <bits/stdc++.h>
using namespace std;
#define maxn 10100
#define maxm 100100
int cnt, head[maxn], to[maxm], nxt[maxm];
int depth, top, color, col[maxn], sum[maxn], s[maxn], dfn[maxn], low[maxn];
int n, m, x[maxm], y[maxm], val[maxn], in[maxn], ans[maxn];
void add(int u, int v) { to[++cnt] = v, nxt[cnt] = head[u], head[u] = cnt; }
void tarjan(int u) {
    dfn[u] = low[u] = ++depth, s[++top] = u;
    for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i]) {
        if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if (!col[v]) low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        col[u] = ++color;
        while (s[top] != u) sum[color] += val[s[top]], col[s[top--]] = color;
        sum[color] += val[u], top--;
    }
}
int topo() {
    queue<int> q;
    for (int i = 1; i <= color; i++) if (in[i] == 0) q.push(i);
    while (q.size()) {
        auto u = q.front();
        q.pop(), ans[u] = max(ans[u], sum[u]);
        for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i]) {
            ans[v] = max(ans[v], ans[u] + sum[v]);
            if (--in[v] == 0) q.push(v);
        }
    }
    return *max_element(ans + 1, ans + color + 1);
}
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", val + i);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", x + i, y + i);
        add(x[i], y[i]);
    }
    for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);
    memset(head, 0, sizeof(head));
    memset(nxt, 0, sizeof(nxt));
    memset(to, 0, sizeof(to));
    cnt = 0;
    for (int i = 1; i <= m; i++) if (col[x[i]] != col[y[i]]) add(col[x[i]], col[y[i]]), in[col[y[i]]]++;
    printf("%d", topo());
    return 0;
}