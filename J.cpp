
#include<bits/stdc++.h>

using namespace std;

#define mems(a, v) memset(a, v, sizeof(a))
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
//typedef int ll;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<pair<ll,ll>> vii;
typedef vector<vi> vvi;
const ll maxn = 1e5 + 7;
const ll mod = 1e9 + 7;
const ll inf = 1e18;

vii tree[9*maxn];
ll dis[9*maxn], a[maxn], base, n, q, s;

void Build(ll id, ll l, ll r)
{
    if (l == r)
    {
        ll idx = a[l];
        tree[idx].pb(ii(id, 0));
        tree[idx].pb(ii(id + base, 0));
        tree[id].pb(ii(idx, 0));
        tree[id + base].pb(ii(idx, 0));
        return;
    }
    ll mid = (l+r)/2;
    Build(2*id, l, mid);
    Build(2*id+1, mid+1, r);

    tree[id].pb(ii(2*id, 0));
    tree[id].pb(ii(2*id+1, 0));

    tree[2*id + base].pb(ii(id + base, 0));
    tree[2*id + 1 + base].pb(ii(id + base, 0));
}
void Add_query_type2(ll id, ll l, ll r, ll u, ll v, ll k, ll w)
{
    if (l > v || r < u)
    {
        return;
    }
    if (l >= u && r <= v)
    {
        tree[a[k]].pb(ii(id, w));
        return;
    }
    ll mid = (l+r)/2;
    Add_query_type2(2*id, l, mid, u, v, k, w);
    Add_query_type2(2*id+1, mid+1, r, u, v, k, w);
}
void Add_query_type3(ll id, ll l, ll r, ll u, ll v, ll k, ll w)
{
    if (l > v || r < u)
    {
        return;
    }
    if (l >= u && r <= v)
    {
        tree[id + base].pb(ii(a[k], w));
        return;
    }
    ll mid = (l+r)/2;
    Add_query_type3(2*id, l, mid, u, v, k, w);
    Add_query_type3(2*id+1, mid+1, r, u, v, k, w);
}
void dijsktra(ll i)
{
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    for(ll i=1; i<=9*n; i++)
    {
        dis[i] = inf;
    }
    dis[i] = 0;
    pq.push(ii(dis[i], i));
    while(!pq.empty())
    {
        ii top = pq.top();
        ll d = top.f;
        ll u = top.sc;
        pq.pop();
        if (d != dis[u])
        {
            continue;
        }
        for (ii temp: tree[u])
        {
            ll v = temp.f;
            ll w = temp.sc;
            if (dis[v] > d + w)
            {
                dis[v] = d + w;
                pq.push(ii(dis[v], v));
            }
        }
    }

}
int main()
{
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    speed();
    cin >> n >> q >> s;
    for (ll i=1; i<=n; i++)
    {
        a[i] = i + 8*n;
    }
    base = 4*n;
    Build(1, 1, n);
    for (ll i=0; i<q; i++)
    {
        ll type;
        cin >> type;
        if (type == 1)
        {
            ll u, v, w;
            cin >> u >> v >> w;
            tree[a[u]].pb(ii(a[v], w));
        }
        else
        {
            ll u, l, r, w;
            cin >> u >> l >> r >> w;
            if (type == 2)
            {
                Add_query_type2(1, 1, n, l, r, u, w);
            }
            if (type == 3)
            {
                Add_query_type3(1, 1, n, l, r, u, w);
            }
        }
    }
    dijsktra(a[s]);
    for (ll i=1; i<=n; i++)
    {
        if (dis[a[i]] == inf)
        {
            dis[a[i]] = -1;
        }
        cout << dis[a[i]] << " ";
    }
    cout << endl;

}


