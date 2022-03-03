//P4148 简单题
//有一个N×N的棋盘，每个格子内有一个整数，初始时的时候全部为0，现在需要维护两种操作
//操作1：格式：1 x y A 含义：将格子(x,y)里的数字加上 A
//操作2：格式：2 x1 y1 x2 y2 含义：输出 x1, y1, x2, y2这个矩形内的数字和
//操作3：格式：3 含义：终止程序
//局部重构 alpha = 0.6/0.75
#include <bits/stdc++.h>
using namespace std;
#define maxn 200010
struct kdt {
    const double alpha = 0.75;
    struct point {
        int x[2], val;
        point() {};
        point(int x, int y, int val) : val(val) { this->x[0] = x, this->x[1] = y; }
        bool in(int x1, int y1, int x2, int y2) { return x[0] >= x1 && x[0] <= x2 && x[1] >= y1 && x[1] <= y2; }
    } pt[maxn];
    struct node {
        int ls, rs, mn[2], mx[2], sum, sz;
        point p;
        bool in(int x1, int y1, int x2, int y2) { return mn[0] >= x1 && mx[0] <= x2 && mn[1] >= y1 && mx[1] <= y2; }
        bool out(int x1, int y1, int x2, int y2) { return mx[0] < x1 || mn[0] > x2 || mx[1] < y1 || mn[1] > y2; }
    } a[maxn];
    kdt() { a[0].mn[0] = a[0].mn[1] = INT32_MAX, a[0].mx[0] = a[0].mx[1] = INT32_MIN; }
    int buf[maxn], cnt, tot, rt;
    void slap(int u) {
        if (!u)return;
        buf[++tot] = u, pt[tot] = a[u].p;
        slap(a[u].ls), slap(a[u].rs);
    }
    int newnode() { return tot ? buf[tot--] : ++cnt; }
    int query(int u, int x1, int y1, int x2, int y2) {
        if (a[u].in(x1, y1, x2, y2))return a[u].sum;
        if (a[u].out(x1, y1, x2, y2))return 0;
        return (a[u].p.in(x1, y1, x2, y2) ? a[u].p.val : 0) + query(a[u].ls, x1, y1, x2, y2) +
               query(a[u].rs, x1, y1, x2, y2);
    }
    void pushup(int p) {
        auto &u = a[p], &l = a[u.ls], &r = a[u.rs];
        u.sum = u.p.val + l.sum + r.sum, u.sz = l.sz + r.sz + 1;
        for (int i = 0; i <= 1; i++) {
            u.mn[i] = min({u.p.x[i], l.mn[i], r.mn[i]});
            u.mx[i] = max({u.p.x[i], l.mx[i], r.mx[i]});
        }
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
    void insert(int &u, point p, int k) {
        if (!u) return u = newnode(), a[u].ls = a[u].rs = 0, a[u].p = p, pushup(u), void();
        if (p.x[k] <= a[u].p.x[k]) insert(a[u].ls, p, k ^ 1);
        else insert(a[u].rs, p, k ^ 1);
        pushup(u), maintain(u, k);
    }
} T;
int n, ans, op, x, y, xx, yy, k;
signed main() {
    scanf("%d", &n);
    while (scanf("%d", &op), op != 3) {
        if (op == 1) {
            scanf("%d%d%d", &x, &y, &k);
            T.insert(T.rt, {x ^ ans, y ^ ans, k ^ ans}, 0);
        } else {
            scanf("%d%d%d%d", &x, &y, &xx, &yy);
            printf("%d\n", ans = T.query(T.rt, x ^ ans, y ^ ans, xx ^ ans, yy ^ ans));
        }
    }
    return 0;
}