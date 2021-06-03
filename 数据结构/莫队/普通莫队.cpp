//Luogu P3709 大爷的字符串题
//区间众数(输出负值)
//取block = n/sqrt(m)使复杂度最优为O(n*sqrt(m)) 也可以选择n/sqrt(2/3*m) 但注意卡block != 0
#include <bits/stdc++.h>
using namespace std;
#define maxn 200010
struct node {
    int l, r, id, pos;
} b[maxn];
int n, m, block, a[maxn], cnt[maxn], num[maxn], sum[maxn], ans;
vector<int> v;
bool cmp(node x, node y) {
    if (x.id == y.id) {
        if (x.id & 1) return x.r < y.r;
        else return x.r > y.r;
    } else return x.l < y.l;
}
void add(int x) {
    cnt[x = a[x]]++;
    ans = max(ans, cnt[x]);
    num[cnt[x]]++;
}
void del(int x) {
    num[cnt[x = a[x]]]--;
    if (num[cnt[x]] == 0 && ans == cnt[x]) ans--;
    cnt[x]--;
}
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), v.push_back(a[i]);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for (int i = 1; i <= n; i++) a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin();
    block = sqrt(n);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &b[i].l, &b[i].r);
        b[i].id = b[i].l / block, b[i].pos = i;
    }
    sort(b + 1, b + m + 1, cmp);
    for (int i = 1, ll, rr, l = 1, r = 0; i <= m; i++) {
        ll = b[i].l, rr = b[i].r;
        while (l < ll) del(l++);
        while (l > ll) add(--l);
        while (r < rr) add(++r);
        while (r > rr) del(r--);
        sum[b[i].pos] = ans;
    }
    for (int i = 1; i <= m; i++) printf("%d\n", -sum[i]);
    return 0;
}