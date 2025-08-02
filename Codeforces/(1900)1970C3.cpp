/*
Problem: 1970C3. Game on Tree (Hard)
Rating: 1900
Tags: DP, tree, game theory
Key learning: Nim game, Rerooting technique
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;

void solve() {
    int n, t; cin >> n >> t;
    vector<vector<int>> adj(n+1);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> position(n+1, 0);
    vector<bool> dp(n+1, false);
    auto dfs1 = [&](auto&& self, int u, int par) -> void {
        int pos = 0;
        for (int v : adj[u]) {
            if (v == par) continue;
            self(self,v,u);
        }
        for (int v : adj[u]) {
            if (v == par) continue;
            if (position[v] == 0) pos++;
        }
        position[u] = pos;
    };

    dfs1(dfs1, 1, 0);
    dp[1] = position[1];

    //Chuyển gốc trên cây
    auto dfs2 = [&](auto &&self, int u, int par) -> void {
        for (int v : adj[u]) {
            if (v == par) continue;
            int pu = position[u], pv = position[v];
            if (pv == 0) position[u]--;
            if (position[u] == 0) position[v]++;
            dp[v] = position[v];
            self(self, v, u);
            position[u] = pu;
            position[v] = pv;
        }
    };

    dfs2(dfs2, 1, 0);
    while (t--) {
        int u; cin >> u;
        // cout << u << " ";
        cout << (dp[u] ? "Ron" : "Hermione") << endl;
    }

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while (T--) solve();
    return 0;
}