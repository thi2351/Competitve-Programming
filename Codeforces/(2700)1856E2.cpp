/*
Problems: 1856E2. PermuTree (Hard)
Rating: 2700
Tags: DP, Tree, Math, Greedy
Key learning: Subset sum optimization, bitset template
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define pb push_back
const int INF    = 1e9;
const int MOD    = 998244353;
const int MOD2   = 1e9 + 7;
const ll  LL_INF = 4e18;

static const int MAXT = 1000000;

vector<ll> b;
ll closest_val;

template <int LEN = 1>
void subset_sum(int n) {
    if (n >= LEN) {
        constexpr int next = (LEN * 2 <= MAXT ? LEN * 2 : MAXT);
        subset_sum<next>(n);
        return;
    }
    bitset<LEN> dp;
    dp.reset();
    dp[0] = 1;
    for (ll x : b) 
        dp |= (dp << x);

    ll best_diff = n;
    closest_val = 0;
    for (int i = 0; i <= n/2 + 1; ++i) {
        if (dp[i]) {
            ll diff = llabs(i - (n - i));
            if (diff < best_diff) {
                best_diff = diff;
                closest_val = i;
            }
        }
    }
}

void solve() {
    int n; 
    cin >> n;
    vector<vector<int>> adj(n+1);
    FOR(i, 2, n) {
        int u; 
        cin >> u;
        adj[u].pb(i);
        adj[i].pb(u);
    }

    vector<int> sz(n+1, 1);
    vector<vector<int>> szChild(n+1);

    // compute subtree sizes and record each child‑size
    auto dfs1 = [&](auto&& self, int u, int p) -> void {
        sz[u] = 1;
        szChild[u].clear();
        for (int v : adj[u]) {
            if (v == p) continue;
            self(self, v, u);
            sz[u] += sz[v];
            szChild[u].pb(sz[v]);
        }
    };
    dfs1(dfs1, 1, -1);

    ll ret = 0;
    // for each node, build b[] and run the templated subset_sum
    auto dfs2 = [&](auto&& self, int u, int p) -> void {
        int T = sz[u] - 1;
        if (T > 0) {
            map<int,int> cnt;
            for (int x : szChild[u]) 
                cnt[x]++;
            sort(szChild[u].begin(), szChild[u].end());
            if (2*szChild[u].back() >= sz[u] - 1) {
                ret +=  1ll*szChild[u].back()*(sz[u]-1-szChild[u].back());
            }
            else {
            b.clear();
            while (!cnt.empty()) {
                auto it = cnt.begin();
                int w = it->first, c = it->second;
                cnt.erase(it);

                if (c & 1) {
                    b.pb(w);
                    --c;
                } else {
                    b.pb(w);
                    b.pb(w);
                    c -= 2;
                }
                if (c > 0) 
                    cnt[w*2] += (c >> 1);
            }

            subset_sum<1>(T);
            ll x = closest_val;
            ret += x * ll(T - x);
        }
        }
        for (int v : adj[u]) {
            if (v == p) continue;
            self(self, v, u);
        }
    };
    dfs2(dfs2, 1, -1);

    cout << ret << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int TC = 1;
    // cin >> TC;
    while (TC--) solve();
    return 0;
}