#include <bits/stdc++.h>

using namespace std;
using u64 = unsigned long long;
using i64 = long long;
using u32 = unsigned int;
using i32 = int;

#pragma GCC optimization("unroll-loops")
#pragma GCC optimization("O3")
#pragma GCC target("avx2")

void dfs_stk(vector<vector<pair<i32, i32>>> &g, vector<bool> &visited, vector<i32> &stk, i32 v) {
    visited[v] = 1;
    for (i32 i = 0; i < g[v].size(); ++i) {
        i32 idx = g[v][i].first;
        if (visited[idx]) continue;
        dfs_stk(g, visited, stk, idx);
    }
    stk.push_back(v);
}

void dfs(vector<vector<pair<i32, i32>>> &g, vector<i32> &visited, i32 v, i32 x) {
    visited[v] = x;
    for (i32 i = 0; i < g[v].size(); ++i) {
        i32 idx = g[v][i].first;
        if (visited[idx]) continue;
        dfs(g, visited, idx, x);
    }
}

i32 main(void) {
    int m, n;
    cin >> n >> m;
    vector<vector<pair<i32, i32>>> g(n);
    vector<vector<pair<i32, i32>>> t(n);
    vector<bool> visited(n);
    vector<i32> stk; stk.reserve(n);

    for (int i = 0; i < m; ++i) {
        i32 a, b, w;
        cin >> a >> b >> w;
        a--; b--;
        g[a].emplace_back(b, w);
        t[b].emplace_back(a, w);
    }

    for (i32 i = 0; i < visited.size(); ++i)
        if (!visited[i]) { dfs_stk(g, visited, stk, i); }

    vector<i32> scc(n);
    i32 num = 1;
    
    while (!stk.empty()) {
        i32 idx = stk.back(); stk.pop_back();
        if (scc[idx]) continue;
        dfs(t, scc, idx, num);
        num++;
    }
    
    vector<vector<i32>> cc(--num);
    for (int i = 0; i < scc.size(); ++i)
        cc[scc[i]-1].push_back(i);

    for (auto &x : cc)
        sort(x.begin(), x.end());
    
    sort(cc.begin(), cc.end(), [](const vector<i32> &a, const vector<i32> &b) { return a[0] < b[0];});

    cout << "scc: " << num << '\n';
    for (auto x : cc) {
        cout << x.size() << '\n';
        for (auto y : x) cout << y + 1 << ' ';
        cout << '\n';
    }
    return 0;
}
