#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>

using namespace std;

struct Edge {
    int u, v, p, w;
    Edge(int u, int v, int p, int w) : u(u), v(v), p(p), w(w) {}
};

int main() {

    int N, M;
    cin >> N >> M;
    vector<Edge> edges;
    int tot_weight = 0;
    for(int i = 0; i < M; i++) {
        int u, v, p, w;
        cin >> u >> v >> p >> w;
        edges.push_back(Edge(u, v, p, w));
        tot_weight += w;
    }

    double low = 0;
    double high = tot_weight;

    // mid = max{m : canBuild(N, edges, m) == 1}
    while(low <= high) {
        double mid = (low + high) / 2;
        if(canBuild(N, edges, mid)) low = mid;
        else high = mid;
    }

    return 0;
}