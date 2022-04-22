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

#ifdef DEBUG
#include "/home/suraj/cp/debug.hpp"
#else
#define debug(...) 0
#endif

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

constexpr ll p2(ll x) { return (ll)1 << x; }
constexpr ll msk2(ll x) { return p2(x) - 1; }
constexpr ll pct(ll x) { return __builtin_popcountll(x); } // # of bits set
constexpr ll largest_bit(ll x) { return x == 0 ? (ll)-1 : (ll)63 - __builtin_clzll(x); }

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

using item = ll;

struct segtree
{
    using ll = int64_t;
    ll p2(ll x) { return (ll)1 << x; }
    ll largest_bit(ll x) { return x == 0 ? (ll)-1 : (ll)63 - __builtin_clzll(x); }
    ll size;
    vector<item> operations;
    item NEUTRAL_ELEMENT = 0;

    item merge(item a, item b)
    {
        return a + b;
    }

    void init(ll n)
    {
        size = p2(largest_bit(n) + 1);
        operations.resize(2 * size, NEUTRAL_ELEMENT);
    }

    item query(ll i)
    {
        i += size - 1;
        item res = operations[i];
        while (i)
        {
            i = (i - 1) / 2;
            res = merge(res, operations[i]);
        }
        return res;
    }

    void modify(ll x, ll lx, ll rx, ll l, ll r, item v)
    {
        if (lx >= r || rx <= l)
            return;
        if (lx >= l && rx <= r)
        {
            operations[x] = merge(operations[x], v);
            return;
        }
        ll m = (lx + rx) / 2;
        modify(2 * x + 1, lx, m, l, r, v);
        modify(2 * x + 2, m, rx, l, r, v);
    }

    void modify(ll l, ll r, item v)
    {
        modify(0, 0, size, l, r, v);
    }
};

void solve()
{
    ll n, q;
    cin >> n >> q;
    vector<ll> values(n), a;
    for (auto &i : values)
        cin >> i;
    a = values;
    vector<vector<ll>> adj(n);
    for (ll i = 0; i < n - 1; i++)
    {
        ll u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<ll> bg(n), en(n);
    ll cnt = 0;
    auto dfs = [&](auto &self, ll v, ll p) -> void
    {
        bg[v] = cnt;
        cnt++;
        for (auto i : adj[v])
        {
            if (i == p)
                continue;
            a[i] += a[v];
            self(self, i, v);
        }
        en[v] = cnt;
    };
    dfs(dfs, 0, -1);
    segtree st;
    st.init(n);
    while (q--)
    {
        ll t;
        cin >> t;
        if (t == 1)
        {
            ll s, x;
            cin >> s >> x;
            --s;
            st.modify(bg[s], en[s], x - values[s]);
            values[s] = x;
        }
        else
        {
            ll s;
            cin >> s;
            --s;
            cout << a[s] + st.query(bg[s]) << '\n';
        }
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