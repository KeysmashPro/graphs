#include <bits/stdc++.h>

using namespace std;
using u64 = unsigned long long;
using i64 = long long;
using u32 = unsigned int;
using i32 = int;

#pragma GCC optimization("unroll-loops")
#pragma GCC optimization("O3")
#pragma GCC target("avx2")

void tarjan(vector<vector<pair<u32, i32>>> &g, vector<vector<u32>> &scc, u32 &counter,
            vector<u32> &enter, vector<u32> &exit, vector<u32> &stk, vector<bool> &on_stk) {
        
    auto fn = [&](auto&& self, u32 v) -> void {
        enter[v] = exit[v] = counter++;
        stk.push_back(v);
        on_stk[v] = true;

        for (u32 i = 0; i < g[v].size(); ++i) {
            u32 idx = g[v][i].first;
            if (!enter[idx]) {
                self(self, idx);
                exit[v] = min(exit[v], exit[idx]);
            } else if(on_stk[idx]) {
                exit[v] = min(exit[v], exit[idx]);
            }
        }

        if (enter[v] != exit[v]) return;

        vector<u32> cc;
        for(;;) {
            u32 s = stk.back();
            stk.pop_back();
            cc.push_back(s);
            if (s == v) break;
        }
        scc.push_back(std::move(cc));
    };

    for (u32 i = 0; i < g.size(); ++i) {
        if (!enter[i]) fn(fn, i);
    }
}

i32 main(void) {
    u32 m, n;
    cin >> n >> m;

    vector<vector<pair<u32, i32>>> g(n);
    vector<u32> enter(n, 0);
    vector<u32> exit(n, 0);
    vector<vector<u32>> scc; vector<u32> stk; stk.reserve(n);
    vector<bool> on_stk(n, 0);

    for (u32 i = 0; i < m; ++i) {
        i32 a, b, w;
        cin >> a >> b >> w;
        a--; b--;
        g[a].emplace_back(b, w);
    }
    
    u32 c = 0;
    tarjan(g, scc, c, enter, exit, stk, on_stk);

    for (auto &x : scc)
        sort(x.begin(), x.end());
    
    sort(scc.begin(), scc.end(), [](const vector<u32> &a, const vector<u32> &b) {
            return a[0] < b[0];
    });

    cout << "scc: " << scc.size() << '\n';
    for (auto x : scc) {
        for (auto y : x) cout << y + 1 << ' ';
        cout << '\n';
    }
    return 0;
}
