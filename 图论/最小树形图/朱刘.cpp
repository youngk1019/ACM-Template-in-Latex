//Luogu P4716 【模板】最小树形图
//给定包含 n个结点，m条有向边的一个图。试求一棵以结点 r为根的最小树形图，并输出最小树形图每条边的权值之和，如果没有以 r为根的最小树形图，输出 -1
//最小树形图是以该根向外
//复杂度O(nm)
#include <bits/stdc++.h>
using namespace std;
#define maxn 110
#define maxm 10100
#define inf 0x3f3f3f3f
struct edge {
    int u, v, w;
} e[maxm];
int n, m, r, mn[maxn], fa[maxn], tp[maxn], lp[maxn], tot, ans;
int zl() {
    while (true) {
        memset(mn, 0x3f, sizeof(mn));
        memset(fa, 0, sizeof(fa));
        memset(tp, 0, sizeof(tp));
        memset(lp, 0, sizeof(lp));
        for (int i = 1, v; i <= m; i++)
            if (e[i].u != e[i].v && e[i].w < mn[v = e[i].v])
                mn[v] = e[i].w, fa[v] = e[i].u;
        mn[r] = 0;
        for (int u = 1; u <= n; u++) {
            ans += mn[u];
            if (mn[u] == inf) return -1;
        }
        for (int u = 1, v = 1; u <= n; u++, v = u) {
            while (v != r && tp[v] != u && !lp[v]) tp[v] = u, v = fa[v];
            if (v != r && !lp[v]) {
                lp[v] = ++tot;
                for (int k = fa[v]; k != v; k = fa[k]) lp[k] = tot;
            }
        }
        if (!tot) return ans;
        for (int i = 1; i <= n; i++) if (!lp[i]) lp[i] = ++tot;
        for (int i = 1; i <= m; i++) e[i].w -= mn[e[i].v], e[i].u = lp[e[i].u], e[i].v = lp[e[i].v];
        n = tot, r = lp[r], tot = 0;
    }
}
int main() {
    scanf("%d%d%d", &n, &m, &r);
    for (int i = 1, u, v, w; i <= m; i++) scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
    printf("%d", zl());
    return 0;
}