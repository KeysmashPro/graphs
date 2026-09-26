#include <iostream>
#include <numeric>
#include <vector>
#include <map>

using namespace std;
using u64 = unsigned long long;
using i64 = long long;
using u32 = unsigned int;
using i32 = int;

u64 mushrooms(u32 n) {
    u64 res = 0;
    i64 stay = n;
    for(u32 i = 1; stay > 0; ++i) {
        res += stay;
        stay -= i;
    }
    return res;
}

u32 find_scc(vector<vector<pair<u32, u32>>> &g, vector<u32> &scc) {
    size_t n = g.size();
    vector<bool> on_stak(n);
    vector<u32> stak;
    vector<u32> tin(n);
    vector<u32> fup(n);
    u32 counter = 1;
    u32 cc = 0;

    auto fn = [&](auto&& self, u32 v) -> void {

        tin[v] = fup[v] = counter++;
        on_stak[v] = true;
        stak.push_back(v);

        for (u32 i = 0; i < g[v].size(); ++i) {
            auto &[to, weight] = g[v][i];
            if (!tin[to]) {
                self(self, to);
                fup[v] = min(fup[v], fup[to]);
            } else if (on_stak[to]) {
                fup[v] = min(fup[v], tin[to]);
            }
        }

        if (tin[v] != fup[v]) { return; }

        cc += 1;
        for (;;) {
            u32 t = stak.back();
            stak.pop_back();
            on_stak[t] = false;
            scc[t] = cc;
            if (t == v) break;
        }
    };

    for (u32 i = 0; i < n; ++i) {
        if (!tin[i]) { fn(fn, i); }
    }
    return cc;
}


i32 main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    u32 n, m;
    cin >> n >> m;
    vector<vector<pair<u32, u32>>> graph(n);
    vector<u32> scc(n);
    vector<u32> csz(n);

    for (u32 i = 0; i < m; ++i) {
        u32 x, y, w;
        cin >> x >> y >> w;
        x--; y--;
        graph[x].push_back({y, w});
    }

    csz.resize(find_scc(graph, scc));
    map<u32, u64> edges_mapa;

    for (u32 i = 0; i < n; ++i) {
        for (auto to : graph[i]) {
            if (scc[i] == scc[to.first]) {
                csz[scc[i]] += mushrooms(to.second);
            } else {
                edges_mapa[((u64)i << 32) + to.first] = to.second;
            }
        }
    }

    // Do something with DAG edges
    
    // Kan algorithm + DP

    u64 scc_sum = accumulate(csz.begin(), csz.end(), 0ULL);
    cout << scc_sum << endl;

    return 0;
}
