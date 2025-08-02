/*
Problem: 2112E. Tree Coloring
Rating: 2200
Tags: Combinatoric, DP, tree, number theory
Key learning: DP
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (ll)4e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    vector<int> qs(T);
    int maxN = 1;
    for (int i = 0; i < T; ++i) {
        cin >> qs[i];
        maxN = max(maxN, qs[i]);
    }

    vector<ll> dp(maxN + 1, INF);
    dp[1] = 1;

    for (int i = 1; i <= maxN; ++i) {
        if (dp[i] == INF) continue;
        if (i > 2) dp[i] = min(dp[i], dp[i-2] + 1);
        for (int id = i * 3; id <= maxN; id += i) {
            int d = id / i;  // d >= 3
            dp[id] = min(dp[id], dp[i] + dp[d - 2]);
        }
    }

    for (int x : qs) {
        if (dp[x] == INF) 
            cout << "-1\n";
        else
            cout << dp[x] << "\n";
    }
    return 0;
}