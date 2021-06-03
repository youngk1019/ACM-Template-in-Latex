//Luogu P2580 于是他错误的点名开始了
//未匹配输出WRONG 第一匹配输出OK 后续匹配输出REPEAT
#include <bits/stdc++.h>
using namespace std;
#define maxn 500100
#define maxm 100
struct trie {
    int trie[maxn][26], cnt, flag[maxn];
    void insert(char *str) {
        int len = strlen(str), p = 0;
        for (int i = 0; i < len; i++) {
            int x = str[i] - 'a';
            if (!trie[p][x]) trie[p][x] = ++cnt;
            p = trie[p][x];
        }
        flag[p] = 1;
    }
    int query(char *str) {
        int len = strlen(str), p = 0;
        for (int i = 0; i < len; i++) {
            int x = str[i] - 'a';
            if (!trie[p][x]) return 0;
            p = trie[p][x];
        }
        return flag[p] == 1 ? flag[p] = 2, 1 : flag[p];
    }
} T;
int n, m;
char str[maxm];
const char ans[3][10] = {"WRONG", "OK", "REPEAT"};
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", str);
        T.insert(str);
    }
    scanf("%d", &m);
    while (m--) {
        scanf("%s", str);
        puts(ans[T.query(str)]);
    }
    return 0;
}