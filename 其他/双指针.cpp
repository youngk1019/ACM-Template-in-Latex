//CF 1435C Perform Easily
//对于n个数b[1..n] b[i]减去a[1..6]中的一个 使得max{b[i]}-min{b[i]}最小
#include <bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
#define maxn 100100
int n, a[10], b[maxn], cnt[maxn], sum, ans = inf, N;
vector<pair<int, int> > v;
void add(int x) {
    cnt[x]++;
    if (cnt[x] == 1) sum++;
}
void del(int x) {
    cnt[x]--;
    if (cnt[x] == 0) sum--;
}
signed main() {
    for (int i = 1; i <= 6; i++) scanf("%d", a + i);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", b + i);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 6; j++) {
            v.push_back(make_pair(b[i] - a[j], i));
        }
    }
    sort(v.begin(), v.end());
    N = v.size();
    for (int l = 0, r = 0; l < N; l++) {
        while (sum < n && r < N) {
            add(v[r++].second);
        }
        if (sum == n) ans = min(ans, v[r - 1].first - v[l].first);
        del(v[l].second);
    }
    printf("%d\n", ans);
    return 0;
}