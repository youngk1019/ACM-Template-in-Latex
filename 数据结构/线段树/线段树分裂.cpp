//P5494 【模板】线段树分裂
//操作0：格式：0 p x y 含义：将可重集 p 中大于等于 x 且小于等于 y 的值放入一个新的可重集中（新可重集编号为从 2 开始的正整数，是上一次产生的新可重集的编号+1）
//操作1：格式：1 p t   含义：将可重集 t 中的数放入可重集 p，且清空可重集 t（数据保证在此后的操作中不会出现可重集 t）
//操作2：格式：2 p x q 含义：在 p 这个可重集中加入 x 个数字 q
//操作3：格式：3 p x y 含义：查询可重集 p 中大于等于 x 且小于等于 y 的值的个数
//格式4：格式：4 p k   含义:查询在 p 这个可重集中第 k 小的数，不存在时输出 -1
//第一行两个整数 n,m，表示可重集中的数在 1~n 的范围内，有 m 个操作
//接下来一行 n 个整数，表示 1~n 这些数在编号为1的可重集中出现的次数
//时间复杂度O(nlogn) 空间复杂度O(nlogn)带合并空间优化
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define maxn 200010
int n, m, op, p, x, y, k, q, t, cnt = 1;
ll q1, q2;
struct seqment_tree {
    int cnt, ls[maxn << 5], rs[maxn << 5], rt[maxn], tot, bac[maxn << 5];
    ll val[maxn << 5];
    int newnode() { return tot ? bac[tot--] : ++cnt; }
    void del(int x) { return bac[++tot] = x, ls[x] = rs[x] = val[x] = 0, void(); }
    void modify(int &p, int l, int r, int x, int k) {
        if (!p) p = newnode();
        val[p] += k;
        if (l == r) return;
        int mid = (l + r) >> 1;
        if (x <= mid) modify(ls[p], l, mid, x, k);
        else modify(rs[p], mid + 1, r, x, k);
    }
    ll query(int p, int ql, int qr, int l, int r) {
        if (ql <= l && r <= qr) return val[p];
        ll ret = 0;
        int mid = (l + r) >> 1;
        if (ql <= mid) ret += query(ls[p], ql, qr, l, mid);
        if (qr > mid) ret += query(rs[p], ql, qr, mid + 1, r);
        return ret;
    }
    int kth(int p, int l, int r, ll k) {
        if (l == r) return l;
        int mid = (l + r) >> 1;
        if (k <= val[ls[p]]) return kth(ls[p], l, mid, k);
        else return kth(rs[p], mid + 1, r, k - val[ls[p]]);
    }
    void merge(int &a, int b) {//树b合并到树a中
        if (!a || !b) return a = a + b, void();
        val[a] += val[b];
        merge(ls[a], ls[b]), merge(rs[a], rs[b]);
        del(b);
    }
    void split(int a, int &b, ll k) {//树a中分裂出树b
        if (!a) return;
        b = newnode();
        if (k > val[ls[a]]) split(rs[a], rs[b], k - val[ls[a]]);
        else swap(rs[a], rs[b]);
        if (k < val[ls[a]]) split(ls[a], ls[b], k);
        val[b] = val[a] - k, val[a] = k;
    }
} T;
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &x);
        T.modify(T.rt[cnt], 1, n, i, x);
    }
    while (m--) {
        scanf("%d", &op);
        if (op == 0) {
            scanf("%d%d%d", &p, &x, &y);
            q1 = T.query(T.rt[p], 1, y, 1, n), q2 = T.query(T.rt[p], x, y, 1, n);
            T.split(T.rt[p], T.rt[++cnt], q1 - q2);
            T.split(T.rt[cnt], k, q2);
            T.merge(T.rt[p], k);
        } else if (op == 1) {
            scanf("%d%d", &p, &t);
            T.merge(T.rt[p], T.rt[t]);
        } else if (op == 2) {
            scanf("%d%d%d", &p, &x, &q);
            T.modify(T.rt[p], 1, n, q, x);
        } else if (op == 3) {
            scanf("%d%d%d", &p, &x, &y);
            printf("%lld\n", T.query(T.rt[p], x, y, 1, n));
        } else if (op == 4) {
            scanf("%d%d", &p, &k);
            if (T.val[T.rt[p]] < k) puts("-1");
            else printf("%d\n", T.kth(T.rt[p], 1, n, k));
        }
    }
    return 0;
}