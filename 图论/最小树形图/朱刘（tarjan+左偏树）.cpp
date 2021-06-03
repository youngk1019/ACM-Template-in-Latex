//Luogu P4716 【模板】最小树形图
//给定包含 n个结点，m条有向边的一个图。试求一棵以结点 r为根的最小树形图，并输出最小树形图每条边的权值之和，如果没有以 r为根的最小树形图，输出 -1
//最小树形图是以该根向外
//复杂度O((n+m)logn) 主要开双倍n空间
#include<bits/stdc++.h>
using namespace std;
#define maxn 110
#define maxm 10010
#define inf 0x3f3f3f3f
#define lc t[x].ls
#define rc t[x].rs
priority_queue<pair<int, int> > q;
int rt[maxn << 1], pre[maxn << 1], val[maxn << 1];
int n, m, r, ans, tot;
struct dsu {
    int f[maxn << 1];
    void init(int n) { for (int i = 1; i <= n; i++) f[i] = i; }
    int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
} D, id;
struct node {
    int x, y, w;
    bool operator<(const node &u) const { return w < u.w; }
    void work() { ans += w, pre[x] = pre[D.find(x)] = y, val[x] = val[D.find(x)] = w; }
};
struct tnode {
    node v;
    int ls, rs, d, tag;
    void add(int x) { tag += x, v.w += x; }
} t[maxm];
void pushdown(int x) { t[lc].add(t[x].tag), t[rc].add(t[x].tag), t[x].tag = 0; }
int merge(int x, int y) {
    if (!x || !y)return x | y;
    if (t[y].v < t[x].v)swap(x, y);
    pushdown(x), pushdown(y), rc = merge(y, rc);
    if (t[lc].d < t[rc].d)swap(lc, rc);
    return t[x].d = t[rc].d + 1, x;
}
void pop(int &x) { pushdown(x), x = merge(lc, rc); }
int work() {
    rt[r] = 0, t[0].v.w = inf;
    D.init(n), id.init(n);
    for (int i = 1; i <= n; i++) if (rt[i])q.emplace(-t[rt[i]].v.w, i);
    for (int u, v, p, flag = 1; --n; flag = 1) {
        while (flag) {
            if (q.empty()) return -1;
            u = q.top().second, q.pop();
            t[rt[u]].v.work(), v = t[rt[u]].v.y;
            pop(rt[u]), t[rt[u]].add(-val[u]);
            if (D.find(u) == D.find(v))continue;
            if (flag = (u == id.find(v))) {
                tot++, id.f[tot] = D.f[tot] = tot, p = D.find(v);
                do {
                    rt[tot] = merge(rt[p], rt[tot]);
                    D.f[p] = id.f[p] = tot, p = D.find(pre[p]);
                } while (p != tot);
                for (p = tot; rt[p] && D.find(t[rt[p]].v.y) == p; pop(rt[p]));
                if (rt[p])q.emplace(-t[rt[p]].v.w, p);
            } else id.f[u] = id.find(v);
        }
    }
    return ans;
}

int main() {
    scanf("%d%d%d", &n, &m, &r), tot = n;
    for (int x, y, w, i = 1; i <= m; i++)
        scanf("%d%d%d", &y, &x, &w), t[i].v = (node) {x, y, w}, rt[x] = merge(rt[x], i);
    printf("%d", work());
    return 0;
}