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
    ll n, q;
    cin >> n >> q;
    ll max_jump = largest_bit(n);
    vector<vector<ll>> children(n), ancestors(max_jump + 1, vector<ll>(n, -1));
    for (ll i = 1; i < n; i++)
    {
        ll p;
        cin >> p;
        --p;
        children[p].push_back(i);
        ancestors[0][i] = p;
    }
    for (ll i = 1; i <= max_jump; i++)
    {
        for (ll j = 0; j < n; j++)
        {
            if (ancestors[i - 1][j] != -1)
            {
                ancestors[i][j] = ancestors[i - 1][ancestors[i - 1][j]];
            }
        }
    }
    auto kth_ancestor = [&](ll v, ll k)
    {
        ll i = 0;
        while (k > 0 && v != -1)
        {
            if (k & 1)
                v = ancestors[i][v];
            i++;
            k /= 2;
        }
        return v;
    };
    while (q--)
    {
        ll v, k;
        cin >> v >> k;
        --v;
        ll res = kth_ancestor(v, k);
        cout << (res == -1 ? -1 : res + 1) << '\n';
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