#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std; using usize = size_t;
using u32 = unsigned int;
using i32 = int;

struct Frame {u32 v, n, a, c;};

/* v - current vertex, a - ancestor, n - neighbot counter c - multi graph fix */
void articulation_points(vector<vector<pair<u32,u32>>> &g, vector<pair<u32,u32>> &bridges, vector<u32> &points)
{
    u32 n = g.size();
    vector<bool> art_point(n, false);
    vector<u32> tin(n, 0);
    vector<u32> low(n, 0);
    u32 counter = 1;
    vector<Frame> frames;

    for (u32 start = 0; start < n; ++start) {
        if (tin[start]) continue;
        tin[start] = low[start] = counter++;
        frames.push_back({start, 0, start});
        u32 src_counter = 0;

        while(!frames.empty()) {
            auto &top = frames.back();
            auto [v, n, a, c] = top;
            if (n < g[v].size()) {
                auto to = g[v][n].first;
                top.n++;
                if (a == to && !c) { top.c++; continue; }
                if(!tin[to]) {
                    if (v == a) src_counter++;
                    tin[to] = low[to] = counter++;
                    frames.push_back({to, 0, v});
                } else {
                    low[v] = min(low[v], tin[to]);
                }
                continue;
            }
            frames.pop_back();
            if (frames.empty()) break;

            if (low[v] > tin[a]) bridges.push_back({a, v});
            if (a != start && low[v] >= tin[a]) art_point[v] = true;
            low[a] = min(low[a], low[v]);
        }
        if (src_counter > 1) art_point[start] = true;
    }
    for (u32 i = 0; i < n; ++i ) {
        if (art_point[i]) points.push_back(i);
    }
}


i32 main(void) {
    u32 n, m;
    ifstream file("test.txt");
    file >> n >> m;
    
    vector<vector<pair<u32,u32>>> g(n);
        for (u32 src, sin, i = 0; i < m; ++i) {
        file >> src >> sin; src--; sin--;
        g[src].push_back({sin, 1});
        g[sin].push_back({src, 1});
    }

    vector<pair<u32,u32>> bridges;
    vector<u32> points;
    articulation_points(g, bridges, points);
    sort(points.begin(), points.end());
    sort(bridges.begin(), bridges.end());
    cout << "Articulation points count: " << points.size() << "\n[ ";
    for (auto x : points) { cout << x + 1 << ' '; }
    cout << "]\n";
    cout << "Bridges count: " << bridges.size() << "\n[ ";
    for (auto x : bridges) { cout << x.first + 1 << '-' << x.second + 1 << ' '; }
    cout << "]\n";
    return 0;
}
