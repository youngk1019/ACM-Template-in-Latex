//Lougu P1368 【模板】最小表示法
//找出字符串S的循环同构串中字典序最小的一个
//也可以通过P = S + S通过Lyndon分解求出在S的Lyndon Word
#include <bits/stdc++.h>
using namespace std;
#define maxn 600100 //两倍空间
int n, a[maxn];
signed main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", a + i), a[i + n] = a[i];
    int i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        int t = a[(i + k) % n] - a[(j + k) % n];
        if (t == 0) k++;
        else {
            if (t > 0) i += k + 1;
            else j += k + 1;
            if (i == j) j++;
            k = 0;
        }
    }
    for (int o = min(i, j); o < min(i, j) + n; o++) printf("%d ", a[o]);
    return 0;
}