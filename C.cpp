#include<bits/stdc++.h>

using namespace std;

#define memset(a, v) memset(a, v, sizeof(a))
#define all(v) v.begin(), v.end()
#define f first
#define sc second
#define pb push_back
#define mp make_pair
#define speed() ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define pi 3.14159265358979323846
#define BFS_BLACK 1
#define BFS_WHITE -1
#define BFS_GREY 2
#define DFS_BLACK 1
#define DFS_WHITE -1
#define DFS_GREY 2
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<pair<ll,ll>> vii;
const int maxn = 2e5+7;

ll n, q, a[maxn];
ll lazy[4*maxn], tree[4*maxn];

void build(ll id, ll l, ll r)
{
    if (l == r)
    {
        tree[id] = a[l];
        return;
    }
    ll mid = (l+r)/2;
    build(2*id, l, mid);
    build(2*id+1, mid+1, r);
    tree[id] = max(tree[2*id], tree[2*id+1]);
}
void lazi(ll id, ll l, ll r)
{
    if (lazy[id] == 0)
    {
        return;
    }
    tree[id] += lazy[id];
    if (l != r)
    {
        lazy[2*id] += lazy[id];
        lazy[2*id+1] += lazy[id];
    }
    lazy[id] = 0;
}
ll Get(ll id, ll l, ll r, ll u, ll v)
{
    lazi(id, l, r);
    if (l > v || r < u)
    {
        return -(1e9+7);
    }
    if (l >= u && r <= v)
    {
        return tree[id];
    }
    ll mid = (l+r)/2;
    ll t1 = Get(2*id, l, mid, u, v);
    ll t2 = Get(2*id+1, mid+1, r, u, v);
    return max(t1, t2);
}
void update(ll id, ll l, ll r, ll u, ll v, ll val)
{
    lazi(id, l, r);
    if (l > v || r < u)
    {
        return;
    }
    if (l >= u && r <= v)
    {
        lazy[id] += val;
        lazi(id, l, r);
        return;
    }
    ll mid = (l+r)/2;
    update(2*id, l, mid, u, v, val);
    update(2*id+1, mid+1, r, u, v, val);
    tree[id] = max(tree[2*id], tree[2*id+1]);
}
int main()
{
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    speed();
    cin >> n >> q;
    for (ll i=1; i<=n; i++)
    {
        cin >> a[i];
    }
    build(1, 1, n);
    for (ll i=0; i<q; i++)
    {
        ll truyvan;
        cin >> truyvan;
        if (truyvan == 1)
        {
            ll x, y, val;
            cin >> x >> y >> val;
            update(1, 1, n, x, y, val);
        }
        else if (truyvan == 2)
        {
            ll pos;
            cin >> pos;
            ll max1 = Get(1, 1, n, pos, pos);
            cout << max1 << endl;
        }
    }
}

