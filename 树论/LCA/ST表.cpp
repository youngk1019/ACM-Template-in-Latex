//P3379 【模板】最近公共祖先（LCA）
//ST表 预处理O(nlogn) 查询O(m)
//dft需要开两倍空间
#include <bits/stdc++.h>
using namespace std;
#define maxn 500010
#define maxm 1000010
int n, m, s, x, y, depth[maxm], f[maxm][20], lg[maxm], id[maxm], vis[maxm], dft;
int head[maxn], nxt[maxm], to[maxm], cnt;
void add(int u, int v) { nxt[++cnt] = head[u], to[cnt] = v, head[u] = cnt; }
void dfs(int u, int fa) {
    id[u] = ++dft, vis[dft] = u, depth[dft] = depth[id[fa]] + 1;
    for (int i = head[u]; i; i = nxt[i]) {
        if (to[i] == fa)continue;
        dfs(to[i], u), vis[++dft] = u, depth[dft] = depth[id[fa]] + 1;
    }
}
void rmq() {
    for (int i = 1; i <= dft; i++) lg[i] = lg[i - 1] + ((1 << lg[i - 1]) == i);
    for (int i = 1; i <= dft; i++) f[i][0] = i;
    for (int i = 1; (1 << i) <= dft; i++) {
        for (int j = 1; j + (1 << i) - 1 <= dft; j++) {
            int x = f[j][i - 1], y = f[j + (1 << (i - 1))][i - 1];
            f[j][i] = (depth[x] <= depth[y]) ? x : y;
        }
    }
}
int query(int l, int r) {
    l = id[l], r = id[r];
    if (r < l)swap(l, r);
    int k = lg[r - l + 1] - 1;
    int x = f[l][k], y = f[r - (1 << k) + 1][k];
    return (depth[x] <= depth[y]) ? vis[x] : vis[y];
}
signed main() {
    scanf("%d%d%d", &n, &m, &s);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        add(x, y), add(y, x);
    }
    dfs(s, 0), rmq();
    while (m--) {
        scanf("%d%d", &x, &y);
        printf("%d\n", query(x, y));
    }
    return 0;
}