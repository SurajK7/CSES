/*
    Author: GouenjiShuuya
    Credits:    https://codeforces.com/blog/entry/96344
                https://github.com/bqi343/USACO
                https://github.com/nealwu/competitive-programming
                https://github.com/maksim1744/programming-library
*/

#ifndef LOCAL
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,sse4.2,bmi,bmi2,popcnt,lzcnt")
#endif

#include "bits/extc++.h"

using namespace std;
using namespace __gnu_pbds;
using ll = int64_t;

#define all(x) begin(x), end(x)
#define sz(x) ll((x).size())

// const ll MOD = 1e9 + 7;
const ll MOD = 998244353;
const ll INF = 4e18;
const ll dr[4] = {1, 0, -1, 0}, dc[4] = {0, 1, 0, -1};

mt19937_64 rngl((uint64_t)chrono::steady_clock::now().time_since_epoch().count());

constexpr ll p2(ll x) { return 1LL << x; }
constexpr ll msk2(ll x) { return p2(x) - 1; }
constexpr ll pct(ll x) { return __builtin_popcountll(x); } // # of bits set
constexpr ll largest_bit(ll x) { return x == 0 ? -1LL : 63LL - __builtin_clzll(x); }

ll cdiv(ll a, ll b) { return a / b + ((a ^ b) > 0 && a % b); }

ll fdiv(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }

template <class T>
bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }

template <class T>
bool ckmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

template <class T>
void remDup(vector<T> &v)
{
    sort(all(v));
    v.erase(unique(all(v)), end(v));
}

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <class key, class value, class cmp = std::less<key>>
using ordered_map = tree<key, value, cmp, rb_tree_tag, tree_order_statistics_node_update>;

void solve()
{
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> adj(n);
    for (ll i = 0; i < n - 1; i++)
    {
        ll u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    ll max_jump = largest_bit(n) + 1;
    vector<vector<ll>> ancestors(max_jump, vector<ll>(n, -1));
    vector<ll> levels(n);
    auto dfs = [&](auto &self, ll v, ll p, ll l) -> void
    {
        for (auto i : adj[v])
        {
            if (i == p)
                continue;
            ancestors[0][i] = v;
            levels[i] = l;
            self(self, i, v, l + 1);
        }
    };
    dfs(dfs, 0, -1, 1);
    for (ll i = 1; i < max_jump; i++)
    {
        for (ll j = 0; j < n; j++)
        {
            if (ancestors[i - 1][j] != -1)
                ancestors[i][j] = ancestors[i - 1][ancestors[i - 1][j]];
        }
    }
    auto kth_ancestor = [&](ll v, ll k) -> ll
    {
        ll i = 0;
        while (k > 0 && v >= 0)
        {
            if (k & 1)
            {
                v = ancestors[i][v];
            }
            i++;
            k >>= 1;
        }
        return v;
    };
    auto lca = [&](ll u, ll v) -> ll
    {
        if (levels[u] > levels[v])
            swap(u, v);
        ll d = levels[v] - levels[u];
        if (d > 0)
            v = kth_ancestor(v, d);
        if (u == v)
        {
            return u;
        }
        for (ll i = max_jump - 1; i >= 0; i--)
        {
            if (ancestors[i][u] != ancestors[i][v])
            {
                u = ancestors[i][u], v = ancestors[i][v];
            }
        }
        return ancestors[0][u];
    };
    vector<ll> ep(n), ad(n);
    while (m--)
    {
        ll u, v;
        cin >> u >> v;
        --u, --v;
        ll l = lca(u, v);
        ad[l]++;
        ep[u]++;
        ep[v]++;
        ep[l] -= 2;
    }
    vector<ll> ans(n);
    auto ndfs = [&](auto &self, ll v, ll p) -> void
    {
        for (auto i : adj[v])
        {
            if (i == p)
                continue;
            self(self, i, v);
            ans[v] += ans[i];
        }
        ans[v] += ep[v];
    };
    ndfs(ndfs, 0, -1);
    for (ll i = 0; i < n; i++)
        cout << ans[i] + ad[i] << " \n"[i == n - 1];
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    ll t = 1;
    // cin >> t;
    for (ll i = 1; i <= t; i++)
    {
        // cout << "Case #" << i << ": ";
        solve();
    }
    return (0 - 0);
}