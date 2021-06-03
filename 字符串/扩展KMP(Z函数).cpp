//Lougu P5410 【模板】扩展KMP（Z函数）
//b的z函数数组z，即b与b的每一个后缀的LCP长度。
//b与a的每一个后缀的LCP长度数组p
//LCP: 最长公共前缀
#include <bits/stdc++.h>
using namespace std;
#define maxn 20000100
char a[maxn], b[maxn];
int z[maxn], p[maxn], n, m;
void Z(char *s, int n) {
    z[1] = n;
    for (int i = 2, l = 0, r = 0; i <= n; i++) {
        if (i <= r) z[i] = min(z[i - l + 1], r - i + 1);
        while (i + z[i] <= n && s[i + z[i]] == s[z[i] + 1]) z[i]++;
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
}
void exkmp(char *s, int n, char *t, int m) {
    Z(t, m);
    for (int i = 1, l = 0, r = 0; i <= n; i++) {
        if (i <= r) p[i] = min(z[i - l + 1], r - i + 1);
        while (i + p[i] <= n && s[i + p[i]] == t[p[i] + 1]) p[i]++;
        if (i + p[i] - 1 > r) l = i, r = i + p[i] - 1;
    }
}
signed main() {
    scanf("%s%s", a + 1, b + 1);
    n = strlen(a + 1), m = strlen(b + 1);
    exkmp(a, n, b, m);
    long long ans = 0;
    for (int i = 1; i <= m; i++) ans ^= 1LL * i * (z[i] + 1);
    printf("%lld\n", ans);
    ans = 0;
    for (int i = 1; i <= n; i++) ans ^= 1LL * i * (p[i] + 1);
    printf("%lld\n", ans);
    return 0;
}