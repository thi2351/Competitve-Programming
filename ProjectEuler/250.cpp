#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using vi = vector<int>;
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define pb push_back
const int INF    = 1e9;
// const int MOD    = 998244353;
// const int MOD2   = 1e9 + 7;
const ll  LL_INF = 4e18;
const int MAXN = 1e5 + 5;
const int MAXK = 18;


void solve() {
    auto binPow = [&](int x) {
        int64_t ret = 1, b = x;
        int e = x;               
        while (e > 0) {
            if (e & 1) ret = (ret * b) % 250;
            b = (b * b) % 250;
            e >>= 1;
        }
        return int(ret);
    };
    vector<int> item;
    for (int i = 1; i <= 250250; i++) item.pb(binPow(i)); 
    static constexpr uint64_t MOD1 = 10000000000000000ULL;
    static constexpr ll      MOD2 = 1000000007;
    vector<uint64_t> dp1(250, 0), next1(250);
    vector<ll>      dp2(250, 0), next2(250);
    dp1[0] = 1;
    dp2[0] = 1;

    for (int x : item) {
        int w = (x % 250 + 250) % 250;
        next1 = dp1;
        next2 = dp2;
        for (int r = 0; r < 250; r++) {
            if (dp1[r] || dp2[r]) {
                int nr = r + w;
                if (nr >= 250) nr -= 250;
                next1[nr] = (next1[nr] + dp1[r]) % MOD1;
                next2[nr] = (next2[nr] + dp2[r]) % MOD2;
            }
        }
        dp1.swap(next1);
        dp2.swap(next2);
    }
    // for (int i = 1; i <= 100; i++) cout << dp1[i] << " ";
    // cout << endl;
    uint64_t ans = (dp1[0] + MOD1 - 1) % MOD1;
    cout << setw(16) << setfill('0') << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int TC = 1;
    cin >> TC;
    while (TC--) solve();
    return 0;
}
