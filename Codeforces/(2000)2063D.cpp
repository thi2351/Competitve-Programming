/*
Problem: 2063D. Game with Triangles
Rating: 2000
Tag: Ternary search, math, two pointers, geometry, greedy
Key learning: Ternary search
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
const int MAXN = 1e5 + 5;
const int MAXK = 18;


void solve() {
    int n, m; cin >> n >> m;
    vector<ll> a(n);
    vector<ll> b(m);
    for (auto &x : a) cin >> x;
    for (auto &x : b) cin >> x;
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    int k_max = min((m+n)/3,min(m,n));
    //cause b has m point, a can have at most min(k_max, m) operation, same thinking on a
    int mx_a = min(k_max, min(m, n/2));
    int mx_b = min(k_max, min(n, m/2));
    vector<ll> tot_a(mx_a + 1, 0);
    vector<ll> tot_b(mx_b + 1, 0);
    for (int i = 1; i <= mx_a; i++) {
        tot_a[i] = tot_a[i-1] + (-a[i-1] + a[n-i]);
    }
    for (int i = 1; i <= mx_b; i++) {
        tot_b[i] = tot_b[i-1] + (-b[i-1] + b[m-i]);
    }

    auto perform = [&](int k) -> ll {
        //perform a ternary search to search suitable k
        //Let k be total operation, a will perform x operation, b will perform (k - x) operation
        //Therefore: 2*x + (k - x) <= n -> x <= n - k
        //           x + 2*(k - x) <= m -> x >= 2k - m
        //Moreover, b perform at most mx_b operation, a will perform at least k - mx_b operation
        int lo = max({0, 2*k - m, k - mx_b});
        int hi = min({k, n - k, mx_a});

        auto f = [&](int i) -> ll {
            return tot_a[i] + tot_b[k - i];
        };

        ll res = -LL_INF;
        while (hi - lo > 3) {
            int m1 = lo + (hi - lo)/3;
            int m2 = hi - (hi - lo)/3;
            if (f(m1) < f(m2)) {
                lo = m1;
            }
            else {
                hi = m2;
            }
        }
        for (int i = lo; i <= hi; i++) {
            res = max(res, f(i));
        }
        return res;
    };
    
    cout << k_max << endl;
    for (int i = 1; i <= k_max; i++) {
        cout << perform(i) << " ";
    }
    cout << endl;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int TC = 1;
    cin >> TC;
    while (TC--) solve();
    return 0;
}