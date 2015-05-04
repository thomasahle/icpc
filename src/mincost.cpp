// Implementation of min cost max flow algorithm using adjacency
// matrix (Edmonds and Karp 1972).  This implementation keeps track of
// forward and reverse edges separately (so you can set cap[i][j] !=
// cap[j][i]).  For a regular max flow, set all edge costs to 0.
//
// Running time, O(|V|^2) cost per augmentation
//     max flow:           O(|V|^3) augmentations
//     min cost max flow:  O(|V|^4 * MAX_EDGE_COST) augmentations
//
// INPUT:
//     - graph, constructed using AddEdge()
//     - source
//     - sink
//
// OUTPUT:
//     - (maximum flow value, minimum cost value)
//     - To obtain the actual flow, look at positive values only.

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <limits>
#include <queue>

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)

using namespace std;

typedef int F;
typedef double C;
#define F_INF (1<<29)
#define C_INF 1.0E+9
#define MAXV 900
#define MAXE 400000 // E*2!

int V,E;
F cap[MAXE];
C cost[MAXE],dist[MAXV],pot[MAXV];
int to[MAXE],prev[MAXE],last[MAXV],path[MAXV];
bool used[MAXV];
priority_queue <pair <C, int> > q;

const inline int in(int i) { return 2*i; }
const inline int out(int i) { return 2*i+1; }

class MinCostFlow{
    public:

    MinCostFlow(int n){
        int i;
        V = n; E = 0;
        REP(i,V) last[i] = -1;
    }

    void add_edge(int x, int y, F w, C c){
        cap[E] = w; cost[E] = c; to[E] = y; prev[E] = last[x]; last[x] = E; E++;
        cap[E] = 0; cost[E] = -c; to[E] = x; prev[E] = last[y]; last[y] = E; E++;
    }

    pair <F, C> search(int s, int t){
        F ansf=0; C ansc=0;
        int i;

        REP(i,V) used[i] = false;
        REP(i,V) dist[i] = C_INF;

        dist[s] = 0; path[s] = -1; q.push(make_pair(0,s));
        while(!q.empty()){
            int x = q.top().second; q.pop();
            if(used[x]) continue; used[x] = true;
            for(int e=last[x];e>=0;e=prev[e]) if(cap[e] > 0){
                C tmp = dist[x] + cost[e] + pot[x] - pot[to[e]];
                if(tmp < dist[to[e]] && !used[to[e]]){
                    dist[to[e]] = tmp;
                    path[to[e]] = e;
                    q.push(make_pair(-dist[to[e]],to[e]));
                }
            }
        }

        REP(i,V) pot[i] += dist[i];

        if(used[t]){
            ansf = F_INF;
            for(int e=path[t];e>=0;e=path[to[e^1]]) ansf = min(ansf,cap[e]);
            for(int e=path[t];e>=0;e=path[to[e^1]]) {ansc += cost[e] * ansf; cap[e] -= ansf; cap[e^1] += ansf;}
        }

        return make_pair(ansf,ansc);
    }

    pair <F, C> mincostflow(int s, int t){
        F ansf=0; C ansc=0;
        int i;
        while(1){
            pair <F, C> p = search(s,t);
            if(!used[t]) break;
            ansf += p.first; ansc += p.second;
        }
        return make_pair(ansf,ansc);
    }
};

int main()
{
    int n;
    cin >> n;
    double x[405], y[405];
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }
    int src = in(n);
    int snk = out(n);
    int top = 0;
    for (int i = 1; i < n; ++i) {
        if (y[i] > y[top])
            top = i;
    }
    for (int i = 0; i < n; ++i)
    {
        if (y[i] == y[top] && i != top) {
            cout << "-1" << endl;
            return 0;
        }
    }
    MinCostFlow mcmf(2 * n + 2);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (y[i] < y[j]) {
                mcmf.add_edge(out(i), in(j), 1, sqrt((y[j]-y[i])*(y[j]-y[i]) + (x[j]-x[i])*(x[j]-x[i])));
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (i != top)
            mcmf.add_edge(src, out(i), 1, 0);
        mcmf.add_edge(in(i), snk, 2, 0);
    }
    pair<F,C> pfc = mcmf.mincostflow(src, snk);
    if (pfc.first < n-1)
        cout << "-1" << endl;
    else
        printf("%.8f\n", pfc.second);
}
