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

using item = int64_t;

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

    void build(vector<item> &a, ll x, ll lx, ll rx)
    {
        if (rx - lx == 1)
        {
            if (lx < (ll)a.size())
            {
                values[x] = a[lx];
            }
            return;
        }
        ll m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
    }

    void init(vector<item> &a)
    {
        size = p2(largest_bit((ll)a.size()) + 1);
        values.resize(2 * size, NEUTRAL_ELEMENT);
        build(a, 0, 0, size);
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
    ll n, q;
    cin >> n >> q;
    vector<ll> values(n);
    for (auto &i : values)
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
        cnt++;
        for (auto i : adj[v])
        {
            if (i == p)
                continue;
            self(self, i, v);
        }
        en[v] = cnt;
    };
    dfs(dfs, 0, -1);
    segtree st;
    vector<item> a(n);
    for (ll i = 0; i < n; i++)
        a[bg[i]] = values[i];
    st.init(a);
    while (q--)
    {
        ll t;
        cin >> t;
        if (t == 1)
        {
            ll s, x;
            cin >> s >> x;
            --s;
            st.modify(bg[s], x);
        }
        else
        {
            ll s;
            cin >> s;
            --s;
            cout << st.range_query(bg[s], en[s]) << '\n';
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