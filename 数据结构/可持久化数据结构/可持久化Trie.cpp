//Lougu P4735 最大异或和
//操作1：格式：A x 含义：添加操作，表示在序列末尾添加一个数 x，序列的长度 n+1
//操作2：格式：Q l r x 含义：询问操作，你需要找到一个位置 p,满足l<=p<=r 使得a[p]^a[p+1]^..^a[n]^x最大，输出最大是多少
#include <bits/stdc++.h>
using namespace std;
#define maxn 600100 //n+m
int n, m, x, now, l, r;
char op;
struct persistable_trie {
    int trie[maxn << 6][2], rt[maxn], sum[maxn << 6], cnt;
    void insert(int &cur, int pre, int x) {
        cur = ++cnt;
        int p = cur;
        for (int i = 24; i >= 0; i--) {
            int ch = (x >> i) & 1;
            sum[p] = sum[pre] + 1, trie[p][ch] = ++cnt;
			trie[p][ch ^ 1] = trie[pre][ch ^ 1];
            pre = trie[pre][ch], p = trie[p][ch];
        }
        sum[p] = sum[pre] + 1;
    }
    int query(int pre, int cur, int x) {
        int ret = 0;
        for (int i = 24; i >= 0; i--) {
            int ch = (x >> i) & 1;
            if (sum[trie[cur][ch ^ 1]] - sum[trie[pre][ch ^ 1]] > 0) {
                cur = trie[cur][ch ^ 1], pre = trie[pre][ch ^ 1], ret += (1 << i);
            } else cur = trie[cur][ch], pre = trie[pre][ch];
        }
        return ret;
    }
} T;
signed main() {
    scanf("%d%d", &n, &m);
    T.insert(T.rt[1], T.rt[0], 0);
    n++;
    for (int i = 2; i <= n; i++) {
        scanf("%d", &x);
        now ^= x, T.insert(T.rt[i], T.rt[i - 1], now);
    }
    while (m--) {
        scanf(" %c", &op);
        if (op == 'A') {
            scanf("%d", &x);
            n++, now ^= x, T.insert(T.rt[n], T.rt[n - 1], now);
        } else {
            scanf("%d%d%d", &l, &r, &x);
            x ^= now, printf("%d\n", T.query(T.rt[l - 1], T.rt[r], x));
        }
    }
    return 0;
}