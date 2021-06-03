//Lougu P3375 【模板】KMP字符串匹配
#include <bits/stdc++.h>
using namespace std;
#define maxn 10000100
char s1[maxn], s2[maxn];
int nxt[maxn], lens1, lens2;
void getnext(char *s) {
    int k = 0;
    for (int i = 2; i <= lens2; i++) {
        while (k && s[i] != s[k + 1]) k = nxt[k];
        if (s[k + 1] == s[i]) k++;
        nxt[i] = k;
    }
}
void kmp(int l, int r) {
    int k = 0;
    for (int i = l; i <= r; i++) {
        while (k && s2[k + 1] != s1[i]) k = nxt[k];
        if (s2[k + 1] == s1[i]) k++;
        if (k == lens2) {
            printf("%d\n", i - lens2 + 1);
            k = nxt[k];
        }
    }
}
signed main() {
    scanf("%s%s", s1 + 1, s2 + 1);
    lens1 = strlen(s1 + 1), lens2 = strlen(s2 + 1);
    getnext(s2);
    kmp(1, lens1);
    for (int i = 1; i <= lens2; i++) printf("%d ", nxt[i]);
    return 0;
}