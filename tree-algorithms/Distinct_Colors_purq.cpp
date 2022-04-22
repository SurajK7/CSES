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
    vector<item> values;
    item NEUTRAL_ELEMENT = 0;

    item merge(item a, item b)
    {
        return a + b;
    }

    void init(ll n)
    {
        size = p2(largest_bit(n) + 1);
        values.resize(2 * size, NEUTRAL_ELEMENT);
    }

    void modify(ll i, item v)
    {
        i += size - 1;
        values[i] = v;
        while (i)
        {
            i = (i - 1) / 2;
            values[i] = merge(values[2 * i + 1], values[2 * i + 2]);
        }
    }

    item range_query(ll x, ll lx, ll rx, ll l, ll r)
    {
        if (lx >= r || rx <= l)
            return NEUTRAL_ELEMENT;
        if (lx >= l && rx <= r)
            return values[x];
        ll m = (lx + rx) / 2;
        item y = range_query(2 * x + 1, lx, m, l, r), z = range_query(2 * x + 2, m, rx, l, r);
        item res = merge(y, z);
        return res;
    }

    item range_query(ll l, ll r)
    {
        return range_query(0, 0, size, l, r);
    }
};

void solve()
{
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (auto &i : a)
        cin >> i;
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
        ++cnt;
        for (auto i : adj[v])
        {
            if (i == p)
                continue;
            self(self, i, v);
        }
        en[v] = cnt;
    };
    dfs(dfs, 0, -1);
    vector<ll> v(n);
    for (ll i = 0; i < n; i++)
    {
        v[bg[i]] = a[i];
    }
    segtree st;
    st.init(n);
    map<ll, deque<ll>> occ;
    for (ll i = 0; i < n; i++)
    {
        occ[v[i]].push_back(i);
    }
    vector<pair<array<ll, 2>, ll>> queries(n);
    for (ll i = 0; i < n; i++)
    {
        queries[i] = {{bg[i], en[i]}, i};
    }
    sort(all(queries));
    for (auto i : occ)
        st.modify(i.second.front(), 1);
    vector<ll> ans(n);
    ll j = 0;
    for (ll i = 0; i < n; i++)
    {
        while (j < queries[i].first[0])
        {
            if (st.range_query(j, j + 1) == 1)
            {
                occ[v[j]].pop_front();
                if (!occ[v[j]].empty())
                {
                    st.modify(occ[v[j]].front(), 1);
                }
            }
            ++j;
        }
        ans[queries[i].second] = st.range_query(queries[i].first[0], queries[i].first[1]);
    }
    for (ll i = 0; i < n; i++)
        cout << ans[i] << " \n"[i == n - 1];
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