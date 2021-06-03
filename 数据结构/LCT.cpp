//Lougu P3690 【模板】Link Cut Tree （动态树）
//操作0：格式：0 x y 含义：代表询问从 x到 y的路径上的点的权值的xor和。保证x到y是联通的
//操作1：格式：1 x y 含义：代表连接 x到 y，若 x到 y已经联通则无需连接。
//操作2：格式：2 x y 含义：代表删除边 (x,y)，不保证边 (x,y)存在。
//操作3：格式：3 x y 含义：代表将点 x上的权值变成 y。
#include<bits/stdc++.h>
using namespace std;
#define maxn 100010
struct LCT {
    int f[maxn], ch[maxn][2], s[maxn], v[maxn], a[maxn], c[maxn];
#define lc ch[p][0]
#define rc ch[p][1]
#define upd(p) s[p] = s[ch[p][0]] + s[ch[p][1]] + 1,c[p] = c[ch[p][0]] ^ c[ch[p][1]] ^ a[p]
#define get(p) (p == ch[f[p]][1])
#define rev(p) v[p] ^= 1,swap(ch[p][0],ch[p][1])
#define isrt(p) (ch[f[p]][0] != p && ch[f[p]][1] != p)
    void spd(int p) {
        if (p && v[p]) {
            if (lc) rev(lc);
            if (rc) rev(rc);
            v[p] = 0;
        }
    }
    void rot(int p) {
        int x = f[p], y = f[x], u = get(p), v = get(x), o = isrt(x);
        f[ch[p][u ^ 1]] = x, ch[x][u] = ch[p][u ^ 1];
        f[x] = p, ch[p][u ^ 1] = x, upd(x), upd(p);
        if ((f[p] = y) && !o) ch[y][v] = p;
    }
    void pre(int p) {
        if (!isrt(p)) pre(f[p]);
        spd(p);
    }
    void splay(int p) {
        pre(p);
        for (int x = f[p]; !isrt(p); rot(p), x = f[p]) {
            if (!isrt(x))rot(get(p) == get(x) ? x : p);
        }
    }
    void access(int p) { for (int x = 0; p; p = f[x = p]) splay(p), rc = x, upd(p); }
    void makert(int p) { access(p), splay(p), rev(p); }
    void split(int x, int y) { makert(x), access(y), splay(y); }
    int findrt(int p) {
        access(p), splay(p);
        while (lc) spd(p), p = lc;
        return splay(p), p;
    }
    bool link(int x, int y) { return makert(x), findrt(y) != x && (f[x] = y); }
    bool cut(int x, int y) {
        makert(x);
        if (findrt(y) != x || s[x] != 2) return false;
        return f[y] = ch[x][1] = 0, upd(x), true;
    }
    void change(int p, int x) { makert(p), a[p] = x, upd(p); }
} T;
int n, m, op, x, y;
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &T.a[i]), T.c[i] = T.a[i], T.s[i] = 1;
    while (m--) {
        scanf("%d%d%d", &op, &x, &y);
        if (op == 0) T.split(x, y), printf("%d\n", T.c[y]);
        else if (op == 1) T.link(x, y);
        else if (op == 2) T.cut(x, y);
        else if (op == 3) T.change(x, y);
    }
    return 0;
}