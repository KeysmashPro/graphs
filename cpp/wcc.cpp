#include <bits/stdc++.h>

using namespace std;

using f64 = double;
using f32 = float;
using i64 = long long;
using i32 = int;
using u64 = unsigned long long;
using u32 = unsigned int;


i32 main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i32 n, m;
    cin >> n >> m;
    vector<i32> st;
    vector<i32> num(n, 0);  // current unchecked edge
    vector<bool> vis(n, 0); // visited vertesiec
    vector<vector<pair<i32, i32>>> vec(n);

    /* INPUT */
    for (i32 i = 0; i < m; ++i) {
        i32 i0, i1;
        cin >> i0 >> i1; i0--; i1--;
        vec[i1].push_back({i0, 1}); //reverse edges
    }

    /* DFS */
    vis[0] = 1;
    st.push_back(0);
    while (!st.empty()) {
        i32 idx = st.back();
        vis[idx] = 1;
        while (num[idx] < vec[idx].size() && vis[vec[idx][num[idx]].first]) num[idx]++;

        if (num[idx] < vec[idx].size()) {
            st.push_back(vec[idx][num[idx++]].first);
        } else {
            st.pop_back();
        }
    }

    /* Connected Component */
    vector<i32> res;
    res.reserve(n);
    for (i32 i = 0; i < n; ++i)
        if (vis[i]) res.push_back(i + 1);

    sort(res.begin(), res.end());
    
    for (auto x : res) {
        cout << x << ' ';
    }
    cout << '\n';
    return 0;
}

