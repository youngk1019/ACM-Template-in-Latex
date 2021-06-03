//P3379 【模板】最近公共祖先（LCA）
//Tarjan离线 时间复杂度O(n+m)
#include <bits/stdc++.h>
using namespace std;
#define maxn 500010
#define maxm 1000010
int n, m, s, x, y, ans[maxn];
int head[maxn], nxt[maxm], to[maxm], cnt;
int qhead[maxn], qnxt[maxm], qto[maxm], qid[maxm], qcnt;
bool vis[maxn];
struct dsu {
    int f[maxn];
    void init(int n) { for (int i = 1; i <= n; i++) f[i] = i; }
    int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
    bool merge(int x, int y) {//x为父亲，如果返回true则原本不为同一并查集
        int fx = find(x), fy = find(y);
        return f[fy] = fx, fx != fy;
    }
} D;
void add(int u, int v) { nxt[++cnt] = head[u], to[cnt] = v, head[u] = cnt; }
void addq(int u, int v, int id) { qnxt[++qcnt] = qhead[u], qto[qcnt] = v, qid[qcnt] = id, qhead[u] = qcnt; }
void tarjan(int u) {
    vis[u] = true;
    for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i]) if (vis[v] == false) tarjan(v), D.merge(u, v);
    for (int i = qhead[u]; i; i = qnxt[i]) if (vis[qto[i]]) ans[qid[i]] = D.find(qto[i]);
}
signed main() {
    scanf("%d%d%d", &n, &m, &s);
    D.init(n);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        add(x, y), add(y, x);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        addq(x, y, i), addq(y, x, i);
    }
    tarjan(s);
    for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
    return 0;
}