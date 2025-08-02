/*
Problem: 2075D. Equalization
Rating: 2000
Tag: DP, math, bitmasks, brute force
Key learning: DP on subset sum
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 100001;
int dp[61][61];
void preprocess() {
    for (int i = 0; i <= 60; i++) {
        for (int j = 0; j <= 60; j++) {
            dp[i][j] = (int)1e9;
        }
    }
    dp[0][0] = 0;
    for (int x = 0; x < 61; ++x) {
        for (int i = 60; i >= 0; --i) {
          for (int j = 60; j >= 0; --j) {
            if (dp[i][j] == (int)1e9) continue;
            if (i + x < 61) dp[i + x][j] = min(dp[i + x][j], dp[i][j] + (1LL << x));
            if (j + x < 61) dp[i][j + x] = min(dp[i][j + x], dp[i][j] + (1LL << x));
          }
        }
    }
}
void solve() {
    int x, y;
    cin >> x >> y;
    int ret = 1e9;
    for (int i = 0; i <= 60; i++) {
        for (int j = 0; j <= 60; j++) {
            if ((x >> i) == (y >> j)) {
                ret = min(ret, dp[i][j]);
            }
        }
    }
    cout << ret << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc = 1;
    cin >> tc;
    preprocess();
    while (tc--) solve();
    return 0;
}