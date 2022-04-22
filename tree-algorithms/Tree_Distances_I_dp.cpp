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

struct path
{
    ll d, n;
};

void solve()
{
    ll n;
    cin >> n;
    vector<vector<ll>> adj(n);
    for (ll i = 1; i < n; i++)
    {
        ll u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<array<path, 2>> subtree(n);
    auto dfs_subtree = [&](auto &self, ll v, ll p) -> void
    {
        for (auto i : adj[v])
        {
            if (i == p)
                continue;
            self(self, i, v);
            if (subtree[i][0].d + 1 > subtree[v][0].d)
            {
                swap(subtree[v][0], subtree[v][1]);
                subtree[v][0] = {subtree[i][0].d + 1, i};
            }
            else if (subtree[i][0].d + 1 > subtree[v][1].d)
            {
                subtree[v][1] = {subtree[i][0].d + 1, i};
            }
        }
    };
    dfs_subtree(dfs_subtree, 0, -1);
    vector<ll> non_subtree(n);
    auto dfs = [&](auto &self, ll v, ll p) -> void
    {
        for (auto i : adj[v])
        {
            if (i == p)
                continue;
            if (subtree[v][0].n == i)
            {
                non_subtree[i] = 1 + max(non_subtree[v], subtree[v][1].d);
            }
            else
            {
                non_subtree[i] = 1 + max(non_subtree[v], subtree[v][0].d);
            }
            self(self, i, v);
        }
    };
    dfs(dfs, 0, -1);
    for (ll i = 0; i < n; i++)
    {
        cout << max(subtree[i][0].d, non_subtree[i]) << " \n"[i == n - 1];
    }
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