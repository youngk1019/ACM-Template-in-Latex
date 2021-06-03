//Luogu P1177 【模板】快速排序
//压2^16 只支持2^32 如果要支持负数每个数先加上2^31
#include <bits/stdc++.h>
using namespace std;
#define maxn 100010
int n, a[maxn], temp[maxn], cnt[1 << 16];
void radixsort(unsigned *a, int n) {//a[0,n)
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++) cnt[a[i] & 65535]++;
    for (int i = 1; i <= 65535; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) temp[--cnt[a[i] & 65535]] = a[i];
    for (int i = 0; i < n; i++) a[i] = temp[i];
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++) cnt[a[i] >> 16]++;
    for (int i = 1; i <= 65535; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) temp[--cnt[a[i] >> 16]] = a[i];
    for (int i = 0; i < n; i++) a[i] = temp[i];
}
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), a[i];
    radixsort((unsigned *) a + 1, n);
    for (int i = 1; i <= n; i++) printf("%d ", a[i]);
    return 0;
}