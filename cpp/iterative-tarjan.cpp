#include <bits/stdc++.h>

using namespace std;
using u32 = unsigned int;
using i32 = int;

i32 main(void) {
    u32 m, n;
    cin >> n >> m;

    // SSC storage
    vector<u32> offset; offset.reserve(n);
    vector<u32> scc(n);
    u32 cc = 0;

    // Var
    vector<vector<pair<u32, i32>>> g(n);
    vector<u32> enter(n, 0);
    vector<u32> exit(n, 0);
    vector<u32> stk; stk.reserve(n);
    vector<bool> on_stk(n, 0);

    // Input
    for (u32 i = 0; i < m; ++i) {
        i32 a, b, w;
        cin >> a >> b >> w;
        a--; b--;
        g[a].emplace_back(b, w);
    }
    
    // Tarjan
    u32 counter = 1;
    for (u32 start = 0; start < g.size(); ++start) {
        if (enter[start]) continue;

        vector<pair<u32, u32>> frames;
        frames.push_back({start, 0});
        enter[start] = exit[start] = counter++;
        stk.emplace_back(start);
        on_stk[start] = 1;

        while(!frames.empty()) {
            auto &[v, neighbor] = frames.back();
            if (neighbor < g[v].size()) {
                auto to = g[v][neighbor].first;
                neighbor++;
                if (!enter[to]) {
                    enter[to] = exit[to] = counter++;
                    stk.push_back(to);
                    on_stk[to] = true;
                    frames.push_back({to, 0});
                } else if (on_stk[to]) {
                    exit[v] = min(exit[v], exit[to]);
                }
            } else {
                if (enter[v] == exit[v]) {
                    offset.push_back(cc);
                    for (;;) {
                        u32 s = stk.back();
                        stk.pop_back();
                        on_stk[s] = 0;
                        scc[cc] = s; cc++;
                        if (s == v) break;
                    }
                }

                frames.pop_back();
                if (!frames.empty()) {
                    u32 parent = frames.back().first;
                    exit[parent] = min(exit[parent], exit[v]);
                }
            }
        }
    }

    cout << offset.size() << endl;
    return 0;
}
