//Lougu P3369 【模板】普通平衡树
//1: 插入 x 数
//2: 删除 x 数(若有多个相同的数，因只删除一个)
//3: 查询 x 数的排名(排名定义为比当前数小的数的个数 +1 )
//4: 查询排名为 x 的数
//5: 求 x 的前驱(前驱定义为小于 x，且最大的数)
//6: 求 x 的后继(后继定义为大于 x，且最小的数)
#include<bits/stdc++.h>
using namespace std;
#define maxn 100010
struct Splay {
    int rt, tot, f[maxn], ch[maxn][2], a[maxn], c[maxn], s[maxn];
#define lc ch[p][0]
#define rc ch[p][1]
#define upd(p) s[p] = s[ch[p][0]] + s[ch[p][1]] + c[p]
#define get(p) (p == ch[f[p]][1])
#define clr(p) f[p] = ch[p][0] = ch[p][1] = a[p] = c[p] = s[p] = 0
    void rot(int p) {
        int x = f[p], y = f[x], u = get(p), v = get(x);
        f[ch[p][u ^ 1]] = x, ch[x][u] = ch[p][u ^ 1];
        f[x] = p, ch[p][u ^ 1] = x, upd(x), upd(p);
        if ((f[p] = y)) ch[y][v] = p;
    }
    void splay(int p, int g = 0) {
        for (int x = f[p]; (x = f[p]) != g; rot(p)) {
            if (f[x] != g) {
                rot(get(p) == get(x) ? x : p);
            }
        }
        if (!g) rt = p;
    }
    void ins(int k) {
        if (!rt) return a[rt = ++tot] = k, c[tot] = s[tot] = 1, void();
        int x = rt, y = 0;
        while (true) {
            if (a[x] == k) return ++c[x], ++s[x], upd(y), splay(x);
            y = x, x = ch[x][a[x] < k];
            if (!x) {
                a[++tot] = k, c[tot] = s[tot] = 1;
                f[tot] = y, ch[y][a[y] < k] = tot, upd(y);
                return splay(tot);
            }
        }
    }
    int rank(int k) {
        int p = rt, x = 0;
        while (true) {
            if (k < a[p]) {
                if (!lc) return splay(p), x + 1;
                p = lc;
            } else {
                x += s[lc];
                if (k == a[p]) return splay(p), x + 1;
                x += c[p];
                if (!rc) return splay(p), x + 1;
                p = rc;
            }
        }
    }
    int kth(int k) {
        int p = rt;
        while (true) {
            if (k <= s[lc]) p = lc;
            else {
                k -= s[lc];
                if (k <= c[p]) return splay(p), a[p];
                k -= c[p], p = rc;
            }
        }
    }
    int pre(int k) { return kth(rank(k) - 1); }
    int nxt(int k) { return kth(rank(k + 1)); }
    void del(int k) {
        rank(k);
        if (k != a[rt]) return;
        if (c[rt] > 1) return --c[rt], --s[rt], void();
        int p = rt;
        if (!lc && !rc) return rt = 0, clr(p), void();
        if (!lc || !rc) return f[rt = lc + rc] = 0, clr(p), void();
        return pre(k), f[rc] = rt, ch[rt][1] = rc, clr(p), --s[rt], void();
    }
} T;
int t, op, x;
signed main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &op, &x);
        if (op == 1) T.ins(x);
        else if (op == 2) T.del(x);
        else if (op == 3) printf("%d\n", T.rank(x));
        else if (op == 4) printf("%d\n", T.kth(x));
        else if (op == 5) printf("%d\n", T.pre(x));
        else if (op == 6) printf("%d\n", T.nxt(x));
    }
    return 0;
}