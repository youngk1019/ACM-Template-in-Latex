//Luogu P1903 [国家集训队]数颜色/维护队列
//带修莫队 区间不同种类的数字的个数
//取block = n^(2/3) 使复杂度最优为O(n^(5/3))
#include <bits/stdc++.h>
using namespace std;
#define maxn 140010
#define maxm 1000010//数值范围
struct query {
    int l, r, pos, time;//pos是查询下标
} b[maxn];
struct change {
    int pos, val;//pos是位置下标
} c[maxn];
int n, m, block, a[maxn], cnt[maxm], sum[maxn], ans, tot, tim;
char op;
bool cmp(query x, query y) {
    if (x.l / block != y.l / block) return x.l / block < y.l / block;
    if (x.r / block != y.r / block) {
        if ((x.l / block) & 1) return x.r / block < y.r / block;
        else return x.r / block > y.r / block;
    }
    return x.time < y.time;
}
void add(int x) {
    if (cnt[a[x]] == 0) ans++;
    cnt[a[x]]++;
}
void del(int x) {
    cnt[a[x]]--;
    if (cnt[a[x]] == 0) ans--;
}
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    while (m--) {
        scanf(" %c", &op);
        if (op == 'R') {
            tim++;
            scanf("%d%d", &c[tim].pos, &c[tim].val);
        } else {
            tot++;
            scanf("%d%d", &b[tot].l, &b[tot].r);
            b[tot].pos = tot, b[tot].time = tim;
        }
    }
    block = pow(n, 2.0 / 3.0);
    sort(b + 1, b + tot + 1, cmp);
    for (int i = 1, ll, rr, tt, p, l = 1, r = 0, t = 0; i <= tot; i++) {
        ll = b[i].l, rr = b[i].r, tt = b[i].time;
        while (l < ll) del(l++);
        while (l > ll) add(--l);
        while (r < rr) add(++r);
        while (r > rr) del(r--);
        while (tt < t) {
            p = c[t].pos;
            if (l <= p && p <= r) del(p);
            swap(a[p], c[t].val);
            if (l <= p && p <= r) add(p);
            t--;
        }
        while (tt > t) {
            p = c[++t].pos;
            if (l <= p && p <= r) del(p);
            swap(a[p], c[t].val);
            if (l <= p && p <= r) add(p);
        }
        sum[b[i].pos] = ans;
    }
    for (int i = 1; i <= tot; i++) printf("%d\n", sum[i]);
    return 0;
}