//Luogu 【模板】回滚莫队&不删除莫队
//区间两个相同的数的最远距离
//块号从1开始，所有的块号+1
#include <bits/stdc++.h>
using namespace std;
#define maxn 200010
struct node {
    int l, r, id, pos;
} b[maxn];
int n, m, block, blocknum, a[maxn], last[maxn], st[maxn], ans, _ans[maxn];
vector<int> v;
bool cmp(node x, node y) {
    if (x.id == y.id) return x.r < y.r;
    else return x.l < y.l;
}
void radd(int x) {
    last[a[x]] = x;
    if (!st[a[x]]) st[a[x]] = x;
    ans = max(ans, x - st[a[x]]);
}
void ladd(int x) {
    if (last[a[x]]) ans = max(ans, last[a[x]] - x);
    else last[a[x]] = x;
}
void ldel(int x) {
    if (last[a[x]] == x) last[a[x]] = 0;
}
int calc(int l, int r) {
    static int st[maxn];
    int ret = 0;
    for (int i = l; i <= r; i++)st[a[i]] = 0;
    for (int i = l; i <= r; i++) {
        if (!st[a[i]]) st[a[i]] = i;
        else ret = max(ret, i - st[a[i]]);
    }
    return ret;
}
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), v.push_back(a[i]);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for (int i = 1; i <= n; i++) a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin();
    scanf("%d", &m);
    block = sqrt(n);
    blocknum = n / block + 1;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &b[i].l, &b[i].r);
        b[i].id = b[i].l / block + 1, b[i].pos = i;
    }
    sort(b + 1, b + m + 1, cmp);
    for (int i = 1, j = 1; j <= blocknum; j++) {
        int br = min(n, j * block), l = br + 1, r = l - 1;
        ans = 0;
        while (b[i].id == j) {
            int ll = b[i].l, rr = b[i].r;
            if (rr / block + 1 == j) {
                _ans[b[i].pos] = calc(ll, rr), i++;
                continue;
            }
            while (r < rr) radd(++r);
            int tp = ans;
            while (l > ll) ladd(--l);
            _ans[b[i].pos] = ans;
            while (l <= br) ldel(l++);
            ans = tp, i++;
        }
        memset(last, 0, sizeof(last));
        memset(st, 0, sizeof(st));
    }
    for (int i = 1; i <= m; i++) printf("%d\n", _ans[i]);
    return 0;
}