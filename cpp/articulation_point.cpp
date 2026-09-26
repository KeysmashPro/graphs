#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using usize = size_t;
using u32 = unsigned int;
using i32 = int;

struct Two {u32 n0, n1;};
struct Frame {u32 v, n, a, c;};


/* v - current vertex, a - ancestor, n - neighbot counter */
/* c - child counter, to - current neighbor */
vector<u32> find_articulation_point(vector<vector<Two>> &g)
{
    u32 s = g.size();
    u32 counter = 1;
    vector<Frame> frames;
    vector<u32> points;
    vector<u32> tin(s, 0); vector<u32> low(s, 0);

    for(u32 start = 0; start < s; ++start) {
        if (tin[start]) continue;
        tin[start] = low[start] = counter++;
        frames.push_back({start, 0, start, 0});

        while (!frames.empty()) {
            auto &top = frames.back();
            auto [v, n, a, c] = top;
            if (n < g[v].size()) {
                auto to = g[v][n].n0;
                top.n++;
                if (to == a) continue;
                if (!tin[to]) {
                    top.c++;
                    tin[to] = low[to] = counter++;
                    frames.push_back({to ,0 , v, 0});
                } else {
                    low[v] = min(low[v], tin[to]);
                }
                continue;
            }
            frames.pop_back();

            if (v == a && c > 1) {
                points.push_back(v);
                continue;
            }

            if (frames.empty()) continue;

            u32 m = 0;
            for (u32 i = 0; i < g[v].size(); ++i) {
                u32 idx = g[v][i].n0;
                if (idx == a) continue;
                m = max(m, low[idx]);
            }
            if (m >= tin[v]) points.push_back(v);
            low[a] = min(low[a], low[v]);
        }
    }
    return points;
}

i32 main(void) {
    /* size, edges */
    u32 s, e;
    ifstream file("test.txt");
    file >> s >> e;

    vector<vector<Two>> g(s);
    for (u32 src, sin, i = 0; i < e; ++i) {
        file >> src >> sin; src--; sin--;
        g[src].push_back({sin, 1});
        g[sin].push_back({src, 1});
    }

    vector<u32> points = find_articulation_point(g);
    sort(points.begin(), points.end());
    cout << "Articulation points count: " << points.size() << "\n[ ";
    for (auto x : points) { cout << x + 1 << ' '; }
    cout << "]\n";
    return 0;
}
