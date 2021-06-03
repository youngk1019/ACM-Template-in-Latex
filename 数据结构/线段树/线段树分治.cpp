//Lougu P5787 二分图 /【模板】线段树分治
//有一个 n 个节点的图,在 k 时间内有 m 条边会出现后消失,求出每一时间段内这个图是否是二分图
//x,y,l,r 表示有一条连接 x,y 的边在 l 时刻出现 r 时刻消失
//代码实现选择变为[l+1,r]时间存在这条边
//时间复杂度O(mlognlogk) 空间复杂度O(n)
#include <bits/stdc++.h>
using namespace std;
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
#define maxn 100100
int n, m, k, x, y, l, r;
struct dsu {
    int f[maxn << 1], depth[maxn << 1];
    stack<pair<int, int> > s;
    void init(int n) {
        for (int i = 1; i <= n; i++) f[i] = i;
        memset(depth + 1, 0, sizeof(int) * n);
        while (s.size()) s.pop();
    }
    int find(int x) {
        while (x ^ f[x]) x = f[x];
        return x;
    }
    void merge(int x, int y) {//合并的时候深度低的合并到深度高的上面去, x,y前需要find
        if (x == y) return;
        if (depth[x] > depth[y]) swap(x, y);
        s.push(make_pair(x, depth[x] == depth[y]));
        f[x] = y, depth[y] += depth[x] == depth[y];
    }
    void recall(int x) {//撤回到版本x 版本为s.size()
        while (s.size() > x) depth[f[s.top().first]] -= s.top().second, f[s.top().first] = s.top().first, s.pop();
    }
} D;
struct segment_tree {
    vector<pair<int, int> > v[maxn << 2];
    void insert(int p, int nl, int nr, int l, int r, pair<int, int> x) {
        if (nl <= l && r <= nr) return v[p].push_back(x), void();
        int mid = (l + r) >> 1;
        if (nl <= mid) insert(ls(p), nl, nr, l, mid, x);
        if (nr > mid) insert(rs(p), nl, nr, mid + 1, r, x);
    }
} T;
void dfs(int p, int l, int r) {
    bool ok = true;
    int ed = D.s.size();
    for (auto &u:T.v[p]) {
        int fx = D.find(u.first), fy = D.find(u.second);
        if (fx == fy) {
            for (int i = l; i <= r; i++) puts("No");
            ok = false;
            break;
        }
        D.merge(D.find(fx + n), fy), D.merge(D.find(fy + n), fx);
    }
    if (ok) {
        if (l == r) puts("Yes");
        else {
            int mid = (l + r) >> 1;
            dfs(ls(p), l, mid), dfs(rs(p), mid + 1, r);
        }
    }
    D.recall(ed);
}
signed main() {
    scanf("%d%d%d", &n, &m, &k);
    while (m--) {
        scanf("%d%d%d%d", &x, &y, &l, &r);
        if (l ^ r) T.insert(1, l + 1, r, 1, k, make_pair(x, y));
    }
    D.init(2 * n);
    dfs(1, 1, k);
    return 0;
}