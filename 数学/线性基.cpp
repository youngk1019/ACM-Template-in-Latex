//Luogu P3812 【模板】线性基
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define maxm 50
struct linear_basis {
    ll a[maxm], temp[maxm];
    bool flag;//是否可以表示0
    void insert(ll x) {
        for (int i = maxm - 1; i >= 0; i--) {
            if (x & (1LL << i)) {
                if (!a[i]) return a[i] = x, void();
                else x ^= a[i];
            }
        }
        flag = true;
    }
    ll qmax(ll ret = 0) {
        for (int i = maxm - 1; i >= 0; i--)ret = max(ret, ret ^ a[i]);
        return ret;
    }
    ll qmin() {
        if (flag)return 0;
        for (int i = 0; i <= maxm - 1; i++) if (a[i]) return a[i];
    }
    ll query(ll k) {
        ll ret = 0;
        int cnt = 0;
        k -= flag;
        if (!k)return 0;
        for (int i = 0; i <= 50; i++) {
            for (int j = i - 1; j >= 0; j--) if (a[i] & (1ll << j))a[i] ^= a[j];
            if (a[i]) temp[cnt++] = a[i];
        }
        if (k >= (1LL << cnt)) return -1;
        for (int i = 0; i < cnt; i++) if (k & (1LL << i)) ret ^= temp[i];
        return ret;
    }
    //查询是否存在
    bool count(ll x) {
        for (int i = maxm - 1; i >= 0; i--) {
            if (x & (1 << i))x ^= a[i];
        }
        return x == 0;
    }
} T;
int n;
ll x;
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)scanf("%lld", &x), T.insert(x);
    printf("%lld", T.qmax());
    return 0;
}