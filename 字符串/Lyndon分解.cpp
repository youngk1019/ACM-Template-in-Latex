//Lougu P6114 【模板】Lyndon分解
//请把这个字符串分成若干部分 S=S1S2S3...Sm，是的每个Si都是Lyndon Word
//且Si >= Si+1
//一个字符串S是一个Lyndon Word，当且仅当S是其后缀中最小的字符串
//输出所有右端点下标的异或和
#include <bits/stdc++.h>
using namespace std;
#define maxn 5000100
char s[maxn];
int n, ans;
signed main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    int i = 1;
    while (i <= n) {
        int j = i, k = i + 1;
        while (k <= n && s[j] <= s[k]) j = s[j] == s[k++] ? j + 1 : i;
        while (i <= j) i += k - j, ans ^= i - 1;
    }
    printf("%d\n", ans);
    return 0;
}