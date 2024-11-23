#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

// complexity(canPlace) = Ο(Μ)
bool canPlace(const vector<pair<int, int>>& intervals, const int& n, const int& d) {
    int placed = 0;                             // none of the stores are located
    int lastPlaced = INT_MIN;                   // init starting position
    for(const auto& interval : intervals) {     // for each interval check
        int start = interval.first;             // start for the start-position
        int end = interval.second;
        int pos = max(start, lastPlaced + d);   // if the start position is further that prev_position + d
        while(pos <= end) {                     // until we reach the end of the interval
            lastPlaced = pos;                   // we save the current position as prev position
            placed++;                           // 1 more store located
            if(placed == n) return true;        // if we reach n stores we return true
            pos += d;                           // else check again for one more store
        }
    }
    return false;
}

int main() {

    // auto io_start = high_resolution_clock::now();
    int N, M;
    cin >> N >> M;      // read N, M from stdin
    vector<pair<int, int>> intervals;       // create vector to contain intervals [si, fi]

    for(int i=0; i<M; i++) {
        int si, fi;
        scanf("%d %d", &si, &fi);          // read interval [si, fi]
        intervals.push_back(make_pair(si, fi));     // push [si, fi] into the interval
    }

    // auto io_finish = high_resolution_clock::now();
    // duration<double> io_elapsed = io_finish - io_start;
    // printf("Time take for IO: %f seconds.\n", io_elapsed.count());

    auto start = high_resolution_clock::now();      // start = clock
    
    // sort the intervals such as f1 <= ... <= fn
    // complexity(sort) = O(M*logM)
    sort(intervals.begin(), intervals.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second;
    });

    int smin = intervals[0].first;
    int fmax = intervals[M-1].second;
    int result = 0;
    int low = 1;
    int high = (fmax-smin)/(M-1);

    // binary search of mid
    // we search for mid = max{m : canPlace(interval, N, m) = true}
    // complexity(binary_search) = O(logD), D = high-low
    while(low <= high) {
        int mid = (low +  high)/2;
        if(canPlace(intervals, N, mid)) {
            result = mid;
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    printf("%d\n", result);                             // print the result

    auto finish = high_resolution_clock::now();         // finish = clock
    duration<double> elapsed = finish - start;          // duration
    printf("Algorithm Time: %f seconds.\n", elapsed.count());

    // Total complexity is O(M*logM) + O(M*logD) = O(M*logM)
    return 0;
}
