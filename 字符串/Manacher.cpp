//Lougu P3805 【模板】manacher算法
//字符串S最长回文串的长度
#include <bits/stdc++.h>
using namespace std;
#define maxn 22000100 //两倍空间
int ans, n, p[maxn];
char str[maxn], s[maxn];
signed main() {
    scanf("%s", str + 1);
    n = strlen(str + 1);
    for (int i = 1; i <= n; i++) s[i << 1] = str[i], s[(i << 1) | 1] = '#';
    n = (n << 1) | 1, s[0] = '@', s[1] = '#';
    for (int i = 1, r = 0, mid = 0; i <= n; i++) {
        if (i <= r) p[i] = min(p[(mid << 1) - i], r - i + 1);
        while (s[i - p[i]] == s[i + p[i]]) p[i]++;
        if (p[i] + i > r) r = p[i] + i - 1, mid = i;
        ans = max(ans, p[i]);
    }
    printf("%d\n", ans - 1);
    return 0;
}