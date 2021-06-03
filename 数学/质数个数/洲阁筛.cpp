//hdu 5901 Count primes
//洲阁筛 单次复杂度O(n^(2/3)/logn)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define maxn 1000010
int prime[maxn], cnt, sum[maxn];
bool flag[maxn];
void sieve() {//把小于等于sqrt（n）的质数筛出来
    for (int i = 2; i < maxn; i++) {
        sum[i] = sum[i - 1];
        if (!flag[i]) prime[++cnt] = i, sum[i]++;
        for (int j = 1; j <= cnt && i * prime[j] < maxn; j++) {
            flag[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
        }
    }
}
int last[maxn << 1];
ll g[maxn << 1], value[maxn << 1], n;
ll cal(ll n) {
    int tot = 0, sn = sqrt(n);//考虑<=n的数由<=sqrtn的质数筛出的情况
    int p = upper_bound(prime + 1, prime + cnt + 1, sn) - prime - 1;//pos第一个小于等于sn的质数位置
    for (ll i = n; i >= 1; i = n / (n / i + 1)) value[++tot] = n / i;//记录所有[n/i]的值，只有这样的数才会出现在转移中 //离散
    for (int i = 1; i <= tot; i++) g[i] = value[i], last[i] = 0;
    for (int i = 1; i <= p; i++) {
        for (int j = tot; j >= 0; j--) {
            ll k = value[j] / prime[i];
            if (k < prime[i]) break;//忽略那些-1的转移
            k = k < sn ? k : tot - n / k + 1;//找到在value中的对应下标
            g[j] -= g[k] - (i - last[k] - 1);//将g[k]的-1的转移补回去
            last[j] = i;
        }
    }
    return sum[sn] + g[tot] - 1;//-1是减去1的贡献
}
int main() {
    sieve();
    while (~scanf("%lld", &n)) printf("%lld\n", cal(n));
    return 0;
}