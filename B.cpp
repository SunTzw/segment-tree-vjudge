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
const ll maxn = 2e5+7;

ll n, q, a[maxn];
ll tree[4*maxn];

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
    tree[id] = tree[2*id] + tree[2*id+1];
}
void Update(ll id, ll l, ll r, ll i, ll val)
{
    if (l > i || r < i)
    {
        return;
    }
    if (l == r)
    {
        tree[id] = val;
        return;
    }
    ll mid = l + (r-l)/2;
    Update(2*id, l, mid, i, val);
    Update(2*id+1, mid+1, r, i, val);
    tree[id] = tree[2*id] + tree[2*id+1];
}
ll Get(ll id, ll l, ll r, ll u, ll v)
{
    if (l > v || r < u)
    {
        return 0;
    }
    if (l >= u && r <= v)
    {
        return tree[id];
    }
    ll mid = l + (r-l)/2;
    ll get1 = Get(2*id, l, mid, u, v);
    ll get2 = Get(2*id+1, mid+1, r, u, v);
    return get1 + get2;
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
        ll truyvan, x, y;
        cin >> truyvan >> x >> y;
        if (truyvan == 1)
        {
            Update(1, 1, n, x, y);
        }
        else if (truyvan == 2)
        {
            ll min1 = Get(1, 1, n, x, y);
            cout << min1 << endl;
        }
    }
}

