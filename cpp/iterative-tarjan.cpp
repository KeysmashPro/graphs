#include <bits/stdc++.h>

using namespace std;
using u32 = unsigned int;
using i32 = int;

i32 main(void) {
    u32 n, m, c = 0;
    cin >> n >> m;

    vector<vector<pair<u32, i32>>> g(n);
    vector<u32> tin(n, 0);
    vector<u32> fup(n, 0);
    vector<u32> stk; stk.reserve(n);
    vector<bool> on_stk(n, 0);
    vector<u32> scc(n);

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
        if (tin[start]) continue;

        vector<pair<u32, u32>> frames;
        frames.push_back({start, 0});
        tin[start] = fup[start] = counter++;
        stk.emplace_back(start);
        on_stk[start] = 1;

        while(!frames.empty()) {
            auto &[v, neighbor] = frames.back();
            if (neighbor < g[v].size()) {
                auto to = g[v][neighbor].first;
                neighbor++;
                if (!tin[to]) {
                    tin[to] = fup[to] = counter++;
                    stk.push_back(to);
                    on_stk[to] = true;
                    frames.push_back({to, 0});
                } else if (on_stk[to]) {
                    fup[v] = min(fup[v], fup[to]);
                }
            } else {
                if (tin[v] == fup[v]) {
                    c++;
                    for (;;) {
                        u32 s = stk.back();
                        stk.pop_back();
                        on_stk[s] = 0;
                        scc[s] = c;
                        if (s == v) break;
                    }
                }

                frames.pop_back();
                if (!frames.empty()) {
                    u32 parent = frames.back().first;
                    fup[parent] = min(fup[parent], fup[v]);
                }
            }
        }
    }

    cout << c << endl;
    return 0;
}
