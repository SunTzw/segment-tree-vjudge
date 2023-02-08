
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
const ll maxn = 1e6 + 20;
const ll mod = 1e9 + 7;

ll a[maxn];

struct node
{
    ll cnt4 = 0;
    ll cnt7 = 0;
    ll lis = 0;
    ll lds = 0;
    bool check = false;
    node() {}
    node (ll _cnt4, ll _cnt7, ll _lis, ll _lds, bool _check)
    {
        cnt4 = _cnt4;
        cnt7 = _cnt7;
        lis = _lis;
        lds = _lds;
        check = _check;
    }
};

node tree[4*maxn];

void swap(ll &a, ll &b)
{
    ll t = a;
    a = b;
    b = t;
}
void mmb(ll id)
{
    tree[id].check = !tree[id].check;
    swap(tree[id].lis, tree[id].lds);
    swap(tree[id].cnt4, tree[id].cnt7);
}
void push(ll id)
{
    if (tree[id].check)
    {
        mmb(2*id);
        mmb(2*id + 1);
        tree[id].check = false;
    }
}
void Build(ll id, ll l, ll r)
{
    if (l == r)
    {
        tree[id].lis = 1;
        tree[id].lds = 1;
        if (a[l] == 4)
        {
            tree[id].cnt4++;
        }
        else
        {
            tree[id].cnt7++;
        }
        return;
    }
    ll mid = (l+r)/2;
    Build(2*id, l, mid);
    Build(2*id+1, mid+1, r);
    tree[id].lis = max(max(max(tree[2*id].lis, tree[2*id+1].lis), tree[2*id].cnt4 + tree[2*id+1].lis), tree[2*id].lis + tree[2*id+1].cnt7);
    tree[id].lds = max(max(max(tree[2*id].lds, tree[2*id+1].lds), tree[2*id].cnt7 + tree[2*id+1].lds), tree[2*id].lds + tree[2*id+1].cnt4);
    tree[id].cnt4 = tree[2*id].cnt4 + tree[2*id+1].cnt4;
    tree[id].cnt7 = tree[2*id].cnt7 + tree[2*id+1].cnt7;
}
void Update(ll id, ll l, ll r, ll u, ll v)
{
    if (l == u && r == v)
    {
        mmb(id);
        return;
    }
    push(id);
    ll mid = (l+r)/2;
    if (v <= mid)
    {
        Update(2*id, l, mid, u, v);
    }
    else if (u >= mid+1)
    {
        Update(2*id+1, mid+1, r, u, v);
    }
    else
    {
        Update(2*id, l, mid, u, mid);
        Update(2*id+1, mid+1, r, mid+1, v);
    }
    tree[id].lis = max(max(max(tree[2*id].lis, tree[2*id+1].lis), tree[2*id].cnt4 + tree[2*id+1].lis), tree[2*id].lis + tree[2*id+1].cnt7);
    tree[id].lds = max(max(max(tree[2*id].lds, tree[2*id+1].lds), tree[2*id].cnt7 + tree[2*id+1].lds), tree[2*id].lds + tree[2*id+1].cnt4);
    tree[id].cnt4 = tree[2*id].cnt4 + tree[2*id+1].cnt4;
    tree[id].cnt7 = tree[2*id].cnt7 + tree[2*id+1].cnt7;
}
int main()
{
    //freopen(".INP", "r", stdin);
    //freopen(".OUT", "w", stdout);
    speed();
    ll n, q;
    cin >> n >> q;
    for (ll i=1; i<=n; i++)
    {
        char c;
        cin >> c;
        a[i] = c - '0';
    }
//    for (ll i=1; i<=n; i++)
//    {
//        cout << a[i] << " ";
//    }
//    cout << endl;
    Build(1, 1, n);
    for (ll i=0; i<q; i++)
    {
        string s;
        cin >> s;
        if (s == "count")
        {
            cout << tree[1].lis << endl;
        }
        else
        {
            ll u, v;
            cin >> u >> v;
            Update(1, 1, n, u ,v);
        }
    }
    return 0;
}

