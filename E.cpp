
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
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
const ll maxn = 2e5 + 7;

ll a[maxn], type, l, r, n, q;

int main()
{
    speed();
    cin >> n;
    for (ll i=1; i<=n; i++)
    {
        cin >> a[i];
    }
    cin >> q;
    for (ll i=0; i<q; i++)
    {
        cin >> type;
        if (type == 1)
        {
            cin >> l >> r;
            ll tong = 0;
            for (ll i=l; i<=r; i++)
            {
                tong += a[i];
            }
            cout << tong << endl;
        }
        else
        {
            ll x;
            cin >> l >> r >> x;
            for (ll i=l; i<=r; i++)
            {
                a[i]^=x;
            }
        }
    }
}

