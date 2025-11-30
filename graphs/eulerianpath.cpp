#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int,int>>> adj(n+1); // adjacency list: {neighbor, edge_id}

    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }

    // Check that all vertices have even degree
    for (int v = 1; v <= n; ++v) {
        if (adj[v].size() % 2 != 0) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    // Find a starting vertex (any with degree > 0)
    int start = -1;
    for (int v = 1; v <= n; ++v) {
        if (!adj[v].empty()) {
            start = v;
            break;
        }
    }

    if (start == -1) {
        cout << "IMPOSSIBLE\n"; // no edges in the graph
        return 0;
    }

    vector<bool> used(m+1, false); // mark edges used
    stack<int> st;
    st.push(start);

    vector<int> path; // final Eulerian cycle

    // Hierholzer's algorithm
    while (!st.empty()) {
        int v = st.top();
        bool found_unused = false;

        for (auto &[u, eid] : adj[v]) {
            if (!used[eid]) {
                used[eid] = true;
                st.push(u);
                found_unused = true;
                break;
            }
        }

        if (!found_unused) {
            path.push_back(v);
            st.pop();
        }
    }

    reverse(path.begin(), path.end());

    // Check if path covers all edges
    if ((int)path.size() != m + 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    // Print Eulerian cycle
    for (size_t i = 0; i < path.size(); ++i) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << '\n';

    return 0;
}
