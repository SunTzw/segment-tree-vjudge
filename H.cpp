
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

string s;
ll tree[27][4*maxn], lazy[27][4*maxn];
ll cnt[27], n, q;

void Build(ll id, ll l, ll r)
{
    for (ll c=0; c<26; c++)
    {
        lazy[c][id] = -1;
    }
    if (l == r)
    {
        tree[s[l - 1] - 'a'][id] = 1;
        return;
    }
    ll mid = (l+r)/2;
    Build(2*id, l, mid);
    Build(2*id+1, mid+1, r);
    for (ll c=0; c<26; c++)
    {
        tree[c][id] = tree[c][2*id] + tree[c][2*id+1];
    }
}
void Lazi(ll id, ll l, ll r, ll c)
{
    if (lazy[c][id] == -1)
    {
        return;
    }
    tree[c][id] = lazy[c][id]*(r-l+1);
    if (l != r)
    {
        lazy[c][2*id] = lazy[c][id];
        lazy[c][2*id+1] = lazy[c][id];
    }
    lazy[c][id] = -1;
}
void Update(ll id, ll l, ll r, ll u, ll v, ll val, ll c)
{
    Lazi(id, l, r, c);
    if (l > v || r < u)
    {
        return;
    }
    if (l >= u && r <= v)
    {
        lazy[c][id] = val;
        Lazi(id, l, r, c);
        return;
    }
    ll mid = (l+r)/2;
    Update(2*id, l, mid, u, v, val, c);
    Update(2*id+1, mid+1, r, u, v, val, c);
    tree[c][id] = tree[c][2*id] + tree[c][2*id+1];
}
ll Get(ll id, ll l, ll r, ll u, ll v, ll c)
{
    Lazi(id, l, r, c);
    if (l > v || r < u)
    {
        return 0;
    }
    if (l >= u && r <= v)
    {
        return tree[c][id];
    }
    ll mid = (l+r)/2;
    ll t1 = Get(2*id, l, mid, u, v, c);
    ll t2 = Get(2*id+1, mid+1, r, u, v, c);
    return t1 + t2;
}
int main()
{
//    freopen(".INP", "r", stdin);
//    freopen(".OUT", "w", stdout);
    speed();
    cin >> n >> q;
    cin >> s;
    Build(1, 1, n);
    for (ll t=0; t<q; t++)
    {
        ll i, j, k;
        cin >> i >> j >> k;
        for (ll c=0; c<26; c++)
        {
            cnt[c] = Get(1, 1, n, i, j, c);
            Update(1, 1, n, i, j, 0, c);
        }
        ll s1 = 0;
        if (k == 1)
        {
            ll cur = i;
            for (ll c=0; c<26; c++)
            {
                if (cnt[c] == 0)
                {
                    continue;
                }
                Update(1, 1, n, cur, cur + cnt[c] - 1, 1, c);
                cur += cnt[c];
            }
        }
        else
        {
            ll cur = i;
            for (ll c=25; c>=0; c--)
            {
                if(cnt[c] == 0)
                {
                    continue;
                }
                Update(1, 1, n, cur, cur + cnt[c] - 1, 1, c);
                cur += cnt[c];
            }
        }
    }
    for (ll i=1; i<=n; i++)
    {
        for (ll c=0; c<26; c++)
        {
            if (Get(1, 1, n, i, i, c) == 1)
            {
                cout << (char)(c + 'a');
                break;
            }
        }
    }
}

