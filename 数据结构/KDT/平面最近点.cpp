//P4169 [Violet]天使玩偶/SJY摆棋子
//平面哈夫曼距离最近点
//先插入n个点 后m个操作
//操作1：格式：1 x y 含义：新插入点(x,y)
//操作2：格式：2 x y 含义：查询离它最近的点有多远
//定期+局部重构
#include <bits/stdc++.h>
using namespace std;
#define maxn 600010
struct kdt {
    const double alpha = 0.75;
    struct point {
        int x[2];
        point() {};
        point(int x, int y) { this->x[0] = x, this->x[1] = y; }
        bool in(int x1, int y1, int x2, int y2) { return x[0] >= x1 && x[0] <= x2 && x[1] >= y1 && x[1] <= y2; }
    } pt[maxn];
    struct node {
        int ls, rs, mn[2], mx[2], sz;
        point p;
        bool in(int x1, int y1, int x2, int y2) { return mn[0] >= x1 && mx[0] <= x2 && mn[1] >= y1 && mx[1] <= y2; }
        bool out(int x1, int y1, int x2, int y2) { return mx[0] < x1 || mn[0] > x2 || mx[1] < y1 || mn[1] > y2; }
        int H(point &p) {
            int x = p.x[0], y = p.x[1];
            return max(0, mn[0] - x) + max(0, x - mx[0]) + max(0, mn[1] - y) + max(0, y - mx[1]);
        }
    } a[maxn];
    kdt() { a[0].mn[0] = a[0].mn[1] = INT32_MAX, a[0].mx[0] = a[0].mx[1] = INT32_MIN; }
    int buf[maxn], cnt, tot, rt, ans;
    void pushup(int p) {
        auto &u = a[p], &l = a[u.ls], &r = a[u.rs];
        u.sz = l.sz + r.sz + 1;
        for (int i = 0; i <= 1; i++) {
            u.mn[i] = min({u.p.x[i], l.mn[i], r.mn[i]});
            u.mx[i] = max({u.p.x[i], l.mx[i], r.mx[i]});
        }
    }
    void slap(int u) {
        if (!u)return;
        buf[++tot] = u, pt[tot] = a[u].p;
        slap(a[u].ls), slap(a[u].rs);
    }
    int newnode() { return tot ? buf[tot--] : ++cnt; }
    void rebuild() {
        for (int i = 1; i <= cnt; i++) pt[i] = a[i].p;
        int up = cnt;
        cnt = 0, rt = rebuild(1, up, 0);
    }
    int rebuild(int l, int r, int k) {
        if (l > r)return 0;
        int mid = (l + r) >> 1, u = newnode();
        nth_element(pt + l, pt + mid, pt + r + 1, [&](point a, point b) { return a.x[k] < b.x[k]; });
        a[u].p = pt[mid], a[u].ls = rebuild(l, mid - 1, k ^ 1), a[u].rs = rebuild(mid + 1, r, k ^ 1);
        return pushup(u), u;
    }
    void maintain(int &u, int k) {
        if (a[u].sz * alpha < a[a[u].ls].sz || a[u].sz * alpha < a[a[u].rs].sz) slap(u), u = rebuild(1, tot, k);
    }
    void insert(point p) { insert(rt, p); }
    void insert(int &u, point &p, int k = 0) {
        if (!u) return u = newnode(), a[u].ls = a[u].rs = 0, a[u].p = p, pushup(u), void();
        if (p.x[k] <= a[u].p.x[k]) insert(a[u].ls, p, k ^ 1);
        else insert(a[u].rs, p, k ^ 1);
        pushup(u), maintain(u, k);
    }
    int dis(point &a, point &b) { return abs(a.x[0] - b.x[0]) + abs(a.x[1] - b.x[1]); }
    int query(point p) { return ans = INT32_MAX, query(rt, p), ans; }
    void query(int u, point &p) {
        int lv = INT32_MAX, rv = INT32_MAX;
        if (!u)return;
        ans = min(ans, dis(p, a[u].p));
        if (a[u].ls) lv = a[a[u].ls].H(p);
        if (a[u].rs) rv = a[a[u].rs].H(p);
        if (lv < rv) {
            if (lv < ans) query(a[u].ls, p);
            if (rv < ans) query(a[u].rs, p);
        } else {
            if (rv < ans) query(a[u].rs, p);
            if (lv < ans) query(a[u].ls, p);
        }
    }
} T;
int n, m, op, x, y;
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &x, &y);
        T.a[i].p = {x, y};
    }
    T.cnt = n, T.rebuild();
    while (m--) {
        scanf("%d%d%d", &op, &x, &y);
        if (op == 1) T.insert({x, y});
        else printf("%d\n", T.query({x, y}));
    }
    return 0;
}