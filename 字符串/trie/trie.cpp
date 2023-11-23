//Luogu P2580 于是他错误的点名开始了
//未匹配输出WRONG 第一匹配输出OK 后续匹配输出REPEAT
#include <bits/stdc++.h>
using namespace std;
struct trie {
    vector<array<int, 26> > t;
    vector<int> flag;
    trie() { expand(); }
    void insert(string &str) {
        int p = 0;
        for (char &c: str) {
            int x = c - 'a';
            if (!t[p][x]) t[p][x] = t.size(), expand();;
            p = t[p][x];
        }
        flag[p] = 1;
    }
    int query(string &str) {
        int p = 0;
        for (char &c: str) {
            int x = c - 'a';
            if (!t[p][x]) return 0;
            p = t[p][x];
        }
        return flag[p] == 1 ? flag[p] = 2, 1 : flag[p];
    }
private:
    void expand() { t.emplace_back(), flag.emplace_back(); }
} T;
int n, m;
string str;
const string ans[] = {"WRONG", "OK", "REPEAT"};
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> str, T.insert(str);
    cin >> m;
    while (m--) cin >> str, cout << ans[T.query(str)] << '\n';
    return 0;
}