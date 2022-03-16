//Luogu P3809 【模板】后缀排序
//SA 为这个字符串的所有非空后缀按字典序从小到大排序，然后按顺序输出后缀的第一个字符在原串中的位置
//height 为LCP(sa[i],sa[i-1])
#include <bits/stdc++.h>
using namespace std;
#define maxn 1000100
int n, m, x[maxn], y[maxn], cnt[maxn], sa[maxn], rk[maxn], height[maxn];
char s[maxn];
void get_SA() {
    n = strlen(s + 1), m = 'z';
    for (int i = 1; i <= n; i++) cnt[x[i] = s[i]]++;
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; i--) sa[cnt[x[i]]--] = i;
    for (int k = 1; k <= n; k <<= 1) {
        int num = 0;
        for (int i = n - k + 1; i <= n; i++) y[++num] = i;
        for (int i = 1; i <= n; i++) if (sa[i] > k) y[++num] = sa[i] - k;
        for (int i = 1; i <= m; i++) cnt[i] = 0;
        for (int i = 1; i <= n; i++) cnt[x[i]]++;
        for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; i--) sa[cnt[x[y[i]]]--] = y[i], y[i] = 0;
        swap(x, y);
        x[sa[1]] = 1, num = 1;
        for (int i = 2; i <= n; i++) {
            x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++num;
        }
        if (num == n) break;
        m = num;
    }
}
void get_height() {
    int k = 0;
    for (int i = 1; i <= n; i++) rk[sa[i]] = i;
    for (int i = 1; i <= n; i++) {
        if (rk[i] == 1) continue;
        k = max(0, k - 1);
        int j = sa[rk[i] - 1];
        while (j + k <= n && i + k <= n && s[i + k] == s[j + k]) k++;
        height[rk[i]] = k;
    }
}
signed main() {
    scanf("%s", s + 1);
    get_SA();
    for (int i = 1; i <= n; i++) printf("%d ", sa[i]);
    return 0;
}