//Lougu P3373 【模板】线段树2
//操作1：格式：1 x y k 含义：将区间 [x,y] 内每个数乘上 k
//操作2：格式：2 x y k 含义：将区间 [x,y] 内每个数加上 k
//操作3：格式：3 x y 含义：输出区间 [x,y] 内每个数的和对 p 取模所得的结果
//先乘后加
#include <bits/stdc++.h>
using namespace std;
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
#define maxn 100100
int a[maxn], n, m, mod, op, x, y, k;
struct segment_tree {
    int val[maxn << 2], tagadd[maxn << 2], tagmul[maxn << 2];
    void pushup(int p) {
        val[p] = (val[ls(p)] + val[rs(p)]) % mod;
    }
    void calcmul(int p, int k) {
        tagmul[p] = 1LL * tagmul[p] * k % mod;
        val[p] = 1LL * val[p] * k % mod;
    }
    void calcadd(int p, int l, int r, int add, int mul) {
        tagadd[p] = (1LL * tagadd[p] * mul % mod + add) % mod;
        val[p] = (val[p] + 1LL * add * (r - l + 1) % mod) % mod;
    }
    void pushdown(int p, int l, int r) {
        int mid = (l + r) >> 1;
        calcmul(ls(p), tagmul[p]), calcmul(rs(p), tagmul[p]);
        calcadd(ls(p), l, mid, tagadd[p], tagmul[p]);
        calcadd(rs(p), mid + 1, r, tagadd[p], tagmul[p]);
        tagadd[p] = 0, tagmul[p] = 1;
    }
    void build(int p, int l, int r) {
        tagmul[p] = 1;
        if (l == r) return val[p] = a[l] % mod, void();
        int mid = (l + r) >> 1;
        build(ls(p), l, mid), build(rs(p), mid + 1, r);
        pushup(p);
    }
    void updateadd(int p, int nl, int nr, int l, int r, int k) {
        if (nl <= l && r <= nr) {
            val[p] = (val[p] + 1LL * k * (r - l + 1) % mod) % mod;
            tagadd[p] = (tagadd[p] + k) % mod;
            return;
        }
        pushdown(p, l, r);
        int mid = (l + r) >> 1;
        if (nl <= mid) updateadd(ls(p), nl, nr, l, mid, k);
        if (nr > mid) updateadd(rs(p), nl, nr, mid + 1, r, k);
        pushup(p);
    }
    void updatemul(int p, int nl, int nr, int l, int r, int k) {
        if (nl <= l && r <= nr) {
            val[p] = 1LL * val[p] * k % mod;
            tagmul[p] = 1LL * tagmul[p] * k % mod;
            tagadd[p] = 1LL * tagadd[p] * k % mod;
            return;
        }
        pushdown(p, l, r);
        int mid = (l + r) >> 1;
        if (nl <= mid) updatemul(ls(p), nl, nr, l, mid, k);
        if (nr > mid) updatemul(rs(p), nl, nr, mid + 1, r, k);
        pushup(p);
    }
    int query(int p, int ql, int qr, int l, int r) {
        if (ql <= l && r <= qr) return val[p];
        int ret = 0, mid = (l + r) >> 1;
        pushdown(p, l, r);
        if (ql <= mid) ret = (ret + query(ls(p), ql, qr, l, mid)) % mod;
        if (qr > mid) ret = (ret + query(rs(p), ql, qr, mid + 1, r)) % mod;
        return ret;
    }
} T;
signed main() {
    scanf("%d%d%d", &n, &m, &mod);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    T.build(1, 1, n);
    while (m--) {
        scanf("%d", &op);
        if (op == 1) scanf("%d%d%d", &x, &y, &k), T.updatemul(1, x, y, 1, n, k);
        else if (op == 2) scanf("%d%d%d", &x, &y, &k), T.updateadd(1, x, y, 1, n, k);
        else scanf("%d%d", &x, &y), printf("%d\n", T.query(1, x, y, 1, n));
    }
    return 0;
}
