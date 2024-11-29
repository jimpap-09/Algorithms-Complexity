#include <iostream>
#include <algorithm>
#include <vector>
#include <limits.h>

using namespace std;


// struct for edges
// each edge has form : (u, v, p, w)
// u = src, v = dest, p = profit, w = weight
// adjWeight = adjasted weight
struct Edge {
    int u, v, p, w;
    double adjWeight;
    Edge(int u, int v, int p, int w) : u(u), v(v), p(p), w(w), adjWeight(0.0) {}
};

// each node belongs to a subset-tree
// that has a parent (root) and a rank
struct subset {
    int parent;
    int rank;
};

// struct for mst
// and has total profit and weight
struct MST {
    int total_profit;
    int total_weight;
};

// struct for DSU : Disjoint Set Union
struct DSU {
    // N : nodes
    int N;
    vector<subset> subsets;

    // DSU constructor
    // each node i has parent(i) = i and rank(i) = 0
    DSU(int N) {
        this->N = N;
        subsets.resize(N);
        for(int i=0; i<N; i++) {
            subsets[i].parent = i;
            subsets[i].rank = 0;
        }
    }

    // if isCycle(e) = true
    // we ignore the edge e, cause it creates cycle
    // therefore it doesnt belong to the mst
    bool isCycle(Edge e) {
        int x = find_path_compression(e.u);
        int y = find_path_compression(e.v);
        if(x == y) return true;
        else union_by_rank(x, y);
        return false;
    }

    // union by rank
    void union_by_rank(int x, int y) {
        if(subsets[x].rank > subsets[y].rank) subsets[y].parent = subsets[x].parent;
        else if(subsets[x].rank < subsets[y].rank) subsets[x].parent = subsets[y].parent;
        else {
            subsets[y].parent = subsets[x].parent;
            subsets[x].rank++;
        }
    }

    // find with path compression
    int find_path_compression(int x) {
        if(subsets[x].parent != x) subsets[x].parent = find_path_compression(subsets[x].parent);
        return subsets[x].parent;
    }
};

// gcd function
int _gcd(int a, int b) {
    return b == 0 ? a : _gcd(b, a % b);
}

// build mst function
// on a graph with adjasted weights
// find the tree with the most adjasted weight
MST build_mst(int N, vector<Edge>& edges, double x) {
    // change the adjasted weight for each edge
    for(auto& edge : edges) {
        edge.adjWeight = edge.p - edge.w * x;
    }

    // sort the edges such as e1.adjWeight > e2.adjweight
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.adjWeight > b.adjWeight;
    });
    
    // create a dsu of N nodes
    DSU dsu(N);

    // init mst stats
    int edge_counter = 0;
    int total_profit = 0;
    int total_weight = 0;

    // for each edge
    // if it's a valid edge
    // update the stats and add the edge to the mst
    // and return the mst when N-1 edges have been added to the mst
    for(const auto& edge : edges) {
        if(!dsu.isCycle(edge)) {
            edge_counter++;
            total_profit += edge.p;
            total_weight += edge.w;
            if(edge_counter == N-1) break;
        }
    }

    return {total_profit, total_weight};
}

// main function
int main() {

    // read N : nodes and M : edges
    int N, M;
    cin >> N >> M;
    
    vector<Edge> edges;

    // init the limits
    int min_frac = INT_MAX;
    int max_frac = INT_MIN;

    // read the edges
    for(int i = 0; i < M; i++) {
        int u, v, p, w;
        cin >> u >> v >> p >> w;
        edges.push_back(Edge(u-1, v-1, p, w));
        // update the limits of Binary Search
        int frac = p / w;
        if(frac >= max_frac) max_frac = frac;
        if(frac <= min_frac) min_frac = frac;
    }

    // init mst results
    int best_profit = 0;
    int best_weight = 0;
    double result;

    // Binary Search
    // for each x
    // create build_mst return mst with adjasted weight
    // if mst.total_weight > 0 then calculate the fraction P/W
    // if its bigger than x then search the higher part
    // otherwise search the lower part

    double low = min_frac;
    double high = max_frac;

    while(high - low > 1e-9) {
        double x = (low + high) / 2.0;
        MST mst = build_mst(N, edges, x);
        if(mst.total_weight > 0) {
            double result = (double) mst.total_profit/mst.total_weight;
            if(result >= x) {
                best_profit = mst.total_profit;
                best_weight = mst.total_weight;
                low = x;
            }
            else high = x;
        }
    }

    // gcd(P, W)
    int gcd = _gcd(best_profit, best_weight);

    cout << best_profit / gcd << " " << best_weight / gcd << endl;

    return 0;
}
