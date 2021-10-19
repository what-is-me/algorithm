long long qpow(long long a, int n, long long mod = 1e9 + 7, long long c = 1) {
    for (; n; n >>= 1, a = a * a % mod)
        if (n & 1) c = c * a % mod;
    return c;
}
int qpow(int a, int n, int mod = 1e9 + 7, int c = 1) {
    for (; n; n >>= 1, a = a * a % mod)
        if (n & 1) c = c * a % mod;
    return c;
}