//Luogu P5491 【模板】二次剩余
//计算x^2 ≡ n (mod p)
//保证p是奇素数 若无解，则输出Hola!
#include<bits/stdc++.h>
using namespace std;
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rd(RANDOM);
uniform_int_distribution<int> dis(0, INT32_MAX);
int t, n, p;
int I;
struct cp {
    int r, i;
    cp(int r = 0, int i = 0) : r(r), i(i) {}
    bool operator==(const cp x) { return (x.i == i) && (x.r == r); }
    cp operator*(const cp x) {
        return cp((1LL * r * x.r % p + 1LL * I * i % p * x.i % p) % p,
                  (1LL * i * x.r % p + 1LL * r * x.i % p) % p);
    }
};
cp qpow(cp a, int b) {
    cp ret = (cp) {1, 0};
    while (b) {
        if (b & 1) ret = ret * a;
        a = a * a, b >>= 1;
    }
    return ret;
}
bool check(int x) { return qpow(x, (p - 1) >> 1) == 1; }
int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &p);
        if (!n) {
            puts("0");
            continue;
        }
        if (qpow(n, (p - 1) >> 1) == p - 1) {
            puts("Hola!");
            continue;
        }
        int a = dis(rd) % p;
        while (!a || check((1LL * a * a % p + p - n) % p)) a = dis(rd) % p;
        I = (1LL * a * a % p + p - n) % p;
        int x1 = qpow(cp(a, 1), (p + 1) >> 1).r;
        int x2 = (p - x1) % p;
        if (x1 > x2) swap(x1, x2);
        if (x1 == x2)printf("%d\n", x1);
        else printf("%d %d\n", x1, x2);
    }
    return 0;
}