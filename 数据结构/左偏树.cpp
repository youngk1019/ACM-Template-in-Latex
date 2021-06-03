//Luogu P3377 【模板】左偏树（可并堆）
//操作1：格式：1 x y含义：将第 x个数和第 y个数所在的小根堆合并（若第 x或第 y个数已经被删除或第 x和第 y个数在用一个堆内，则无视此操作）
//操作2：格式：2 x  含义：输出第 x个数所在的堆最小数，并将这个最小数删除（若有多个最小数，优先删除先输入的；若第 x个数已经被删除，则输出 -1并无视删除操作）
//如果弹出，则值变为-1
#include <bits/stdc++.h>
using namespace std;
#define maxn 100100
int n, m, op, x, y;
struct leftist_tree {
    int val[maxn], ls[maxn], rs[maxn], rt[maxn], dis[maxn];
    void init(int n) {
        dis[0] = -1;
        for (int i = 1; i <= n; i++) rt[i] = i;
    }
    int find(int x) { return rt[x] == x ? x : rt[x] = find(rt[x]); }
    void pop(int x) { val[x] = -1, rt[ls[x]] = ls[x], rt[rs[x]] = rs[x], rt[x] = _merge(ls[x], rs[x]); }
    int _merge(int a, int b) {
        if (!a || !b) return a + b;
        if (val[a] > val[b] || (val[a] == val[b] && a > b)) swap(a, b);
        rs[a] = _merge(rs[a], b);
        if (dis[ls[a]] < dis[rs[a]]) swap(ls[a], rs[a]);
        return rt[ls[a]] = rt[rs[a]] = rt[a] = a, dis[a] = dis[rs[a]] + 1, a;
    }
    void merge(int a, int b) { if (a != b) rt[a] = rt[b] = _merge(a, b); }
} T;
signed main() {
    scanf("%d%d", &n, &m);
    T.init(n);
    for (int i = 1; i <= n; i++) scanf("%d", T.val + i);
    while (m--) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d", &x, &y);
            if (T.val[x] == -1 || T.val[y] == -1)continue;
            x = T.find(x), y = T.find(y);
            T.merge(x, y);
        } else {
            scanf("%d", &x);
            if (T.val[x] == -1) puts("-1");
            else printf("%d\n", T.val[x = T.find(x)]), T.pop(x);
        }
    }
    return 0;
}