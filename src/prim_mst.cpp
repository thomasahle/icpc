int n;
// Adjacency list. g[i][j].first = x, where i->x is the j'th edge from i.
// Second is cost of edge i->x
vector<vector<pair<int, int> > >g;
const int INF = 1000000000;

// min_e should be of size n initialized to INF
// sel_e should be of size n initialized to -1
void prim(vector<int>& min_e, vector<int>& sel_e)
{
    min_e[0] = 0;
    set <pair<int, int> > q;
    bool done[n];
    memset(done, 0, sizeof(done));
    q.insert(make_pair(0, 0));
    for (int i = 0; i < n; ++i)
    {
        // if q is empty there is no MST. We assume there is!
        int v = q.begin()->second;
        q.erase(q.begin());
        done[v] = true;

        for (size_t j = 0; j < g[v].size(); ++j)
        {
            int to = g[v][j].first,
                cost = g[v][j].second;
            if (done[to])
                continue;
            if (cost < min_e[to])
            {
                q.erase(make_pair(min_e[to], to));
                min_e[to] = cost;
                sel_e[to] = v;
                q.insert(make_pair(min_e[to], to));
            }
        }
    }
}
