#include <iostream>
#include <vector>

using namespace std;

int n, l;
vector<vector<int> > g;
vector<int> tin, tout;
int timer;
vector<vector<int> > up;

void dfs(int v, int p)
{
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];
    for (size_t i = 0; i < g[v].size(); ++i)
    {
        int to = g[v][i];
        if (to != p)
            dfs(to, v);
    }
    tout[v] = ++timer;
}

bool upper (int a, int b)
{
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca (int a, int b)
{
    if (upper(a, b))
        return a;
    if (upper(b, a))
        return b;
    for (int i = l; i >= 0; --i)
        if (!upper(up[a][i], b))
            a = up[a][i];
    return up[a][0];
}

int main()
{
    cin >> n;
    g.resize(n);
    for (int i = 0; i < n-1; ++i)
    {
        int a,b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    tin.resize(n), tout.resize(n), up.resize(n);
    l = 1;
    while ((1 << l) <= n)
        ++l;
    for (int i = 0; i < n; ++i)
        up[i].resize(l + 1);
    // Use arbitrary node as root. In this case 0
    dfs(0, 0);

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        int a,b;
        cin >> a >> b;
        cout << lca(a,b) << endl;
    }
}
