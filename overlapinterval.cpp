#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// interval structure
struct Interval {
    int si, fi, idx;
    Interval(int start, int finish, int index) : si(start), fi(finish), idx(index) {}
};

// greedy selection of a solution
vector<Interval> greedy_selection(const vector<Interval>& intervals) {
    vector<Interval> selected;

    // if there are no intervals return empty
    if (intervals.empty()) return selected;

    // sort by increasing fi
    vector<Interval> sorted_intervals = intervals;
    sort(sorted_intervals.begin(), sorted_intervals.end(), [](const Interval& a, const Interval& b) {
        return a.fi < b.fi;
    });

    // always choose the first interval
    selected.push_back(sorted_intervals[0]);
    int last_finish_time = sorted_intervals[0].fi;

    // choose the next interval without overlapping with the previous one
    for (const auto& interval : sorted_intervals) {
        if (interval.si >= last_finish_time) {
            selected.push_back(interval);
            last_finish_time = interval.fi;
        }
    }

    return selected;
}

int main() {
    int n;
    cout << "Enter the number of intervals: ";
    cin >> n;

    vector<Interval> intervals;
    cout << "Enter the intervals (start and finish):" << endl;
    for (int i = 0; i < n; ++i) {
        int si, fi;
        cin >> si >> fi;
        intervals.emplace_back(si, fi, i+1);
    }

    // calculate the solution
    vector<Interval> solution = greedy_selection(intervals);

    // show the solution
    cout << solution.size() << "Selected intervals:" << endl;
    int i = 0;
    for (const auto& interval : solution) {
        cout << interval.idx << " : " << "[" << interval.si << ", " << interval.fi << "]" << endl;
    }

    return 0;
}