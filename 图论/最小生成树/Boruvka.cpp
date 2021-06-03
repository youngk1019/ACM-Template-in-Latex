//CF 888G Xor-MST
//给定 n 个结点的无向完全图。每个点有一个点权为 a[i] 连接 i 号结点和 j 号结点的边权为a[i]^a[j],求最小生成树的权值
//Boruvka
#include <bits/stdc++.h>
using namespace std;
#define maxn 200100
struct dsu {
    int f[maxn];
    void init(int n) { for (int i = 1; i <= n; i++) f[i] = i; }
    int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
    bool merge(int x, int y) {//x为父亲，如果返回true则原本不为同一并查集
        int fx = find(x), fy = find(y);
        return f[fy] = fx, fx != fy;
    }
} D;
int trie[maxn << 6][2], cnt, rt[maxn], n, a[maxn], sz[maxn << 6], best[maxn], mn[maxn];
int tail[maxn << 6], x, y, z;
long long ans;
bool flag = true;
void insert(int p, int x, int tag) {
    for (int i = 30; i >= 0; i--) {
        bool y = (x >> i) & 1;
        if (!trie[p][y]) trie[p][y] = ++cnt;
        sz[p]++, p = trie[p][y];
    }
    sz[p]++, tail[p] = tag;
}
pair<int, int> query(int now, int pre, int x) {
    int ret = 0;
    for (int i = 30; i >= 0; i--) {
        bool y = (x >> i) & 1;
        if (trie[now][y] && sz[trie[now][y]] - sz[trie[pre][y]] > 0) now = trie[now][y], pre = trie[pre][y];
        else ret += (1 << i), now = trie[now][y ^ 1], pre = trie[pre][y ^ 1];
    }
    return make_pair(ret, tail[now]);
}
void merge(int &u, int v) {
    if (!u || !v) return u = u + v, void();
    merge(trie[u][0], trie[v][0]), merge(trie[u][1], trie[v][1]);
    sz[u] = sz[trie[u][0]] + sz[trie[u][1]];
}
signed main() {
    scanf("%d", &n);
    D.init(n), rt[0] = ++cnt;
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    sort(a + 1, a + n + 1), n = unique(a + 1, a + n + 1) - a - 1;//必须保证一个叶子节点只有一个值
    for (int i = 1; i <= n; i++) rt[i] = ++cnt, insert(rt[0], a[i], i), insert(rt[i], a[i], i);
    while (flag) {
        memset(mn, 0x3f, sizeof(mn)), flag = false;
        for (int i = 1; i <= n; i++) {
            x = D.find(i);
            auto ret = query(rt[0], rt[x], a[i]);
            y = D.find(ret.second), z = ret.first;
            if (x != y) {
                if (z < mn[x]) mn[x] = z, best[x] = y;
                if (z < mn[y]) mn[y] = z, best[y] = x;
            }
        }
        for (int i = 1; i <= n; i++) {
            int fx = D.find(i), fy = D.find(best[i]);
            if (mn[i] < 0x3f3f3f3f && fx != fy) {
                ans += mn[i], flag = true, merge(rt[fx], rt[fy]), D.merge(i, best[i]);
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}