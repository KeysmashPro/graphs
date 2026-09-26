#include <bits/stdc++.h>

using namespace std;
using usize = size_t;
using u32 = unsigned int;
using i32 = int;

struct Two {u32 n0, n1;};
struct Frame {u32 v, n, a;};

vector<Two> find_bridges(vector<vector<Two>> &g)
{
    u32 s = g.size();
    u32 counter = 1;
    vector<Frame> frames;
    vector<Two> bridges;
    vector<u32> tin(s, 0);
    vector<u32> low(s, 0);

    for(u32 start = 0; start < s; ++start) {
        if (tin[start]) continue;
        tin[start] = low[start] = counter++;
        frames.push_back({start, 0, start});

        while (!frames.empty()) {
            auto &frame = frames.back();
            auto &[v, n, a] = frame;
            if (n < g[v].size()) {
                auto to = g[v][n].n0;
                n++; /* Next neighbor */
                if (to == a) continue;
                if (!tin[to]) {
                    tin[to] = low[to] = counter++;
                    frames.push_back({to ,0, v});
                } else {
                    low[v] = min(low[v], tin[to]);
                }
                continue;
            }
            u32 ancestor = a;
            u32 vertex = v;
            frames.pop_back();
            if (!frames.empty()) {
                low[ancestor] = min(low[ancestor], low[vertex]);
                if (low[vertex] > tin[ancestor]) {
                    bridges.push_back({ancestor + 1, vertex + 1});
                }
            }
        }
    }
    return bridges;
}

i32 main(void) {
    /* size, edges */
    u32 s, e;
    ifstream file("test.txt");
    file >> s >> e;

    vector<vector<Two>> g(s);
    for (u32 src, sin, i = 0; i < e; ++i) {
        file >> src >> sin;
        g[src].push_back({sin - 1, 1});
        g[sin].push_back({src - 1, 1});
    }

    vector<Two> bridges = find_bridges(g);
    cout << "Bridges count: " << bridges.size() << endl;
    for (auto x : bridges) { cout << x.n0 << '-' << x.n1<< '\n'; }
    return 0;
}
