//Luogu P3804 【模板】后缀自动机 (SAM)
//SAM 最多有 2n - 1个节点和3n - 4调转移边
#include <bits/stdc++.h>
using namespace std;
#define maxn 1000100
struct suffix_automaton {
    int last, cnt;
    int ch[maxn << 1][26], fa[maxn << 1], len[maxn << 1], sz[maxn << 1];
    void insert(int c) {
        int p = last, np = ++cnt;
        last = np, len[np] = len[p] + 1;
        while (p && !ch[p][c])ch[p][c] = np, p = fa[p];
        if (!p)fa[np] = 1;
        else {
            int q = ch[p][c];
            if (len[p] + 1 == len[q]) fa[np] = q;
            else {
                int nq = ++cnt;
                len[nq] = len[p] + 1;
                memcpy(ch[nq], ch[q], sizeof(ch[q]));
                fa[nq] = fa[q], fa[q] = fa[np] = nq;
                for (; ch[p][c] == q; p = fa[p])ch[p][c] = nq;
            }
        }
        sz[np] = 1;
    }
    void build(char *str) {
        int len = strlen(str);
        last = cnt = 1;
        for (int i = 0; i < len; i++)insert(str[i] - 'a');
    }
    long long calc() {
        long long ans = 0;
        static int id[maxn << 1];
        for (int i = 1; i <= cnt; i++) id[i] = i;
        sort(id + 1, id + cnt + 1, [&](int &x, int &y) { return len[x] < len[y]; });
        for (int i = cnt; i >= 1; i--) {
            int p = id[i];
            sz[fa[p]] += sz[p];
            if (sz[p] > 1) ans = max(ans, 1LL * sz[p] * len[p]);
        }
        return ans;
    }
} T;
char s[maxn];
signed main() {
    scanf("%s", s);
    T.build(s);
    printf("%lld", T.calc());
	return 0;
}