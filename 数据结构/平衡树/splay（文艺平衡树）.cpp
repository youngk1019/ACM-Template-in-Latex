//Lougu P3391 【模板】文艺平衡树
//区间翻转  开头和末尾需要插入值inf 支持某个位置插入 某个位置删除
#include<bits/stdc++.h>
using namespace std;
#define maxn 100010
#define inf 0x3f3f3f3f
int n, q, l, r, b[maxn];
struct Splay {
    int rt, tot, f[maxn], ch[maxn][2], a[maxn], s[maxn], v[maxn];
#define lc ch[p][0]
#define rc ch[p][1]
#define upd(p) s[p] = s[ch[p][0]] + s[ch[p][1]] + 1
#define get(p) (p == ch[f[p]][1])
#define rev(p) v[p] ^= 1,swap(ch[p][0],ch[p][1])
    void spd(int p) {
        if (p && v[p]) {
            if (lc) rev(lc);
            if (rc) rev(rc);
            v[p] = 0;
        }
    }
    void rot(int p) {
        int x = f[p], y = f[x], u = get(p), v = get(x);
        f[ch[p][u ^ 1]] = x, ch[x][u] = ch[p][u ^ 1];
        f[x] = p, ch[p][u ^ 1] = x, upd(x), upd(p);
        if ((f[p] = y)) ch[y][v] = p;
    }
    void splay(int p, int g = 0) {
        for (int x = f[p]; (x = f[p]) != g; rot(p)) {
            if (f[x] != g) rot(get(p) == get(x) ? x : p);
        }
        if (!g) rt = p;
    }
    int kth(int k) {
        int p = rt;
        while (true) {
            spd(p);
            if (k <= s[lc]) p = lc;
            else {
                k -= s[lc];
                if (k <= 1) return p;
                k -= 1, p = rc;
            }
        }
    }
    void insert(int x, int val) {
        splay(kth(x - 1));
        splay(kth(x), rt);
        int p = ch[ch[rt][1]][0] = ++tot;
        f[p] = ch[rt][1], a[p] = val, s[p] = 1;
        upd(ch[rt][1]), upd(rt);
    }
    void del(int x) {
        splay(kth(x - 1));
        splay(kth(x + 1), rt);
        ch[ch[rt][1]][0] = 0;
        upd(ch[rt][1]), upd(rt);
    }
    int build(int l, int r, int fa = 0) {
        if (l > r) return 0;
        int p = ++tot, mid = (l + r) >> 1;
        f[p] = fa, a[p] = b[mid];
        ch[p][0] = build(l, mid - 1, p);
        ch[p][1] = build(mid + 1, r, p);
        return upd(p), p;
    }
    int getkth(int x) {
        int p = kth(x);
        return splay(p), a[p];
    }
    void reverse(int l, int r) { l = kth(l - 1), r = kth(r + 1), splay(l), splay(r, l), rev(ch[r][0]); }
    void print(int p) {
        spd(p);
        if (lc) print(lc);
        if (a[p] != inf) printf("%d ", a[p]);
        if (rc) print(rc);
    }
} T;
signed main() {
    scanf("%d%d", &n, &q);
    b[1] = b[n + 2] = inf;
    for (int i = 2; i <= n + 1; i++) {
        b[i] = i - 1;
    }
    T.rt = T.build(1, n + 2);
    while (q--) {
        scanf("%d%d", &l, &r);
        T.reverse(l + 1, r + 1);
    }
    T.print(T.rt);
    return 0;
}