//Luogu P3808 【模板】AC自动机（简单版）
//给定 n个模式和一个文本串，求有多少个不同的模式串在文本串里出现过
#include <bits/stdc++.h>
using namespace std;
struct AC_automation {
    vector<array<int, 26>> trie;
    vector<int> val, fail;
    AC_automation() { expand(); }
    void insert(string &str) {
        int p = 0;
        for (char &c: str) {
            int x = c - 'a';
            if (!trie[p][x]) trie[p][x] = trie.size(), expand();
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
    int query(string &str) {
        int p = 0, ret = 0;
        for (char &c: str) {
            p = trie[p][c - 'a'];
            for (int t = p; t && ~val[t]; t = fail[t])ret += val[t], val[t] = -1;
        }
        return ret;
    }
private:
    void expand() {
        trie.emplace_back(), val.emplace_back(), fail.emplace_back();
    }
} T;
int n;
string str;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> str, T.insert(str);
    T.build();
    cin >> str;
    cout << T.query(str) << '\n';
    return 0;
}