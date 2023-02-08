#include<bits/stdc++.h>

using namespace std;

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
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<pair<ll,ll>> vii;
const ll maxn = 1e5+7;

ll n, q, a[maxn];
ll tree[4*maxn];
ll size1[4*maxn];

void build(ll id, ll l, ll r)
{
    if (l == r)
    {
        tree[id] = a[l];
        size1[id] = 1;
        return;
    }
    ll mid = (l+r)/2;
    build(2*id, l, mid);
    build(2*id+1, mid+1, r);
    tree[id] = __gcd(tree[2*id], tree[2*id+1]);
    if (tree[id] == tree[2*id])
    {
        size1[id] += size1[2*id];
    }
    if (tree[id] == tree[2*id+1])
    {
        size1[id] += size1[2*id+1];
    }
}
ii Get(ll id, ll l, ll r, ll u, ll v)
{
    if (l > v || r < u)
    {
        return {0, 0};
    }
    if (l >= u && r <= v)
    {
        ii temp;
        temp.f = tree[id];
        temp.sc = size1[id];
        return temp;
    }
    ll mid = (l+r)/2;
    ii get1 = Get(2*id, l, mid, u, v);
    ii get2 = Get(2*id+1, mid+1, r, u, v);
    ii gcd;
    gcd.f = __gcd(get1.f, get2.f);
    gcd.sc = 0;
    if (get1.f == gcd.f)
    {
        gcd.sc += get1.sc;
    }
    if (get2.f == gcd.f)
    {
        gcd.sc += get2.sc;
    }
    return gcd;
}

int main()
{
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    speed();
    cin >> n;
    for (ll i=1; i<=n; i++)
    {
        cin >> a[i];
    }
    cin >> q;
    mems(size1, 0);
    mems(tree, 0);
    build(1, 1, n);
    for (ll i=0; i<q; i++)
    {
        ll x, y;
        cin >> x >> y;
        ii t = Get(1, 1, n, x, y);
//        cout << "Gcd of set: " << t.f << endl;
        cout << y-x-t.sc+1 << endl;
    }
}

