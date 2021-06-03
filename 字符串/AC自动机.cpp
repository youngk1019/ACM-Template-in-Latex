//Luogu P3808 【模板】AC自动机（简单版）
//给定 n个模式和一个文本串，求有多少个不同的模式串在文本串里出现过
#include <bits/stdc++.h>
using namespace std;
#define maxn 1000100
struct AC_automation {
    int trie[maxn][26], val[maxn], fail[maxn], cnt;
    void insert(char *s) {
        int len = strlen(s), p = 0;
        for (int i = 0; i < len; i++) {
            int x = s[i] - 'a';
            if (!trie[p][x]) trie[p][x] = ++cnt;
            p = trie[p][x];
        }
        val[p]++;
    }
    void build() {
        queue<int> q;
        for (int i = 0; i < 26; i++) {
            if (trie[0][i]) fail[trie[0][i]] = 0, q.push(trie[0][i]);
        }
        while (q.size()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < 26; i++) {
                if (trie[u][i]) fail[trie[u][i]] = trie[fail[u]][i], q.push(trie[u][i]);
                else trie[u][i] = trie[fail[u]][i];
            }
        }
    }
    int query(char *s) {
        int len = strlen(s), p = 0, ret = 0;
        for (int i = 0; i < len; i++) {
            p = trie[p][s[i] - 'a'];
            for (int t = p; t && ~val[t]; t = fail[t])ret += val[t], val[t] = -1;
        }
        return ret;
    }
} T;
int n;
char s[maxn];
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", s);
        T.insert(s);
    }
    T.build();
    scanf("%s", s);
    printf("%d\n", T.query(s));
    return 0;
}