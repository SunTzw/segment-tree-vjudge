
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
const ll maxn = 2e5 + 20;
const ll mod = 1e9 + 7;

struct node
{
    ll ans = 0;
    ll cntL = 0;
    ll cntR = 0;

    node() {}
    node (ll _ans, ll _cntL, ll _cntR)
    {
        ans = _ans;
        cntL = _cntL;
        cntR = _cntR;
    }
};

node tree[4*maxn];
ll a[maxn], n, q;

node Merge(node lx, node rx, ll l, ll mid, ll r)
{
    node temp;
    temp.ans = temp.ans + lx.ans + rx.ans;
    if (a[mid] <= a[mid+1])
    {
        temp.ans = temp.ans + lx.cntR*rx.cntL;
    }
    if (a[mid] <= a[mid+1] && lx.cntL == mid - l + 1)
    {
        temp.cntL = temp.cntL + lx.cntL + rx.cntL;
    }
    else
    {
        temp.cntL = lx.cntL;
    }
    if (a[mid] <= a[mid+1] && rx.cntR == r - mid)
    {
        temp.cntR = temp.cntR + lx.cntR + rx.cntR;
    }
    else
    {
        temp.cntR = rx.cntR;
    }
    return temp;
}
void Build(ll id, ll l, ll r)
{
    if (l == r)
    {
        tree[id] = node(1, 1, 1);
        return;
    }
    ll mid = (l+r)/2;
    Build(2*id, l, mid);
    Build(2*id+1, mid+1, r);
    tree[id] = Merge(tree[2*id], tree[2*id+1], l, mid, r);
}
void Update(ll id, ll l, ll r, ll p, ll val)
{
    if (l == r)
    {
        a[p] = val;
        return;
    }
    ll mid = (l+r)/2;
    if (p <= mid)
    {
        Update(2*id, l, mid, p, val);
    }
    else
    {
        Update(2*id+1, mid+1, r, p, val);
    }
    tree[id] = Merge(tree[2*id], tree[2*id+1], l, mid, r);
}
node Get(ll id, ll l, ll r, ll u, ll v)
{
    if (l == u && r == v)
    {
        return tree[id];
    }
    ll mid = (l+r)/2;
    if (v <= mid)
    {
        return Get(2*id, l, mid, u, v);
    }
    else if (u >= mid+1)
    {
        return Get(2*id+1, mid+1, r, u, v);
    }
    else
    {
        return Merge(Get(2*id, l, mid, u, mid), Get(2*id+1, mid+1, r, mid+1, v), u, mid, v);
    }
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
    Build(1, 1, n);
    for (ll i=0; i<q; i++)
    {
        ll type, x, y;
        cin >> type >> x >> y;
        if (type == 1)
        {
            Update(1, 1, n, x, y);
        }
        else
        {
            cout << Get(1, 1, n, x, y).ans << endl;
        }
    }
}

