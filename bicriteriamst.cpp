#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>

using namespace std;

struct Edge {
    int u, v, p, w;
    double adjWeight;
    Edge(int u, int v, int p, int w) : u(u), v(v), p(p), w(w) {}
};

bool canBuild(const int& N, const vector<Edge>& edges, const double& mid) {
    for(const auto& edge : edges) {
        double edge.adjWeight = edge.p - mid * edge.w;
        adjEdges.push_back(adjWeight, edge);
    }
}

int main() {

    // read N, M
    int N, M;
    cin >> N >> M;
    
    // edges vector contains all edges (u, v, p, w)
    vector<Edge> edges;
    int tot_weight = 0;
    int tot_profit = 0;
    for(int i = 0; i < M; i++) {
        int u, v, p, w;
        cin >> u >> v >> p >> w;
        edges.push_back(Edge(u, v, p, w));
        // calculate the total weight to define the high of bs
        tot_profit += p;
        tot_weight += w;
    }

    double low = 0;
    double high = tot_profit / tot_weight;

    // mid = max{m : canBuild(N, edges, m) == 1}
    while(low <= high) {
        double mid = (low + high) / 2;
        if(canBuild(N, edges, mid)) low = mid;
        else high = mid;
    }

    return 0;
}
