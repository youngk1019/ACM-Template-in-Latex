//Luogu P6113 【模板】一般图最大匹配
//带花树 复杂度O(n(nlogn+m))
#include<bits/stdc++.h>
using namespace std;
#define maxn 1010
int n, m, x, y, cnt, ans;
int lk[maxn], tag[maxn], f[maxn], pre[maxn], dfn[maxn];
vector<int> e[maxn];
queue<int> q;
void link(int x, int y) { lk[x] = y, lk[y] = x; };
void add(int x, int y) {
    if (!lk[x] && !lk[y])link(x, y), ans++;
    e[x].push_back(y), e[y].push_back(x);
}
void rev(int x) { if (x)rev(lk[pre[x]]), link(x, pre[x]); }
int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
int lca(int x, int y) {
    cnt++;
    while (true) {
        if (dfn[x = find(x)] == cnt) return x;
        else if (x) dfn[x] = cnt;
        x = pre[lk[x]], swap(x, y);
    }
}
void shrink(int x, int y, int p) {
    while (find(x) != p) {
        pre[x] = y, y = lk[x], f[x] = f[y] = p;
        if (tag[y] == 2)tag[y] = 1, q.push(y);
        x = pre[y];
    }
}
bool blossom(int u) {
    memset(tag, 0, sizeof(tag));
    memset(pre, 0, sizeof(pre));
    for (int i = 1; i <= n; i++) f[i] = i;
    while (q.size()) q.pop();
    tag[u] = 1, q.push(u);
    int p;
    while (q.size()) {
        u = q.front(), q.pop();
        for (auto &v:e[u]) {
            if (tag[v] == 1) p = lca(u, v), shrink(u, v, p), shrink(v, u, p);
            else if (!tag[v]) {
                pre[v] = u, tag[v] = 2;
                if (!lk[v])return rev(v), true;
                else tag[lk[v]] = 1, q.push(lk[v]);
            }
        }
    }
    return false;
}
signed main() {
    scanf("%d%d", &n, &m);
    while (m--) {
        scanf("%d%d", &x, &y);
        add(x, y);
    }
    for (int i = 1; i <= n; i++) ans += !lk[i] && blossom(i);
    printf("%d\n", ans);
    for (int i = 1; i <= n; i++) printf("%d ", lk[i]);
    return 0;
}