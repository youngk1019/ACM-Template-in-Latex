//Lougu P2801 教主的魔法
//格式：M L R W 含义：表示对闭区间 [L,R]内加上W
//格式：A L R C 含义：询问闭区间 [L,R] 内有大于等于C
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000010
#define maxm 1010
int n, q, x, y, c, block, tot, a[maxn], b[maxn], belong[maxn], l[maxm], r[maxm], lazy[maxm];
char op;
void change(int x, int y, int c) {
    if (belong[x] == belong[y]) {
        for (int i = x; i <= y; i++) a[i] += c;
        for (int i = l[belong[x]]; i <= r[belong[y]]; i++) b[i] = a[i];
        sort(b + l[belong[x]], b + r[belong[y]] + 1);
    } else {
        for (int i = x; i <= r[belong[x]]; i++) a[i] += c;
        for (int i = l[belong[x]]; i <= r[belong[x]]; i++) b[i] = a[i];
        sort(b + l[belong[x]], b + r[belong[x]] + 1);
        for (int i = l[belong[y]]; i <= y; i++) a[i] += c;
        for (int i = l[belong[y]]; i <= r[belong[y]]; i++) b[i] = a[i];
        sort(b + l[belong[y]], b + r[belong[y]] + 1);
        for (int i = belong[x] + 1; i <= belong[y] - 1; i++) lazy[i] += c;
    }
}
int query(int x, int y, int c) {
    int ans = 0;
    if (belong[x] == belong[y]) {
        c -= lazy[belong[x]];
        for (int i = x; i <= y; i++)if (a[i] >= c) ans++;
    } else {
        int k = c - lazy[belong[x]];
        for (int i = x; i <= r[belong[x]]; i++) if (a[i] >= k) ans++;
        k = c - lazy[belong[y]];
        for (int i = l[belong[y]]; i <= y; i++) if (a[i] >= k) ans++;
        for (int i = belong[x] + 1, p; i <= belong[y] - 1; i++) {
            k = c - lazy[i];
            p = lower_bound(b + l[i], b + r[i] + 1, k) - b;
            ans += r[i] - p + 1;
        }
    }
    return ans;
}
signed main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), b[i] = a[i];
    block = sqrt(n), tot = (n + block - 1) / block;
    for (int i = 1; i <= n; i++) belong[i] = (i - 1) / block + 1;
    for (int i = 1; i <= tot; i++) l[i] = (i - 1) * block + 1, r[i] = i * block;
    r[tot] = n;
    for (int i = 1; i <= tot; i++) sort(b + l[i], b + r[i] + 1);
    while (q--) {
        scanf(" %c%d%d%d", &op, &x, &y, &c);
        if (op == 'M') change(x, y, c);
        else printf("%d\n", query(x, y, c));
    }
    return 0;
}