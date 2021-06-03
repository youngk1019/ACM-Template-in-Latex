//Lougu P1531 I Hate It
//操作1：格式：Q x y 含义：查询区间 [x,y] 内的最大值
//操作2：格式：U x y 含义：如果a[x]小于y则更新为y，否则不变，单点修改
#include <bits/stdc++.h>
using namespace std;
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
#define maxn 200100
int a[maxn], n, m, x, y;
char op;
struct segment_tree {
    int val[maxn << 2];
    void pushup(int p) {
        val[p] = max(val[ls(p)], val[rs(p)]);
    }
    void build(int p, int l, int r) {
        if (l == r) return val[p] = a[l], void();
        int mid = (l + r) >> 1;
        build(ls(p), l, mid), build(rs(p), mid + 1, r);
        pushup(p);
    }
    void update(int p, int l, int r, int x, int k) {
        if (x == l && x == r) {
            val[p] = max(val[p], k);//正常最值需要直接修改，不用取max
            return;
        }
        int mid = (l + r) >> 1;
        if (x <= mid) update(ls(p), l, mid, x, k);
        else update(rs(p), mid + 1, r, x, k);
        pushup(p);
    }
    int query(int p, int ql, int qr, int l, int r) {
        if (ql <= l && r <= qr) return val[p];
        int ret = 0x8f3f3f3f, mid = (l + r) >> 1;
        if (ql <= mid) ret = max(ret, query(ls(p), ql, qr, l, mid));
        if (qr > mid) ret = max(ret, query(rs(p), ql, qr, mid + 1, r));
        return ret;
    }
} T;
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    T.build(1, 1, n);
    while (m--) {
        scanf(" %c%d%d", &op, &x, &y);
        if (op == 'Q') printf("%d\n", T.query(1, x, y, 1, n));
        else T.update(1, 1, n, x, y);
    }
    return 0;
}
