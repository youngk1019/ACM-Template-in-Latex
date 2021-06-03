//P7112 【模板】行列式求值
#include <bits/stdc++.h>
using namespace std;
#define maxn 610
int n, p, a[maxn][maxn], ans = 1;
signed main() {
    scanf("%d%d", &n, &p);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)scanf("%d", &a[i][j]), a[i][j] %= p;
    }
    bool tr = false;
    for (int i = 1; i <= n; i++) {
        int k = i;
        for (int j = i + 1; j <= n; j++) if (a[j][i] > a[k][i]) k = j;
        if (i != k) {
            for (int j = i; j <= n; j++) swap(a[i][j], a[k][j]);
            tr ^= true;
        }
        if (a[i][i] == 0) {
            ans = 0;
            break;
        }
        for (int j = i + 1; j <= n; j++) {
            if (a[j][i] > a[i][i]) {
                for (int k = i; k <= n; k++) swap(a[j][k], a[i][k]);
                tr ^= true;
            }
            while (a[j][i]) {
                int x = p - a[i][i] / a[j][i];
                for (int k = i; k <= n; k++) a[i][k] = (a[i][k] + 1LL * x * a[j][k]) % p;
                for (int k = i; k <= n; k++) swap(a[j][k], a[i][k]);
                tr ^= true;
            }
        }
        ans = 1LL * ans * a[i][i] % p;
    }
    printf("%d", tr ? (p - ans) % p : ans);
    return 0;
}